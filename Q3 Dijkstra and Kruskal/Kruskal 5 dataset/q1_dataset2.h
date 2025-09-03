#ifndef STARS_GENERATOR_H
#define STARS_GENERATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_set>

struct Star {
    char name;
    double x, y, z;
    int weight, profit;
};

// Function to calculate the sum of digits in a number
long long sum_of_digits(long long number) {
    long long sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

// Custom random number generator
int custom_rand(const std::vector<int>& allowed_digits) {
    int num_digits = allowed_digits.size();
    return allowed_digits[rand() % num_digits];
}

// Function to extract unique digits from seed
std::vector<int> extract_unique_digits_2(long long seed) {
    std::unordered_set<int> unique_digits;
    while (seed > 0) {
        unique_digits.insert(seed % 10);
        seed /= 10;
    }
    return std::vector<int>(unique_digits.begin(), unique_digits.end());
}

// Function to generate unique random number from allowed digits
int generate_unique_number(const std::vector<int>& allowed_digits, int num_digits) {
    int generated_number = 0;
    for (int i = 0; i < num_digits; ++i) {
        generated_number = generated_number * 10 + custom_rand(allowed_digits);
    }
    return generated_number;
}

// Function to generate stars
std::vector<Star> generate_stars(int count, long long int sum_of_ids) {
    std::vector<int> allowed_digits = extract_unique_digits_2(sum_of_ids);
    srand(static_cast<unsigned int>(time(0) + sum_of_digits(sum_of_ids))); // Seed the random number generator

    std::vector<Star> stars;
    // Generate coordinates and random values for weight and profit for each star
    for (char name = 'A'; name < 'A' + count; ++name) {
        Star star;
        star.name = name;
        star.x = generate_unique_number(allowed_digits, 3);  // Random 3-digit number
        star.y = generate_unique_number(allowed_digits, 3);  // Random 3-digit number
        star.z = generate_unique_number(allowed_digits, 3);  // Random 3-digit number
        star.weight = generate_unique_number(allowed_digits, 2);   // Random 2-digit number
        star.profit = generate_unique_number(allowed_digits, 2);   // Random 2-digit number
        stars.push_back(star);
    }

    return stars;
}

// Function to calculate distance between two stars
double calculate_distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

// Function to generate routes ensuring each star connects to at least 3 others
// Function to generate routes ensuring connectivity
std::vector<std::pair<char, char>> generate_routes(int count) {
    std::vector<std::pair<char, char>> routes;

    // Ensure each star connects to at least one other star
    for (char i = 'A'; i < 'A' + count - 1; ++i) {
        routes.push_back({i, i + 1});
    }

    // Add additional random connections to ensure diversity
    int additional_connections = 54 - (count - 1);
    while (additional_connections > 0) {
        char name1 = 'A' + rand() % count;
        char name2 = 'A' + rand() % count;
        if (name1 != name2 && std::find(routes.begin(), routes.end(), std::make_pair(name1, name2)) == routes.end() &&
            std::find(routes.begin(), routes.end(), std::make_pair(name2, name1)) == routes.end()) {
            routes.push_back(std::make_pair(name1, name2));
            --additional_connections;
        }
    }
    return routes;
}


// Function to save star dataset
void save_star_dataset(const std::vector<Star> &stars, const std::vector<std::pair<char, char>> &routes, const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Save star details
    for (const auto &star : stars) {
        outfile << "Star " << star.name << " " << star.x << " " << star.y << " " << star.z << " " << star.weight << " " << star.profit << std::endl;
    }

    // Save route details with distances
    for (const auto &route : routes) {
        Star star1, star2;
        for (const auto &star : stars) {
            if (star.name == route.first) star1 = star;
            if (star.name == route.second) star2 = star;
        }
        double distance = calculate_distance(star1.x, star1.y, star1.z, star2.x, star2.y, star2.z);
        outfile << "Route " << route.first << "-" << route.second << " Distance: " << distance << std::endl;
    }

    outfile.close();
    std::cout << "Star dataset saved to " << filename << std::endl;
}

#endif // STARS_GENERATOR_H
