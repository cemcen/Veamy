#ifndef DELYNOI_NOISE_H
#define DELYNOI_NOISE_H

#include <delynoi/models/generator/Functor.h>

namespace noise {
    Functor *random_double_noise(Functor *f, double min, double max);
    Functor *random_integer_noise(Functor *f, double min, double max);
}

#endif