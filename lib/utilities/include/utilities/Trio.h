#ifndef UTILITIES_TRIO_H
#define UTILITIES_TRIO_H

/*
 * Class that contains three instances of the same value
 */
template <typename T>
class Trio {
public:
    /*
   * Elements contained
   */
    T first;
    T second;
    T third;

    /*
     * Constructor
     */
    Trio(T f, T s, T t);

    /*
     * Copy constructor
     */
    Trio(const Trio& other);

    /*
     * Default constructor
     */
    Trio();

    /*
     * Equality operator
     * @param other Trio instance to check against
     * @return if the two instances are equal (contain the same elements)
     */
    bool operator==(const Trio& other) const;

    /*
    * Computes the dot product of two Trios (first*first + second*second + ...)
    * @param other Trio to calculate with
    * @return dot product of the two trios
    */
    T dot(Trio<T> other);

    /* Substraction operation. Substracts each corresponding value of the two trios
     * @param other Trio to operate with
     * @return result of the operation
     */
    Trio<T> operator-(const Trio &other) const;
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

template <typename T>
T Trio<T>::dot(Trio<T> other) {
    return this->first*other.first + this->second*other.second + this->third*other.third;
}

template <typename T>
Trio<T> Trio<T>::operator-(const Trio &other) const {
    return Trio<T>(this->first - other.first, this->second - other.second, this->third - other.third);
}

#endif