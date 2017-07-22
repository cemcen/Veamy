#include <mesher/models/generator/Functor.h>
#include <mesher/models/generator/RandomDouble.h>
#include <mesher/models/generator/RandomInteger.h>
#include "FunctorClasses.cpp"

namespace functions {
    Functor *constant() {
        return new Uniform(1.0);
    }

    Functor *constantAlternating() {
        return new ConstantAlternating();
    }

    Functor *uniform(double delta) {
        return new Uniform(delta);
    }

    Functor *sine(double amplitude, double frecuency, double phase) {
        return new Sine(amplitude, frecuency, phase);
    }

    Functor *cosine(double amplitude, double frecuency, double phase) {
        return new Cosine(amplitude, frecuency, phase);
    }

    Functor *random_integer(double min, double max){
        return new Random_Integer(min, max);
    }

    Functor *random_double(double min, double max){
        return new Random_Double(min, max);
    }
}



