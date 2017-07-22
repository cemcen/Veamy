#include <mesher/models/neighbourhood/Neighbours.h>

Neighbours::Neighbours() {}

Neighbours::Neighbours(int i1) {
    this->n1 = i1;
}

Neighbours::Neighbours(int i1, int i2) {
    this->n1 = i1;
    this->n2 = i2;
}

Neighbours::Neighbours(Pair<int> p) {
    this->n1 = p.first;
    this->n2 = p.second;
}

void Neighbours::setNeighbour(int i) {
    this->n2 = i;
}

void Neighbours::changeNeighbour(int oldN, int newN) {
    if(this->n1==oldN){
        this->n1 = newN;
        return;
    }

    if(this->n2==oldN){
        this->n2 = newN;
        return;
    }

    return;
}

bool Neighbours::isNeighbour(int i) {
    return this->n1==i || this->n2==i;
}

int Neighbours::getFirst() const{
    return this->n1;
}

int Neighbours::getSecond() const{
    return this->n2;
}

std::string Neighbours::getString() const {
    return utilities::toString<double>(this->n1) + " " + utilities::toString<double>(this->n2);
}

bool Neighbours::operator==(const Neighbours &other) const{
    return this->getFirst()==other.getFirst() && this->getSecond()==other.getSecond() ||
           this->getFirst()==other.getSecond() && this->getSecond()==other.getFirst();
}

int Neighbours::getOther(int n) {
    if(this->n1==n){
        return this->n2;
    }

    if(this->n2==n){
        return this->n1;
    }

    return -1;
}
