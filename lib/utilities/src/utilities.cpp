#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>
#include <utilities/Pair.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include <math.h>
#include <vector>
#include <iomanip>
#include <fstream>
#include <regex>


namespace utilities {
    std::string toStringWithPrecision(double d, int precision){
        std::stringstream sstream;
        sstream << std::fixed << std::setprecision(precision);
        sstream << d;
        std::string s = sstream.str();

        return s;
    }

    int random_integer(int min, int max){
        static std::random_device rd;
        static std::mt19937 rng (rd());
        std::uniform_int_distribution<int> uni(min,max);

        return uni(rng);
    }

    std::string getPath(){
        #if defined(_WIN64) || defined(_WIN32)
                std::string path = std::getenv("USERPROFILE");
                return  path + "\\";
        #elif defined(__linux__)
                std::string path = std::getenv("HOME");
                return path + "/";
        #endif
    }

    Pair<double> normalize(Pair<double> vector){
        double norm = std::sqrt(std::pow(vector.first,2) + std::pow(vector.second,2));

        return Pair<double>(vector.first/norm, vector.second/norm);
    }

    double radian(double angle){
        return angle*M_PI/180;
    }

    double degrees(double angle){
        double a = (angle > 0 ? angle : (2*M_PI + angle));

        return a* 180/ (M_PI);
    }

    int hash32(int key) {
        int c2=0x27d4eb2d;
        key = (key ^ 61) ^ (key >> 16);
        key = key + (key << 3);
        key = key ^ (key >> 4);
        key = key * c2;
        key = key ^ (key >> 15);
        return key;
    }

    std::vector<std::string> split(std::string s, const std::regex regex) {
        std::vector<std::string> result;

        std::sregex_token_iterator it(s.begin(), s.end(), regex, -1 );
        std::sregex_token_iterator reg_end;

        for ( ; it != reg_end; ++it ) {
            if (!it->str().empty())
                result.emplace_back( it->str());
        }

        return result;
    }

    std::vector<std::string> splitBySpaces(std::string s) {
        return utilities::split(s, std::regex("\\s+"));
    }

    std::ifstream openFile(std::string fileName){
        std::string completeName = utilities::getPath() + fileName;
        std::ifstream infile(completeName);

        if(!infile.good()){
            throw std::runtime_error("Could not open file. Please check path.");
        }

        return infile;
    }
}


