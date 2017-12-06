#include <delynoi/models/generator/noise/RandomDoubleNoise.h>

std::default_random_engine RandomDoubleNoise::rd;
std::mt19937 RandomDoubleNoise::rng(rd());

RandomDoubleNoise::RandomDoubleNoise(Functor *f, double min, double max) {
    this->min = min;
    this->max = max;
    this->f = f;

    this->uni = std::uniform_real_distribution<double>(min,max);
    this->uni_int = std::uniform_int_distribution<int>(INT_MIN+100000,INT_MAX-100000);
}

double RandomDoubleNoise::apply(double x) {
    return f->apply(x) + (uni)(this->rng) * ((uni_int)(this->rng)%2? 1 : -1);
}
