#ifndef UTILITIES_UNIQUELIST_H
#define UTILITIES_UNIQUELIST_H

#include <vector>
#include <algorithm>
#include <map>
#include <utilities/utilities.h>

/*
 * Class that represents a list of unique elements (hence, elements inside a UniqueList list need to be comparable)
 */
template <class T>
class UniqueList {
private:
    /*
     * List of elements and map to ensure uniqueness
     */
    std::vector<T> list;
    std::map<T,int> map;
public:
    /*
     * Default constructor
     */
    UniqueList();

    /* Adds a new element to the tail of the list (if not in the list)
     * @param item element to add
     * @return index where the element was inserted (or found if already in the list)
     */
    int push_back(T& item);

    /* Adds a new element to the tail of the list (without checking uniqueness). Use at your own risk
     * @param item element to add
     * @return index where the element was inserted
     */
    int force_push_back(T& item);

    /*
     * @return number of elements on the list
     */
    int size();

    /* Adds a list of elements to the tail of the unique list (checking each one)
     * @param list elements to add
     * @return list of the indexes where each element was inserted
     */
    std::vector<int> push_list(std::vector<T> list);

    /* Adds a unique list of elements to the tail of the unique list (checking each one)
     * @param list elements to add
     * @return list of the indexes where each element was inserted
     */
    std::vector<int> push_list(UniqueList<T> list);

    /*
     * Deletes the first element of the unique list
     */
    void pop_front();

    /*
     * @return vector inside the unique list
     */
    std::vector<T> getList() const;

    /*
     * @return reference to the vector inside the unique list
     */
    std::vector<T>& getList();

    /* Returns the index of an element in the unique list (-1 if not found)
     * @param elem element to lookup
     * @return index of elem
     */
    int indexOf(T elem);

    /* Gets the element at the given index
     * @param i index to get the element from
     * @return element at position i
     */
    T& operator[](int i);

    /* Equality operator (compares memory direction, not content)
     * @param other
     * @return if the two lists are equal or not
     */
    bool operator==(const UniqueList<T>& other);

    /* Checks if an element is in the list
     * @param elem element to check
     * @return if the element is in the list or not
     */
    bool contains(T elem);

    /* Checks if two lists have common elements
     * @param other list to compare with
     * @return if there is at least one common element in the two lists
     */
    bool hasCommonElement(UniqueList<T> other);

    /*
     * Empties the unique list
     */
    void clear();

    /* Deletes an element from the list
     * @param item element to delete
     */
    void delete_element(T item);
};

template <class T>
UniqueList<T>::UniqueList() {}

template <class T>
int UniqueList<T>::push_back(T& item) {
    auto iter = map.find(item);

    if(iter != map.end())
        return iter->second;

    map.insert(std::make_pair(item, list.size()));
    list.push_back(item);

    return (int) list.size()-1;
}

template <class T>
int UniqueList<T>::force_push_back(T &item) {
    list.push_back(item);

    return (int) list.size()-1;
}

template <class T>
void UniqueList<T>::pop_front() {
    T elem = this->list[0];

    this->list.erase(this->list.begin());
    this->map.erase(elem);
}

template <class T>
int UniqueList<T>::size() {
    return (int) list.size();
}

template <class T>
std::vector<T> UniqueList<T>::getList() const{
    return this->list;
}

template <class T>
int UniqueList<T>::indexOf(T elem) {
    return utilities::indexOf(this->list, elem);
}

template <class T>
bool UniqueList<T>::operator==(const UniqueList<T> &other) {
    return this->list==other.getList();
}

template <class T>
T& UniqueList<T>::operator[](int i) {
    return list[i];
}

template <class T>
std::vector<int> UniqueList<T>::push_list(std::vector<T> list) {
    std::vector<int> index;

    for(int i=0;i<list.size();i++){
        index.push_back(this->push_back(list[i]));
    }

    return index;
}

template <class T>
std::vector<int> UniqueList<T>::push_list(UniqueList<T> list) {
    std::vector<int> index;

    for(int i=0;i<list.size();i++){
        index.push_back(this->push_back(list[i]));
    }

    return index;
}

template <class T>
bool UniqueList<T>::contains(T elem) {
    auto iter = map.find(elem);
    return iter != map.end();
}

template <class T>
std::vector<T>& UniqueList<T>::getList() {
    return this->list;
}

template <class T>
bool UniqueList<T>::hasCommonElement(UniqueList<T> other) {
    for(int i=0; i<other.size(); i++){
        if(this->contains(other[i])){
            return true;
        }
    }

    return false;
}

template <class T>
void UniqueList<T>::clear() {
    this->list.clear();
    this->map.clear();
}

template <class T>
void UniqueList<T>::delete_element(T item) {
    if(!this->contains(item)){
        return;
    }

    auto iter = map.find(item);
    this->list.erase(this->list.begin() + iter->second);
    this->map.clear();

    for (int i=0;i<this->list.size();i++){
        T e = this->list[i];
        map.insert(std::make_pair(e, i));
    }
}


#endif