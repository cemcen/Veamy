#include <delynoi/models/neighbourhood/PointMap.h>

PointMap::PointMap() {}

void PointMap::insert(Point p, int neighbour) {
    auto got = this->map.find(p);

    if(got == this->map.end()){
        NeighboursByPoint n (neighbour);
        this->map.insert(std::make_pair(p,n));
    }else{
        NeighboursByPoint& n = got->second;
        n.add(neighbour);
    }
}

void PointMap::insert(Point &p, std::vector<int> &neighbours) {
    auto got = this->map.find(p);

    if(got == this->map.end()){
        NeighboursByPoint n (neighbours);
        this->map.insert(std::make_pair(p,n));
    }else{
        NeighboursByPoint& n = got->second;
        n.insert(neighbours);
    }
}

NeighboursByPoint &PointMap::get(Point p) {
    return this->map[p];
}

std::map<Point, NeighboursByPoint> &PointMap::getMap() {
    return this->map;
}

int PointMap::size() {
    return this->map.size();
}

void PointMap::printInFile(std::string fileName) {
    std::string path = utilities::getPath();
    path +=  fileName;

    std::ofstream file;
    file.open(path, std::ios::out);


    for(auto v : this->map){
        file << v.first.getString() + " ";
        NeighboursByPoint n = v.second;

        for(int i: n.getNeighbours()){
            file << i << " ";
        }

        file << std::endl;
    }

    file.close();
}


