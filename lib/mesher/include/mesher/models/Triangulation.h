#ifndef MESHER_TRIANGULATION_H
#define MESHER_TRIANGULATION_H

#include <vector>
#include <string>
#include <fstream>
#include <mesher/models/polygon/Triangle.h>
#include <mesher/models/neighbourhood/SegmentMap.h>
#include <mesher/models/Mesh.h>

class Triangulation : public Mesh {
private:
    std::vector<Triangle> triangles;
    std::vector<Point> points;
public:
    Triangulation(std::vector<Point>& p, std::vector<Triangle>& t, SegmentMap edges);
    std::vector<Triangle> getTriangles();
    void print(std::string fileName);
    void writeElements(std::ofstream& file);
    std::vector<Point> getPoints();
};

#endif
