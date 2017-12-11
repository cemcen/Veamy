#ifndef UTILITIES_PAIR_H
#define UTILITIES_PAIR_H

/*
 * Class that contains two instances of the same class. There are no restrictions on what it can contain, but
 * certain operations fail if the values can not be arithmetically operated
 */
template <typename T>
class Pair {
public:
    /*
     * Elements contained
     */
    T first;
    T second;

    /*
     * Constructor
     */
    Pair(T first, T second);

    /*
     * Copy constructor
     */
    Pair(const Pair& other);

    /*
     * Default constructor
     */
    Pair();

    /*
     * Equality operator
     * @param other Pair instance to check against
     * @return if the two instances are equal (contain the same elements)
     */
    bool operator==(const Pair& other) const;

    /*
     * Less than operator
     * @param other Pair instance to compare against
     * @return whether this Pair is less than the other
     */
    bool operator<(const Pair& other) const;

    /*
     * Computes the dot product of two Pairs (multiplies the two first and the two seconds, then adds the results)
     * @param other Pair to calculate with
     * @return dot product of the two pairs
     */
    T dot(Pair other);

    /*
     * Product operator. Multiplies each corresponding value of the two pairs
     * @param other Pair to operate with
     * @return result of the operation
     */
    Pair<T> operator*(double other);

    /* Addition operation. Adds each corresponding value of the two pairs
     * @param other Pair to operate with
     * @return result of the operation
     */
    Pair<T> operator+(const Pair& other) const;

    /* Substraction operation. Substracts each corresponding value of the two pairs
     * @param other Pair to operate with
     * @return result of the operation
     */
    Pair<T> operator-(const Pair& other) const;
};

template <typename T>
Pair<T>::Pair(T first, T second) {
    this->first = first;
    this->second = second;
}

template <typename T>
Pair<T>::Pair(const Pair &other) {
    this->first = other.first;
    this->second = other.second;
}

template <typename T>
Pair<T>::Pair() {}

template <typename T>
bool Pair<T>::operator==(const Pair &other) const{
    return this->first == other.first && this->second == other.second;
}

template <typename T>
T Pair<T>::dot(Pair other) {
    return this->first*other.first + this->second*other.second;
}

template <typename T>
Pair<T> Pair<T>::operator*(const double other) {
    return Pair<T>(this->first*other, this->second*other);
}

template <typename T>
Pair<T> Pair<T>::operator+(const Pair &other) const {
    return Pair<T>(this->first + other.first, this->second + other.second);
}

template <typename T>
bool Pair<T>::operator<(const Pair &other) const {
     if(this->first==other.first){
        return this->second<other.second;
    }

    return this->first<other.first;
}

template <typename T>
Pair<T> Pair<T>::operator-(const Pair &other) const {
    return Pair<T>(this->first - other.first, this->second - other.second);
}

#endif