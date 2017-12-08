#ifndef DELYNOI_RANDOMDOUBLE_H
#define DELYNOI_RANDOMDOUBLE_H

#include <random>
#include "delynoi/models/generator/Functor.h"

/*
 * Generates random double numbers.
 */
class Random_Double : public Functor {
public:
    /*
    * Parameters for the number generation. Maximum and minimum possible values.
    */
    double min;
    double max;

    /*
   * Parameters for random double number generation.
   */
    static std::default_random_engine rd;
    static std::mt19937 rng;
    std::uniform_real_distribution<double> uni;

    /*
     * Constructor.
     */
    Random_Double(double min, double max);

    /*
    * Applies the function (as this is random generation, the result does not use the argument).
    * @param x argument of the function
    * @return function result
    */
    double apply(double x);
};


#endif