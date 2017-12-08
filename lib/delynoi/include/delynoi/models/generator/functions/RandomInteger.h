#ifndef DELYNOI_RANDOMINTEGER_H
#define DELYNOI_RANDOMINTEGER_H

#include <random>
#include "delynoi/models/generator/Functor.h"

/*
 * Generates random integer numbers.
 */
class Random_Integer : public Functor {
private:
    /*
    * Parameters for the number generation. Maximum and minimum possible values.
    */
    double min;
    double max;

    /*
  * Parameters for random integer number generation.
  */
    static std::default_random_engine rd;
    static std::mt19937 rng;
    std::uniform_int_distribution<int> uni;
public:
    /*
     * Constructor.
     */
    Random_Integer(double min, double max);

    /*
   * Applies the function (as this is random generation, the result does not use the argument).
   * @param x argument of the function
   * @return function result
   */
    double apply(double x);
};


#endif