#ifndef DELYNOI_FUNCTOR_H
#define DELYNOI_FUNCTOR_H

/*
 * Abstract class with a similar meaning as a lambda function or function pointer.
 */
class Functor {
public:
    /*
     * Applies the function on a number
     * @param x parameter of the function
     * @return value of the function with the given parameter
     */
    virtual double apply(double x) = 0;
};


#endif 
