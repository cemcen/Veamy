#include <mesher/models/Triangulation.h>

Triangulation::Triangulation(std::vector <Point> &p, std::vector <Triangle> &t, SegmentMap edges) {
    this->points.assign(p.begin(), p.end());
    this->triangles.assign(t.begin(),t.end());
    this->edges = edges;
}

std::vector<Triangle> Triangulation::getTriangles() {
    return this->triangles;
}

void Triangulation::print(std::string fileName) {
    std::string path = utilities::getPath();
    path +=  fileName;

    std::ofstream file;
    file.open(path, std::ios::out);

    file << points.size() << std::endl;
    for(int i=0;i<points.size();i++){
        file << points[i].getString() << std::endl;
    }

    file << this->edges.size() << std::endl;
    for(auto e: this->edges.getMap()){
        IndexSegment edge = e.first;
        file << edge.getString() << std::endl;
    }

    file << this->triangles.size() << std::endl;
    for(int i=0;i<this->triangles.size();i++){
        file << this->triangles[i].getString() << std::endl;
    }


    file.close();
}

void Triangulation::writeElements(std::ofstream &file) {
    file << this->triangles.size() << std::endl;
    for(int i=0;i<this->triangles.size();i++){
        file << this->triangles[i].getString() << std::endl;
    }
}

std::vector<Point> Triangulation::getPoints() {
    return this->points;
}
