//
// Created by alexe on 09.05.2024.
//
#ifndef ALGOHWS_SPECIALSORTER_H
#define ALGOHWS_SPECIALSORTER_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>

struct StringForMerge{
public:
    std::string str;
    int k;

    StringForMerge(std::string s, int k): str(std::move(s)), k(k){}
    StringForMerge(): k(0) {}
};

class SpecialSorter {
public:
    int characterComparisons = 0;
    int StringQuickSort(std::vector<std::string>& vec);
    int StringMergeSort(std::vector<std::string>& vec);
    int MSDWithoutQS(std::vector<std::string>& vec);
    int MSDWithQS(std::vector<std::string>& vec);
    int MSDSort(std::vector<std::string>& vec, bool switchToQuick);
private:
    const int ALPHABET_SIZE = 74;
    const int R = 134;

    void quick_sort(std::vector<std::string>& arr,int k, int low,int high);
    std::vector<int> partition(std::vector<std::string>& arr,int low,int high,int k);

    void merge_sort(std::vector<StringForMerge>& arr, int low, int high);
    void merge(std::vector<StringForMerge>& arr, int low, int high, int mid);
    std::pair<int, int> lcpCompare(const std::string& s1, const std::string& s2, int k);

    void msd(std::vector<std::string>& arr, int low, int high, int d, bool switchToQuick, std::vector<std::string> &temp);
    int charAt(std::string& s, int d);

    int compareStrings(const std::string& s1, const std::string& s2);
};
#endif //ALGOHWS_SPECIALSORTER_H
