#ifndef KRUSKAL_MINIMUM_SPANNING_TREE_H
#define KRUSKAL_MINIMUM_SPANNING_TREE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "q1_dataset2.h"

struct KruskalEdge {
    char from;
    char to;
    double distance;
};

// Union-Find data structure
struct UnionFind {
    std::vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void union_sets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }
};

// Function to read dataset for Kruskal's algorithm
std::vector<KruskalEdge> read_kruskal_dataset(const std::string &filename) {
    std::ifstream infile(filename);
    std::vector<KruskalEdge> edges;

    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return edges; // Return an empty vector if file cannot be opened
    }

    std::string line;
    while (std::getline(infile, line)) {
        char from, to;
        double distance;
        if (sscanf(line.c_str(), "Route %c-%c Distance: %lf", &from, &to, &distance) == 3) {
            edges.push_back({from, to, distance});
        }
    }

    infile.close();
    return edges;
}

// Define Kruskal's algorithm implementation
std::vector<KruskalEdge> kruskal(const std::vector<KruskalEdge> &edges, int vertex_count) {
    std::vector<KruskalEdge> mst;

    // Sort the edges by distance
    std::vector<KruskalEdge> sorted_edges = edges;
    std::sort(sorted_edges.begin(), sorted_edges.end(), [](const KruskalEdge &a, const KruskalEdge &b) {
        return a.distance < b.distance;
    });

    UnionFind uf(vertex_count);

    auto get_index = [](char name) { return name - 'A'; }; // Convert star name to index

    for (const auto &edge : sorted_edges) {
        int u = get_index(edge.from);
        int v = get_index(edge.to);
        if (uf.find(u) != uf.find(v)) {
            uf.union_sets(u, v);
            mst.push_back(edge);
            if (mst.size() == vertex_count - 1) break; // Stop when MST has n-1 edges
        }
    }

    return mst;
}

void save_mst(const std::vector<KruskalEdge> &mst, const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto &edge : mst) {
        outfile << "Connected Stars: " << edge.from << " - " << edge.to << " Distance: " << edge.distance << std::endl;
    }

    outfile.close();
    std::cout << "MST saved to " << filename << std::endl;
}

#endif // KRUSKAL_MINIMUM_SPANNING_TREE_H
