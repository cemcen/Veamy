#ifndef UTILITIES_UNIQUELIST_H
#define UTILITIES_UNIQUELIST_H

#include <vector>
#include <algorithm>
#include <map>
#include <utilities/utilities.h>

template <class T>
class UniqueList {
private:
    std::vector<T> list;
    std::map<T,int> map;
public:
    UniqueList();
    int push_back(T& item);
    int force_push_back(T& item);
    int size();
    std::vector<int> push_list(std::vector<T> list);
    std::vector<int> push_list(UniqueList<T> list);
    void pop_front();

    std::vector<T> getList() const;
    std::vector<T>& getList();

    int indexOf(T elem);
    T& operator[](int i);
    bool operator==(const UniqueList<T>& other);
    bool contains(T elem);
    bool hasCommonElement(UniqueList<T> other);

    void clear();
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