#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <raylib/raylib.h>
#include <defines.h>

class Utils {
public:

    static void removeCommentAndTrim(std::string& line) {
        std::size_t pos = line.find("//");

        if (pos != std::string::npos) {
            line = line.substr(0, pos);
        }

        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), line.end());
    }

    static void extractDigits(int number, std::vector<int>& result, std::size_t minSize, int paddingValue) {
        std::string numStr = std::to_string(number);

        for (char c : numStr) {
            result.push_back(c - '0');
        }

        std::size_t zerosToAdd = minSize > result.size() ? minSize - result.size() : 0;

        result.insert(result.begin(), zerosToAdd, paddingValue);
    }

};

#endif // UTILS_H
