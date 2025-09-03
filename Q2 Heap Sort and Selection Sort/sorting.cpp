#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// Function to read dataset from a text file
vector<int> readDataset(const string& filename, int size) {
    vector<int> dataset;
    dataset.reserve(size);
    ifstream inputFile(filename);
    int value;
    for (int i = 0; i < size && inputFile >> value; ++i) {
        dataset.push_back(value);
    }
    inputFile.close();
    return dataset;
}

// Function to write sorted dataset to a text file
void writeSortedDataset(const vector<int>& sortedDataset, const string& outputFilename) {
    ofstream outputFile(outputFilename);
    for (int value : sortedDataset) {
        outputFile << value << "\n";
    }
    outputFile.close();
}

// Heapify function for heap sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap sort function
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Heap sort
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Selection sort function
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

int main() {
    vector<string> filenames = {"dataset_1.txt", "dataset_2.txt", "dataset_3.txt", "dataset_4.txt", "dataset_5.txt", "dataset_6.txt"};
    vector<int> datasetSizes = {100, 1000, 10000, 100000, 500000, 1000000};

    for (int i = 0; i < 6; ++i) {
        // Read dataset from text file
        vector<int> dataset = readDataset(filenames[i], datasetSizes[i]);
        
        // Perform heap sort
        vector<int> heapSortedDataset = dataset;
        auto startHeap = chrono::high_resolution_clock::now();
        heapSort(heapSortedDataset);
        auto endHeap = chrono::high_resolution_clock::now();
        chrono::duration<double> heapDuration = endHeap - startHeap;

        // Write heap sorted dataset to text file
        string heapSortOutputFilename = "heap_sorted_dataset_" + to_string(i + 1) + ".txt";
        writeSortedDataset(heapSortedDataset, heapSortOutputFilename);

        // Perform selection sort
        vector<int> selectionSortedDataset = dataset;
        auto startSelection = chrono::high_resolution_clock::now();
        selectionSort(selectionSortedDataset);
        auto endSelection = chrono::high_resolution_clock::now();
        chrono::duration<double> selectionDuration = endSelection - startSelection;

        // Write selection sorted dataset to text file
        string selectionSortOutputFilename = "selection_sorted_dataset_" + to_string(i + 1) + ".txt";
        writeSortedDataset(selectionSortedDataset, selectionSortOutputFilename);

        // Print timing information
        cout << "Dataset " << (i + 1) << ":\n";
        cout << "Heap Sort Time: " << heapDuration.count() << " seconds\n";
        cout << "Selection Sort Time: " << selectionDuration.count() << " seconds\n\n";
    }

    return 0;
}
