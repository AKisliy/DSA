#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <chrono>

void generateTest(std::vector<int>& vec,size_t size);
size_t generateIndex(size_t size, size_t subarray);
void small_shuffle(std::vector<int>& vec, size_t inversions);


void heapify(std::vector<int>& arr, int heapSize, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    // looking for the largest "son"
    if ((left < heapSize) && (arr[left] > arr[largest]))
        largest = left;
    if (right < heapSize && arr[right] > arr[largest])
        largest = right;
    // if "parent" is less than son - swap them and then repeat(maybe "parent" is less than "son of son")
    if (largest != index)
    {
        std::swap(arr[index], arr[largest]);
        heapify(arr, heapSize, largest);
    }
}

void build_heap(std::vector<int>& arr){
    // making a heap
    for (int i = arr.size() / 2 - 1; i >= 0; --i)
        heapify(arr, arr.size(), i);
}

void heap_sort(std::vector<int>& arr, size_t min, size_t max)
{
    // making a heap
    build_heap(arr);
    for (int i = max - 1; i > min; --i)
    {
        //placing the largest element on the top
        std::swap(arr[i],arr[0]);
        // reorder our heap to maintain heap-order
        heapify(arr, i, 0);
    }
}



int partition(std::vector<int>& arr,int low,int high)
{
    //choose the pivot
    int pivot=arr[high];
    int i=(low-1);
    for(int j=low;j<=high;j++)
    {
        if(arr[j]<pivot)
        {
            i++;
            std::swap(arr[i],arr[j]);
        }
    }
    std::swap(arr[i+1],arr[high]);
    return (i+1);
}

void quick_sort(std::vector<int>& arr,int low,int high)
{
    if(low<high)
    {
        int pivot_index=partition(arr, low, high);
        quick_sort(arr, low, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, high);
    }
}



void quick_heap(std::vector<int>& array, size_t min, size_t max, size_t threshold){
    if ((max - min) <= threshold) {
        heap_sort(array, min, max);
    } else {
        int pivot_index = partition(array, min, max);
        quick_sort(array, min, pivot_index - 1);
        quick_sort(array, pivot_index + 1, max);
    }
}

void start_testing_quick_heap(std::vector<int>& test_array){
    std::cout<<"Quick+heap test:";
    std::vector<int> thresholds{5,10,20,50};

    for(int threshold: thresholds) {
        std::cout<<"Threshold = "<<threshold<<'\n';
        for (int size = 500; size <= 4000; size += 100) {
            size_t start = generateIndex(test_array.size(), size);
            std::vector<int> sub_vec(test_array.begin() + start, test_array.begin() + start + size);
            auto time = std::chrono::high_resolution_clock::now();
            quick_heap(sub_vec, 0, size - 1, threshold);
            auto elapsed = std::chrono::high_resolution_clock::now() - time;
            long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            std::cout << "(" << size << "," << millisec << "),";
        }
        std::cout<<'\n';
    }
}

void start_testing_quick(std::vector<int>& test_array) {
    std::cout<<"Quick test:"<<'\n';
    for (int size = 500; size <= 4000; size += 100) {
        size_t start = generateIndex(test_array.size(), size);
        std::vector<int> sub_vec(test_array.begin() + start, test_array.begin() + start + size);
        auto time = std::chrono::high_resolution_clock::now();
        quick_sort(sub_vec, 0, size - 1);
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

    start_testing_quick(test1);
    start_testing_quick(test2);
    start_testing_quick(test3);

    start_testing_quick_heap(test1);
    start_testing_quick_heap(test2);
    start_testing_quick_heap(test3);

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
        std::swap(vec[firstIndex], vec[secondIndex]);
        --inversions;
    }
}
