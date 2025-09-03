#include <iostream>
#include <chrono> // For timing

#include "q1_dataset2.h"
#include "kruskal.h"

void generate_dataset2()
{
    // Sum of other group members' ID numbers
    long long int sum_of_ids = 1211101007LL + 1211200107LL + 1221303660LL;
    const int star_count = 20; // Number of stars to generate

    // Generate stars
    std::vector<Star> stars = generate_stars(star_count, sum_of_ids);

    // Generate routes
    std::vector<std::pair<char, char>> routes = generate_routes(star_count);

    // Save dataset
    save_star_dataset(stars, routes, "dataset2_1.txt");
}

void find_minimum_spanning_tree()
{
    // Read dataset
    std::vector<KruskalEdge> edges = read_kruskal_dataset("dataset2_1.txt");

    // Find MST using Kruskal's algorithm
    auto start_time = std::chrono::high_resolution_clock::now(); // Start timing
    std::vector<KruskalEdge> mst = kruskal(edges, 20);           // Assuming there are 20 stars
    auto end_time = std::chrono::high_resolution_clock::now();   // End timing

    // Calculate duration
    std::chrono::duration<double> duration = end_time - start_time;

    // Save MST
    save_mst(mst, "minimum_spanning_tree.txt");

    // Output execution time
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
}

int main()
{

    find_minimum_spanning_tree(); // Call the function to find minimum spanning tree

    return 0;
}
