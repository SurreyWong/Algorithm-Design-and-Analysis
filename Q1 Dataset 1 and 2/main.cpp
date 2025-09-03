#include <iostream>
#include "q1_dataset1.h"
#include "q1_dataset2.h"
#include <cstdlib>  // For system()
#include <ctime>  // Include the ctime header

void generate_dataset1() {
    // Generate and save datasets
    generate_and_save_datasets();
}

void generate_dataset2() {
    // Get current time as seed
    long long int seed = static_cast<long long int>(time(nullptr));

    // Sum of other group members' ID numbers
    long long int sum_of_ids = 1211101007LL + 1211200107LL + 1221303660LL;
    const int star_count = 20;  // Number of stars to generate

    // Generate stars
    std::vector<Star> stars = generate_stars(star_count, sum_of_ids);

    // Generate routes
    std::vector<std::pair<char, char>> routes = generate_routes(star_count);

    // Save dataset and generate DOT file
    save_star_dataset(stars, routes, "dataset2_1.txt");

    // Convert DOT file to PNG using Graphviz
    int result = system("dot -Tpng stars_graph.dot -o stars_graph.png");
    if (result != 0) {
        std::cerr << "Error: Could not generate PNG file using Graphviz." << std::endl;
    } else {
        std::cout << "PNG file generated successfully: stars_graph.png" << std::endl;
    }
}

int main() {
    int choice;
    std::cout << "Select an option:" << std::endl;
    std::cout << "1. Generate dataset 1" << std::endl;
    std::cout << "2. Generate dataset 2" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            generate_dataset1();
            break;
        case 2:
            generate_dataset2();
            break;
        default:
            std::cerr << "Invalid choice." << std::endl;
            return 1;
    }

    return 0;
}
