//
// Created by alexe on 07.05.2024.
//
#ifndef ALGOHWS_STRINGGENERATOR_H
#define ALGOHWS_STRINGGENERATOR_H

#include <vector>
#include <string>
#include <random>
#include <algorithm>

class StringGenerator {
public:
    StringGenerator(double percent = 0.1);
    std::vector<std::string> generateRandomStrings(size_t count);
    std::vector<std::string> generateReverseSortedStrings(size_t count);
    std::vector<std::string> generateNearlySortedStrings(size_t count);

private:
    std::string alphabet = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789!@#%:;^&*()-";
    std::mt19937 rng;
    std::uniform_int_distribution<size_t> len_distribution;
    std::uniform_int_distribution<size_t> char_distribution;
    double unsorted_percent;
    std::string generateRandomString();
};
#endif //ALGOHWS_STRINGGENERATOR_H
