//
// Created by alexe on 07.05.2024.
//
#include "StringGenerator.h"

StringGenerator::StringGenerator(double percent) :
        rng(std::random_device{}()),
        len_distribution(10, 200),
        char_distribution(0, alphabet.size() - 1),
        unsorted_percent(percent) {}


std::vector<std::string> StringGenerator::generateRandomStrings(size_t count) {
    std::vector<std::string> result(count);
    for (size_t i = 0; i < count; ++i)
        result[i] = generateRandomString();
    return result;
}

std::vector<std::string> StringGenerator::generateReverseSortedStrings(size_t count) {
    std::vector<std::string> result = generateRandomStrings(count);
    std::sort(result.begin(), result.end(), std::greater());
    return result;
}

std::vector<std::string> StringGenerator::generateNearlySortedStrings(size_t count) {
    std::vector<std::string> strings = generateRandomStrings(count);
    std::sort(strings.begin(), strings.end());
    auto swapCnt = (size_t) (count * unsorted_percent);
    std::uniform_int_distribution<size_t> index_dist(0, count - 1);
    for (size_t i = 0; i < swapCnt; ++i) {
        std::swap(strings[index_dist(rng)], strings[index_dist(rng)]);
    }
    return strings;
}

std::string StringGenerator::generateRandomString() {
    size_t len = len_distribution(rng);
    std::string result;
    result.reserve(len);
    for (size_t i = 0; i < len; ++i) {
        result += alphabet[char_distribution(rng)];
    }
    return result;
};