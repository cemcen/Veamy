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

/*
 * Namespace containing functions that are common enough, and not related to any modeling per se, to be reused for
 * all libraries
 */
namespace utilities{
    /* Returns the string representation of a value
     * @param a value to transform
     * @return string representation of a
     */
    template <typename T>
    std::string toString(T a){
        std::stringstream sstream;
        sstream << a;
        std::string s = sstream.str();

        return s;
    }

    /* Returns the index of an element in a vector
     * @param vector vector of elements
     * @param element element to lookup
     * @return index of element (-1 if not contained)
     */
    template <typename T>
    int indexOf(std::vector<T> vector, T element){
        int pos = std::find(vector.begin(), vector.end(), element) - vector.begin();

        return pos < (int) vector.size()? pos : -1;
    }

    /*
     * @param x value
     * @return the sign of the given value (-1 or 1)
     */
    template <typename T>
    int sign(T x){
        return (x > 0) - (x < 0);
    }

    /* Returns the string representation of a double number with a given number of decimals
     * @param d double to transform to string
     * @param precision number of decimals to print
     * @return string representation of a
     */
    extern std::string toStringWithPrecision(double d, int precision);

    /* Computes a hash value for an integer
     * @param key number
     * @return hash value of key
     */
    extern int hash32(int key);

    /* Creates a random integer number in an interval
     * @param min minimum value of the interval
     * @param max maximum value of the interval
     * @return created number
     */
    extern int random_integer(int min, int max);

    /* Obtains the home path of the current machine (depending on operating system)
     * @return home path
     */
    extern std::string getPath();

    /* Receives a vector and normalizes it (modifies it so that its norm is unitary)
     * @param vector vector to normalize
     * @return normalized vector
     */
    extern Pair<double> normalize(Pair<double> vector);

    /* Transforms an angle in degrees to radians
     * @param angle angle in degrees
     * @return same angle in radians
     */
    extern double radian(double angle);

    /* Transforms an angle in radians to degrees
     * @param angle angle in radians
     * @return same angle in degrees
     */
    extern double degrees(double angle);

    /* Splits a string using a regular expression (similar to a tokenizer)
     * @param s string to split
     * @param regex regular expression used to split
     * @return list of tokens obtained from s
     */
    extern std::vector<std::string> split(std::string s, const std::regex regex);

    /* Splits a string by spaces
     * @param s string to split
     * @return list of tokens obtained from s
     */
    extern std::vector<std::string> splitBySpaces(std::string s);

    /* Opens a text file, throwing an error if the file is not found
     * @param fileName name of the file to open
     * @return stream used to read the file
     */
    extern std::ifstream openFile(std::string fileName);
}

#endif 
