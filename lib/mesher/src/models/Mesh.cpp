#include <mesher/models/Mesh.h>
#include <utilities/utilities.h>

void Mesh::printInFile(std::string fileName) {
    std::string path = utilities::getPath();
    path +=  fileName;

    std::ofstream file;
    file.open(path, std::ios::out);
    file << std::fixed << std::setprecision(20);

    printInStream(file);
    file.close();
}

void Mesh::printInStream(std::ofstream &file) {
    file << points.size() << std::endl;
    for(int i=0;i<points.size();i++){
        file << points[i].getString() << std::endl;
    }

    file << this->edges.size() << std::endl;
    for(auto e: this->edges.getMap()){
        IndexSegment edge = e.first;
        file << edge.getString() << std::endl;
    }

    writeElements(file);
}

SegmentMap &Mesh::getSegments() {
    return this->edges;
}

SegmentMap Mesh::getSegments() const {
    return this->edges;
}

UniqueList <Point> &Mesh::getPoints() {
    return this->points;
}

UniqueList <Point> Mesh::getPoints() const {
    return this->points;
}

bool Mesh::isFull() {
    return this->points.size()>0;
}

Point Mesh::getPoint(int i) {
    return this->points[i];
}

IndexSegment Mesh::convertSegment(PointSegment s) {
    return IndexSegment(this->points.indexOf(s.getFirst()), this->points.indexOf(s.getSecond()));
}

Neighbours Mesh::getNeighbours(IndexSegment s) {
    return this->edges.get(s);
}
