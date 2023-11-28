#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <chrono>

void generateTest(std::vector<int>& vec,size_t size);
size_t generateIndex(size_t size, size_t subarray);
void small_shuffle(std::vector<int>& vec, size_t inversions);


void InsertionSort(std::vector<int>& A,size_t start,size_t end){
    size_t i = 0, j = 0;
    for (i = start; i <= end; i++) {
        int temp = A[i];
        for (j = i; j > start && temp < A[j - 1]; --j) {
               A[j] = A[j - 1];
        }
        A[j] = temp;
    }
}

void merge(std::vector<int>& array,size_t min,size_t max,size_t mid){
    size_t firstIndex = min;
    size_t secondIndex = mid + 1;

    std::vector<int> tempArray(max - min + 1);
    for (size_t index = min; index <= max; index++) {
        if (firstIndex <= mid && (secondIndex > max || array[firstIndex] <= array[secondIndex])){
            tempArray[index - min] = array[firstIndex++];
        } else {
            tempArray[index - min] = array[secondIndex++];
        }
    }

    // transfer to the initial array
    for(size_t i = min; i <= max; ++i)
        array[i] = tempArray[i - min];
}

void merge_sort(std::vector<int>& array, size_t min, size_t max){
    if(max == min)
        return;
    size_t mid = (max + min) >> 1;

    merge_sort(array, min, mid);
    merge_sort(array, mid + 1, max);

    merge(array, min, max, mid);
}



void merge_insertion(std::vector<int>& array, size_t min, size_t max, size_t threshold){
    if ((max - min) <= threshold) {
        InsertionSort(array, min, max);
    } else {
        size_t mid = (max + min) >> 1;

        merge_insertion(array, min, mid, threshold);
        merge_insertion(array, mid + 1, max, threshold);

        merge(array, min, max, mid);
    }
}

void start_testing_merge_insertion(std::vector<int>& test_array){
    std::cout<<"Merge+insertion test:";
    std::vector<int> thresholds{5,10,20,50};

    for(int threshold: thresholds) {
        std::cout<<"Threshold = "<<threshold<<'\n';
        for (int size = 500; size <= 4000; size += 100) {
            size_t start = generateIndex(test_array.size(), size);
            std::vector<int> sub_vec(test_array.begin() + start, test_array.begin() + start + size);
            auto time = std::chrono::high_resolution_clock::now();
            merge_insertion(sub_vec, 0, size - 1, threshold);
            auto elapsed = std::chrono::high_resolution_clock::now() - time;
            long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            std::cout << "(" << size << "," << millisec << "),";
        }
        std::cout<<'\n';
    }
}

void start_testing_merge(std::vector<int>& test_array) {
    std::cout<<"Merge test:"<<'\n';
    for (int size = 500; size <= 4000; size += 100) {
        size_t start = generateIndex(test_array.size(), size);
        std::vector<int> sub_vec(test_array.begin() + start, test_array.begin() + start + size);
        auto time = std::chrono::high_resolution_clock::now();
        merge_sort(sub_vec, 0, size - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - time;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "(" << size << "," << millisec << "),";
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> test1;
    std::vector<int> test2;
    std::vector<int> test3;

    // random elements
    generateTest(test1, 4000);

    // non-ascending order
    generateTest(test2, 4000);
    std::sort(test2.begin(), test2.end(), std::greater<>());

    // small count of inversions
    generateTest(test3, 4000);
    std::sort(test3.begin(), test3.end());
    small_shuffle(test3, test3.size() / 10);

    start_testing_merge(test1);
    start_testing_merge(test2);
    start_testing_merge(test3);

    start_testing_merge_insertion(test1);
    start_testing_merge_insertion(test2);
    start_testing_merge_insertion(test3);

    return 0;
}

void generateTest(std::vector<int>& vec, size_t size){
    std::random_device dev;
    std::default_random_engine generator(dev());
    std::uniform_int_distribution<int> distribution(0, 3000);
    auto dice = std::bind(distribution, generator);
    for(size_t i = 0; i < size; ++i)
        vec.push_back(dice());
}

size_t generateIndex(size_t size, size_t subarray){
    std::random_device dev;
    std::default_random_engine generator(dev());//(std::time(&t)));
    std::uniform_int_distribution<int> distribution(0, size - subarray);
    auto dice = std::bind(distribution, generator);
    int index = dice();
    return index;
}

void small_shuffle(std::vector<int>& vec, size_t inversions){
    while(inversions){
        size_t firstIndex = generateIndex(vec.size(), 1);
        size_t secondIndex = generateIndex(vec.size(), 1);
//        while(secondIndex == firstIndex)
//            secondIndex = generateIndex(vec.size(), 1);
        std::swap(vec[firstIndex], vec[secondIndex]);
        --inversions;
    }
}
