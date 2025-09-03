#ifndef DATASETS_GENERATOR_H
#define DATASETS_GENERATOR_H

#include <iostream>
#include <fstream>
#include <cstdlib>  // For srand() and rand()
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iterator>

// Group leader's ID
const long long id_leader = 1211202025;

// Dataset sizes
const int size_dataset[] = {100, 1000, 10000, 100000, 500000, 1000000};

// Function to extract unique digits from a given number
std::vector<int> extract_unique_digits(long long number) {
    std::unordered_set<int> unique_digits;
    while (number > 0) {
        unique_digits.insert(number % 10);
        number /= 10;
    }
    return std::vector<int>(unique_digits.begin(), unique_digits.end());
}

// Function to generate a dataset of random 3-digit numbers
std::vector<int> generate_dataset(int seed, int size, const std::vector<int>& allowed_digits) {
    std::vector<int> dataset;
    dataset.reserve(size);

    // Seed the random number generator
    srand(seed);

    int num_digits = allowed_digits.size();

    // Generate random numbers
    for (int i = 0; i < size; ++i) {
        int generated_number = 0;
        for (int j = 0; j < 3; ++j) {
            generated_number = generated_number * 10 + allowed_digits[rand() % num_digits];
        }
        dataset.push_back(generated_number);
    }

    return dataset;
}

// Function to save a dataset to a file
void save_dataset(const std::vector<int>& dataset, const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        std::copy(dataset.begin(), dataset.end(), std::ostream_iterator<int>(outfile, "\n"));
        outfile.close();
        std::cout << "Dataset with " << dataset.size() << " elements saved to " << filename << std::endl;
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

// Function to generate and save multiple datasets
void generate_and_save_datasets() {
    std::vector<int> allowed_digits = extract_unique_digits(id_leader);

    for (int i = 0; i < 6; ++i) {
        std::string filename = "dataset_" + std::to_string(i + 1) + ".txt";
        std::vector<int> dataset = generate_dataset(id_leader + i, size_dataset[i], allowed_digits);
        save_dataset(dataset, filename);
    }
}

#endif // DATASETS_GENERATOR_H
