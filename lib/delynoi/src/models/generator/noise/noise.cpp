#include <delynoi/models/generator/noise/RandomDoubleNoise.h>
#include <delynoi/models/generator/Functor.h>
#include <delynoi/models/generator/noise/RandomIntegerNoise.h>

namespace noise{
    Functor* random_double_noise(Functor* f, double min, double max){
        return new RandomDoubleNoise(f, min, max);
    }

    Functor* random_integer_noise(Functor* f, int min, int max){
        return new RandomIntegerNoise(f, min, max);
    }
}
