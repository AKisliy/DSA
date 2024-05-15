//
// Created by alexe on 07.05.2024.
//
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include "StringGenerator.h"
#include "StandardSorter.h"
#include "SpecialSorter.h"

const std::string random_strings_name = "Random strings";
const std::string nearly_sorted_strings_name = "Nearly sorted strings";
const std::string reverse_sorted_strings_name = "Reverse sorted strings";

std::vector<std::string> getSubarray(const std::vector<std::string> &arr, size_t subarr_size) {
    if (subarr_size > arr.size()) {
        throw std::invalid_argument("Subarray size must me less or equal to arr size");
    }
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, arr.size() - subarr_size);
    size_t start = dist(rng);
    return {arr.begin() + start, arr.begin() + start + subarr_size};
}

void test_sort(std::vector<std::string> &test_array, const std::function<int(std::vector<std::string>&)>& sorter, const std::string& name,
               std::ofstream& resultsFile, const std::string& arr_name) {
    StandardSorter sd;
    for (int size = 100; size <= test_array.size(); size += 100) {
        std::vector<std::string>sub_vec = getSubarray(test_array, size);
        sd.characterComparisons = 0;
        auto time = std::chrono::high_resolution_clock::now();
        int comparisons = sorter(sub_vec);
        auto elapsed = std::chrono::high_resolution_clock::now() - time;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        resultsFile<<name<<","<<arr_name<<","<<size<<","<<millisec<<","<<comparisons<<"\n";
    }
}

void process_test_for_standard_sorter(
        std::vector<std::string> random_strings,
        std::vector<std::string> nearly_sorted_strings,
        std::vector<std::string> reverse_sorted_strings,
        std::ofstream& resultsFile)
{
    std::cout<<"Started standard sorts testing...\n";
    // standard approaches
    StandardSorter sd;
    // Quick sort
    std::cout<<"Quick sort...\n";
    std::string name = "Standard Quick sort";
    test_sort(random_strings,
              [ObjectPtr = &sd](auto &&PH1) { return ObjectPtr->QuickSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, random_strings_name);
    test_sort(nearly_sorted_strings,
              [ObjectPtr = &sd](auto &&PH1) { return ObjectPtr->QuickSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, nearly_sorted_strings_name);
    test_sort(reverse_sorted_strings,
              [ObjectPtr = &sd](auto &&PH1) { return ObjectPtr->QuickSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, reverse_sorted_strings_name);
    // Merge sort
    name = "Standard Merge sort";
    std::cout<<"Merge sort...\n";
    test_sort(random_strings,
              [ObjectPtr = &sd](auto &&PH1) { return ObjectPtr->MergeSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, random_strings_name);
    test_sort(nearly_sorted_strings,
              [ObjectPtr = &sd](auto &&PH1) { return ObjectPtr->MergeSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, nearly_sorted_strings_name);
    test_sort(reverse_sorted_strings,
              [ObjectPtr = &sd](auto &&PH1) { return ObjectPtr->MergeSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, reverse_sorted_strings_name);
    std::cout<<"Finished standard sorts testing!\n";
};

void process_test_for_special_sorter(
        std::vector<std::string> random_strings,
        std::vector<std::string> nearly_sorted_strings,
        std::vector<std::string> reverse_sorted_strings,
        std::ofstream& resultsFile)
{
    std::cout<<"Started special sorts testing...\n";
    // special approaches
    SpecialSorter ss;
    // string Quick sort
    std::string name = "Special Quick sort";
    std::cout<<"String quick sort...\n";
    test_sort(random_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->StringQuickSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, random_strings_name);
    test_sort(nearly_sorted_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->StringQuickSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, nearly_sorted_strings_name);
    test_sort(reverse_sorted_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->StringQuickSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, reverse_sorted_strings_name);

    // string Merge sort
    std::cout<<"String merge sort...\n";
    name = "Special Merge sort";
    test_sort(random_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->StringMergeSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, random_strings_name);
    test_sort(nearly_sorted_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->StringMergeSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, nearly_sorted_strings_name);
    test_sort(reverse_sorted_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->StringMergeSort(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, reverse_sorted_strings_name);

    // MSD without QS
    name = "MSD";
    std::cout<<"MSD...\n";
    test_sort(random_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->MSDWithoutQS(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, random_strings_name);
    test_sort(nearly_sorted_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->MSDWithoutQS(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, nearly_sorted_strings_name);
    test_sort(reverse_sorted_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->MSDWithoutQS(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, reverse_sorted_strings_name);

    // MSD with QS
    name = "MSD+QS";
    std::cout<<"MSD with Quick sort...\n";
    test_sort(random_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->MSDWithQS(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, random_strings_name);
    test_sort(nearly_sorted_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->MSDWithQS(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, nearly_sorted_strings_name);
    test_sort(reverse_sorted_strings,
              [ObjectPtr = &ss](auto &&PH1) { return ObjectPtr->MSDWithQS(std::forward<decltype(PH1)>(PH1)); },
              name, resultsFile, reverse_sorted_strings_name);
    std::cout<<"Finished special sorts testing!\n";
}

int main() {
    // configure file for results
    std::ofstream resultsFile("D:/HSECourse2/sort_results.csv");
    resultsFile<< "Sort Name,Array Name, Array Size, Time, Comparisons\n";

    // generate data for testing
    StringGenerator generator;
    const size_t size = 3000;
    auto random_strings = generator.generateReverseSortedStrings(size);
    auto nearly_sorted_strings = generator.generateNearlySortedStrings(size);
    auto reverse_sorted_strings = generator.generateReverseSortedStrings(size);

    process_test_for_standard_sorter(random_strings, nearly_sorted_strings, reverse_sorted_strings, resultsFile);
    process_test_for_special_sorter(random_strings, nearly_sorted_strings, reverse_sorted_strings, resultsFile);

//    SpecialSorter ss;
//    std::vector<std::string> test = {"!", "Yieifeijefiei", "DF", "FD", "A", "RD", "B" };
//    ss.MSDSort(test, true);
//    for(const auto & str: test)
//        std::cout<<str<<" ";

    resultsFile.close();
    std::cout<<"Results are written to sort_results.csv\n";
    return 0;
};