#ifndef UTILITIES_UTILITIES_H
#define UTILITIES_UTILITIES_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Pair.h"
#include <iomanip>
#include <regex>
#include <string>

namespace utilities{
    template <typename T>
    std::string toString(T a){
        std::stringstream sstream;
        sstream << a;
        std::string s = sstream.str();

        return s;
    }

    template <typename T>
    int indexOf(std::vector<T> vector, T element){
        int pos = std::find(vector.begin(), vector.end(), element) - vector.begin();

        return pos < (int) vector.size()? pos : -1;
    }

    template <typename T>
    int sign(T x){
        return (x > 0) - (x < 0);
    }

    extern std::string toStringWithPrecision(double d, int precision);
    extern int hash32(int key);
    extern int random_integer(int min, int max);
    extern std::string getPath();
    extern Pair<double> normalize(Pair<double> vector);
    extern double radian(double angle);
    extern double degrees(double angle);
    extern std::vector<std::string> split(std::string s, const std::regex regex);
    extern std::vector<std::string> splitBySpaces(std::string s);
    extern std::ifstream openFile(std::string fileName);
}

#endif 
