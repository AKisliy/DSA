//
// Created by alexe on 09.05.2024.
//
#include "SpecialSorter.h"

// -------------------------String Quick Sort-----------------------------------------

int SpecialSorter::StringQuickSort(std::vector<std::string> &vec) {
    characterComparisons = 0;
    quick_sort(vec, 0, 0, vec.size() - 1);
    int result = characterComparisons;
    characterComparisons = 0;
    return result;
}

void SpecialSorter::quick_sort(std::vector<std::string> &arr, int k, int low, int high) {
    if(high - low <= 0)
        return;
    std::vector<int> borders = partition(arr, low, high, k);
    int newLow = borders[0];
    int equalStart = borders[1];
    int equalEnd = borders[2];
    quick_sort(arr, k, newLow, equalStart - 1); // sort lower
    quick_sort(arr, k + 1, equalStart, equalEnd);
    quick_sort(arr, k, equalEnd + 1, high); // sort higher
}

std::vector<int> SpecialSorter::partition(std::vector<std::string> &arr, int low, int high, int k) {
    int index = low;
    for(int i = low; i <= high; ++i){
        if(arr[i].size() == k) // move words with len == k to the beginning
            std::swap(arr[i], arr[index++]);
    }
    char pivot = arr[high][k];
    low = index;
    int j = index;

    while(j <= high){
        characterComparisons += 2;
        if(arr[j][k] < pivot){
            std::swap(arr[low++], arr[j++]);
            --characterComparisons;
        } else if(arr[j][k] > pivot){
            std::swap(arr[j], arr[high--]);
        } else {
            ++j;
        }
    }
    return {index, low, high};
}
// -----------------------------------------------------------------------------------


// -------------------------String Merge Sort-----------------------------------------

int SpecialSorter::StringMergeSort(std::vector<std::string> &vec) {
    characterComparisons = 0;
    int n = vec.size();
    std::vector<StringForMerge> v;
    v.reserve(n);
    for(int i = 0; i < n; ++i){
        v.emplace_back(vec[i], 0);
    }
    merge_sort(v, 0, n - 1);
    for(int i = 0; i < n; ++i){
        vec[i] = v[i].str;
    }
    int result = characterComparisons;
    characterComparisons = 0;
    return result;
}

void SpecialSorter::merge_sort(std::vector<StringForMerge> &arr, int low, int high) {
    if(low >= high)
        return;
    int mid = (low + high) >> 1;

    merge_sort(arr, low, mid);
    merge_sort(arr, mid + 1, high);

    merge(arr, low, high, mid);
}

void SpecialSorter::merge(std::vector<StringForMerge> &arr, int low, int high, int mid) {
    int firstIndex = low;
    int secondIndex = mid + 1;

    std::vector<StringForMerge> tempArray(high - low + 1);
    for (size_t index = low; index <= high; index++) {
        if (firstIndex <= mid && (secondIndex > high || arr[firstIndex].k > arr[secondIndex].k)){
            tempArray[index - low] = arr[firstIndex++];
        } else if(secondIndex <= high && (firstIndex > mid || arr[firstIndex].k < arr[secondIndex].k)) {
            tempArray[index - low] = arr[secondIndex++];
        } else {
            auto pair = lcpCompare(arr[firstIndex].str, arr[secondIndex].str, arr[firstIndex].k);
            if(pair.first < 0){
                tempArray[index - low] = arr[firstIndex++];
                arr[secondIndex].k = pair.second;
            } else{
                tempArray[index - low] = arr[secondIndex++];
                arr[firstIndex].k = pair.second;
            }
        }
    }

    for(int i = low; i <= high; ++i){
        arr[i] = tempArray[i - low];
    }
}

std::pair<int, int> SpecialSorter::lcpCompare(const std::string &s1, const std::string &s2, int k) {
    int i = k;
    int n = s1.length();
    int m = s2.length();
    int minLen = std::min(n,m);
    for(; i < minLen; ++i){
        ++characterComparisons;
        if(s1[i] != s2[i])
            break;
    }
    if(i == minLen && n < m)
        return {-1, i};
    else if(i == minLen && n > m)
        return {1, i};
    else if(i == minLen && n == m)
        return {0, i};
    return s1[i] < s2[i] ? std::make_pair(-1, i) : (s1[i] > s2[i] ? std::make_pair(1, i) : std::make_pair(0, i));
}

// ---------------------------------------------------------------------------------------

// -------------------------MSD Radix Sort------------------------------------------------

int SpecialSorter::MSDWithQS(std::vector<std::string> &vec) {
    return MSDSort(vec, true);
}

int SpecialSorter::MSDWithoutQS(std::vector<std::string> &vec) {
    return MSDSort(vec, false);
}

int SpecialSorter::MSDSort(std::vector<std::string> &vec, bool switchToQuick) {
    int n = vec.size();
    std::vector<std::string> temp(n);
    characterComparisons = 0;
    msd(vec, 0, n - 1, 0, switchToQuick, temp);
    int res = characterComparisons;
    characterComparisons = 0;
    return res;
}

void SpecialSorter::msd(std::vector<std::string> &arr, int low, int high, int d, bool switchToQuick, std::vector<std::string> &temp) {
    if(switchToQuick && high - low < ALPHABET_SIZE - 1) {
        quick_sort(arr, d, low, high);
        return;
    }
    if(low >= high)
        return;
    std::vector<int> count(R + 2, 0);
    for(int i = low; i <= high; ++i){
        int c = charAt(arr[i], d);
        ++count[c + 2];
    }
    for(int r = 0; r < R + 1; ++r)
        count[r + 1] += count[r];

    for (int i = low; i <= high; ++i) {
        int c = charAt(arr[i], d);
        temp[count[c+1]++] = arr[i];
    }

    for (int i = low; i <= high; i++)
        arr[i] = temp[i - low];

    for (int r = 1; r < R + 1; r++)
        msd(arr, low + count[r], low + count[r+1] - 1, d+1, switchToQuick, temp);
}

int SpecialSorter::charAt(std::string &s, int d) {
    if(d == s.length()) return -1;
    return s[d] - '!';
}

int SpecialSorter::compareStrings(const std::string &s1, const std::string &s2) {
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

