#include <delynoi/models/neighbourhood/NeighboursBySegment.h>

NeighboursBySegment::NeighboursBySegment() {}

NeighboursBySegment::NeighboursBySegment(int i1) {
    this->n1 = i1;
}

NeighboursBySegment::NeighboursBySegment(int i1, int i2) {
    this->n1 = i1;
    this->n2 = i2;
}

NeighboursBySegment::NeighboursBySegment(Pair<int> p) {
    this->n1 = p.first;
    this->n2 = p.second;
}

void NeighboursBySegment::setNeighbour(int i) {
    this->n2 = i;
}

int NeighboursBySegment::getFirst() const{
    return this->n1;
}

int NeighboursBySegment::getSecond() const{
    return this->n2;
}

std::string NeighboursBySegment::getString() const {
    return utilities::toString<double>(this->n1) + " " + utilities::toString<double>(this->n2);
}

bool NeighboursBySegment::operator==(const NeighboursBySegment &other) const{
    return this->getFirst()==other.getFirst() && this->getSecond()==other.getSecond() ||
           this->getFirst()==other.getSecond() && this->getSecond()==other.getFirst();
}

