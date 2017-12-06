#include <delynoi/models/generator/noise/RandomIntegerNoise.h>

std::default_random_engine RandomIntegerNoise::rd;
std::mt19937 RandomIntegerNoise::rng(rd());

RandomIntegerNoise::RandomIntegerNoise(Functor *f, double min, double max) {
    this->min = min;
    this->max = max;
    this->f = f;
    this->uni = std::uniform_int_distribution<int>(min,max);
}

double RandomIntegerNoise::apply(double x) {
    return f->apply(x) + (uni)(this->rng) * ((uni)(this->rng)%2? 1 : -1);
}
