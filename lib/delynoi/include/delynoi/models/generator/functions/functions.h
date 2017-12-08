#ifndef DELYNOI_FUNCTIONS_H
#define DELYNOI_FUNCTIONS_H

#include "delynoi/models/generator/Functor.h"

/*
 * Namespace with all generator functions definitions.
 */
namespace functions {
    /*
     * Defines the different options for the Fucntion classes variables.
     */
    enum independent_variable{x, y, both};

    /* Creates a class that given a coordinate, returns the same value.
     * @return an instance of a Constant class.
     */
    Functor* constant();

    /* Creates a class that given a coordinate, displace every even point the given value.
     * @param delta value to displace the points
     * @return an instance of a DisplacePoints class.
     */
    Functor* displace_points(double delta);

    /* Creates a class that given a coordinate, returns all the first batch constant, and the second displaced
     * by half the difference between the elements of the first batch.
     * @return an instance of the ConstantAlternating class
     */
    Functor *constantAlternating();

    /* Creates a class that given a coordinate, it multiplies its value by delta.
     * @param delta value to multiplicate each coordinate
     * @return an instance of the Uniform class
     */
    Functor* uniform(double delta);

    /* Creates a class that generates random integer numbers in the interval (min,max)
     * @param min minimum value to generate
     * @param max maximum value to generate
     * @return an instance of the RandomInteger class
     */
    Functor* random_integer(double min, double max);

    /* Creates a class that generates random double numbers in the interval (min,max)
     * @param min minimum value to generate
     * @param max maximum value to generate
     * @return an instance of the RandomDouble class
     */
    Functor* random_double(double min, double max);

    /* Creates a class that generates number following a sine curve, of the form amplitude*sin(frecuency*value + phase)
     * @param amplitude amplitude value of the function
     * @param frecuency frecuency value
     * @param phase value
     * @return an instance of the Sine class
     */
    Functor* sine(double amplitude, double frecuency, double phase);

    /* Creates a class that generates number following a cosine curve, of the form amplitude*cos(frecuency*value + phase)
    * @param amplitude amplitude value of the function
    * @param frecuency frecuency value
    * @param phase value
    * @return an instance of the Cosine class
    */
    Functor* cosine(double amplitude, double frecuency, double phase);
}

#endif
