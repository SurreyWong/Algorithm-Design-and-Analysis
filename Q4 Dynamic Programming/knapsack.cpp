#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <unordered_set>
#include <chrono>

// Structure to represent a Star
struct Star {
    char name;
    double x, y, z;
    int weight, profit;
};

// Function to read stars from a file
std::vector<Star> read_stars(const std::string &filename) {
    std::ifstream infile(filename);
    std::vector<Star> stars;
    std::unordered_set<char> star_names; // To keep track of added star names

    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            Star star;
            std::sscanf(line.c_str(), "Star %c %lf %lf %lf %d %d", &star.name, &star.x, &star.y, &star.z, &star.weight, &star.profit);
            
            // Check if the star name has already been added
            if (star_names.find(star.name) == star_names.end()) {
                stars.push_back(star);
                star_names.insert(star.name); // Add the star name to the set
            }
        }
        infile.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    return stars;
}

// Function to solve the 0/1 Knapsack problem using Dynamic Programming
std::tuple<int, std::vector<Star>, std::vector<std::vector<int>>> knapsack(const std::vector<Star> &stars, int capacity) {
    int n = stars.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    // Build the DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (stars[i - 1].weight <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - stars[i - 1].weight] + stars[i - 1].profit);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Find the stars to include in the knapsack
    std::vector<Star> selected_stars;
    int w = capacity;
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected_stars.push_back(stars[i - 1]);
            w -= stars[i - 1].weight; // Decrease the remaining capacity
        }
    }

    // Reverse the selected stars since we iterated backwards
    std::reverse(selected_stars.begin(), selected_stars.end());

    // Calculate the total profit
    int total_profit = 0;
    for (const auto &star : selected_stars) {
        total_profit += star.profit;
    }

    return {dp[n][capacity], selected_stars, dp};
}

// Function to save the result to a file
void save_result(const std::vector<std::vector<int>> &dp, const std::vector<Star> &selected_stars, int total_profit, const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Calculate the total weight
    int total_weight = 0;
    for (const auto &star : selected_stars) {
        total_weight += star.weight;
    }

    // Save the total weight and profit
    outfile << "Total Weight: " << total_weight << " kg\n";
    outfile << "Total Profit: " << total_profit << "\n\n";

    // Save the selected stars
    outfile << "Stars to visit:\n";
    for (const auto &star : selected_stars) {
        outfile << "Star " << star.name << " Weight: " << star.weight << " kg, Profit: " << star.profit << "\n";
    }

    // Save the DP matrix
    outfile << "\nDynamic programming table:\n";
    // Print column headers
    outfile << "     "; // Space for row headers
    for (int col = 0; col <= 800; ++col) {
        outfile << std::setw(4) << col << " ";
    }
    outfile << "\n";
    // Print rows with row headers
    for (int i = 0; i < dp.size(); ++i) {
        outfile << std::setw(4) << i << " ";
        for (int j = 0; j <= 800; ++j) {
            outfile << std::setw(4) << dp[i][j] << " ";
        }
        outfile << "\n";
    }

    outfile.close();
    std::cout << "Result saved to " << filename << std::endl;
}

int main() {
    std::string filename = "dataset2_1.txt";
    int capacity = 800;

    auto start_time = std::chrono::high_resolution_clock::now(); // Start timing

    std::vector<Star> stars = read_stars(filename);

    // Solve the knapsack problem
    auto [max_profit, selected_stars, dp] = knapsack(stars, capacity);

    auto end_time = std::chrono::high_resolution_clock::now(); // End timing
    std::chrono::duration<double> duration = end_time - start_time;

    // Save the result to a file
    save_result(dp, selected_stars, max_profit, "knapsack_result.txt");

    // Output time and space complexity
    int n = stars.size();
    int space_complexity = sizeof(int) * (n + 1) * (capacity + 1); // DP table space complexity

    std::cout << "Execution Time: " << duration.count() << " seconds\n";
    std::cout << "Time Complexity: O(n * W), where n = " << n << " and W = " << capacity << "\n";
    std::cout << "Space Complexity: O(n * W), requiring " << space_complexity / 1024 << " KB\n"; // Convert bytes to KB

    return 0;
}
