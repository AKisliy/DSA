//
// Created by alexe on 07.05.2024.
//
#ifndef ALGOHWS_STANDARDSORTER_H
#define ALGOHWS_STANDARDSORTER_H

#include <iostream>
#include <vector>
#include <string>

class StandardSorter {
public:
    int characterComparisons = 0;
    int QuickSort(std::vector<std::string>& vec);
    int MergeSort(std::vector<std::string>& vec);
private:
    void quick_sort(std::vector<std::string>& arr,int low,int high);
    void merge_sort(std::vector<std::string>& arr,size_t min, size_t max);
    void merge(std::vector<std::string>& arr,size_t min, size_t max, size_t mid);
    int partition(std::vector<std::string>& arr,int low,int high);
    int compareStrings(const std::string& s1, const std::string& s2);
};
#endif //ALGOHWS_STANDARDSORTER_H
