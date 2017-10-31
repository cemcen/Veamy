#ifndef UTILITIES_TRIO_H
#define UTILITIES_TRIO_H

template <typename T>
class Trio {
    T first;
    T second;
    T third;

    Trio(T f, T s, T t);
    Trio(const Trio& other);
    Trio();

    bool operator==(const Trio& other) const;
};

template <typename T>
Trio<T>::Trio(T f, T s, T t) {
    this->first = f;
    this->second = s;
    this->third = t;
}

template <typename T>
Trio<T>::Trio(const Trio &other) {
    this->first = other.first;
    this->second = other.second;
    this->third = other.third;
}

template <typename T>
Trio<T>::Trio() {}

template <typename T>
bool Trio<T>::operator==(const Trio &other) const {
    return this->first == other.first &&
           this->second == other.second &&
           this->third == other.third;
}


#endif