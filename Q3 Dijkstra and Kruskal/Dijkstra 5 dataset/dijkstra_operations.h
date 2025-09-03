#ifndef DIJKSTRA_OPERATIONS_H
#define DIJKSTRA_OPERATIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <algorithm>

// Define DijkstraStar struct
struct DijkstraStar {
    char name;
    double x, y, z; // x-axis, y-axis, z-axis
    int weight, profit;
};

// Define Edge struct for graph representation
struct Edge {
    char to; // star destination
    double distance;
};

// Define PathInfo struct to store distance and path
struct PathInfo {
    double distance;
    std::vector<char> path;
};

// Function to calculate distance between two DijkstraStars
double dijkstra_calculate_distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

// Function to read star dataset for Dijkstra's algorithm
void read_star_dataset(const std::string &filename, std::vector<DijkstraStar> &stars, std::unordered_map<char, std::vector<Edge>> &graph) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "Star") {
            DijkstraStar star;
            iss >> star.name >> star.x >> star.y >> star.z >> star.weight >> star.profit;
            stars.push_back(star);
        } else if (type == "Route") {
            char from, to;
            std::string delimiter;
            double distance;
            iss >> from >> delimiter >> to >> delimiter >> distance;
            graph[from].push_back({to, distance});
            graph[to].push_back({from, distance}); 
        }
    }

    infile.close();
}

// Function to apply Dijkstra's Algorithm
std::unordered_map<char, PathInfo> dijkstra(const std::unordered_map<char, std::vector<Edge>> &graph, char start) {
    // Store shortest distance and path from start star to other stars
    std::unordered_map<char, PathInfo> distances;
    for (const auto &node : graph) {
        // Stars unreachable from start
        distances[node.first] = {std::numeric_limits<double>::infinity(), {}};
    }
    // Set distance from start to itself as 0
    distances[start] = {0, {start}};

    // Compare star (char) and distances (double)
    auto compare = [](const std::pair<char, double> &a, const std::pair<char, double> &b) {
        return a.second > b.second;
    };
    std::priority_queue<std::pair<char, double>, std::vector<std::pair<char, double>>, decltype(compare)> pq(compare);
    pq.push({start, 0});

    // Iterate until pq is empty
    while (!pq.empty()) {
        // Retrieve star with smallest distance from pq
        char current = pq.top().first; 
        double current_distance = pq.top().second;
        pq.pop();

        // Check if current star is greater than currently known shortest distance
        if (current_distance > distances[current].distance) {
            continue;
        }

        for (const auto &edge : graph.at(current)) {
            double new_distance = current_distance + edge.distance;
            if (new_distance < distances[edge.to].distance) {
                distances[edge.to].distance = new_distance;
                distances[edge.to].path = distances[current].path;
                distances[edge.to].path.push_back(edge.to);
                pq.push({edge.to, new_distance});
            }
        }
    }

    return distances;
}

// Function to save distances and paths to a file
void save_distances(const std::unordered_map<char, PathInfo> &distances, const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto &entry : distances) {
        outfile << "Shortest distance from Star A to Star " << entry.first << " is " << entry.second.distance << ", path: {";
        for (const auto &star : entry.second.path) {
            outfile << star << (star == entry.second.path.back() ? "" : ", ");
        }
        outfile << "}" << std::endl;
    }

    outfile.close();
}

#endif // DIJKSTRA_OPERATIONS_H
