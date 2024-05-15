//
// Created by alexe on 07.05.2024.
//
#include "StandardSorter.h"

int StandardSorter::QuickSort(std::vector<std::string> &vec) {
    characterComparisons = 0;
    quick_sort(vec, 0, vec.size() - 1);
    int res = characterComparisons;
    characterComparisons = 0;
    return res;
}

int StandardSorter::MergeSort(std::vector<std::string> &vec) {
    characterComparisons = 0;
    merge_sort(vec, 0, vec.size() - 1);
    int res = characterComparisons;
    characterComparisons = 0;
    return res;
}

void StandardSorter::quick_sort(std::vector<std::string> &arr, int low, int high) {
    if(low < high){
        int pivot_index = partition(arr, low, high);
        quick_sort(arr, low, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, high);
    }
}

int StandardSorter::partition(std::vector<std::string> &arr, int low, int high) {
    //choose the pivot
    std::string pivot=arr[high];
    int i = low - 1;
    for(int j=low;j<=high;j++)
    {
        if(compareStrings(arr[j],pivot) < 0)
        {
            i++;
            std::swap(arr[i],arr[j]);
        }
    }
    std::swap(arr[i+1],arr[high]);
    return i + 1;
}

int StandardSorter::compareStrings(const std::string &s1, const std::string &s2) {
    int minLen = std::min(s1.length(), s2.length());
    for(int i = 0; i < minLen; ++i){
        ++characterComparisons;
        if(s1[i] != s2[i]){
            return s1[i] < s2[i] ? -1 : 1;
        }
    }
    ++characterComparisons;
    return s1.length() < s2.length() ? -1 : (s1.length() > s2.length() ? 1 : 0);
}

void StandardSorter::merge_sort(std::vector<std::string> &arr, size_t min, size_t max) {
    if(max == min)
        return;
    size_t mid = (max + min) >> 1;

    merge_sort(arr, min, mid);
    merge_sort(arr, mid + 1, max);

    merge(arr, min, max, mid);
}

void StandardSorter::merge(std::vector<std::string> &arr, size_t min, size_t max, size_t mid) {
    size_t firstIndex = min;
    size_t secondIndex = mid + 1;

    std::vector<std::string> tempArray(max - min + 1);
    for (size_t index = min; index <= max; index++) {
        if (firstIndex <= mid && (secondIndex > max || compareStrings(arr[firstIndex], arr[secondIndex]) <= 0)){
            tempArray[index - min] = arr[firstIndex++];
        } else {
            tempArray[index - min] = arr[secondIndex++];
        }
    }

    // transfer to the initial array
    for(size_t i = min; i <= max; ++i)
        arr[i] = tempArray[i - min];
}