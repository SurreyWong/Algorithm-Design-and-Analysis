#include <iostream>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include "dijkstra_operations.h"

void save_shortest_paths(const std::unordered_map<char, PathInfo>& distances, const std::vector<DijkstraStar>& stars, const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Ensure all stars are included in the output
    for (const auto& star : stars) {
        char star_name = star.name;
        if (distances.find(star_name) != distances.end()) {
            const auto& info = distances.at(star_name);
            outfile << "Shortest distance from Star A to Star " << star_name << " is " << info.distance <<std::endl;
    
        } else {
            outfile << "Star " << star_name << " is unreachable from Star A." << std::endl;
        }
    }

    outfile.close();
}


int main() {
    std::vector<DijkstraStar> stars;
    std::unordered_map<char, std::vector<Edge>> graph;

    // Start timing for the entire program
    auto start_program = std::chrono::steady_clock::now();

    // Read dataset
    read_star_dataset("dataset2_1.txt", stars, graph);

    // Find shortest paths from Star A
    std::unordered_map<char, PathInfo> distances = dijkstra(graph, 'A');

    // Save shortest paths to file
    save_shortest_paths(distances, stars, "shortest_paths.txt");

    // End timing for the entire program
    auto end_program = std::chrono::steady_clock::now();

    // Calculate total duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_program - start_program);
    std::cout << "Result is saved to shortest_paths.txt" <<std::endl;

    // Print execution time of the whole program
    std::cout << "Total execution time: " << duration.count() << " milliseconds." << std::endl;

    return 0;
}