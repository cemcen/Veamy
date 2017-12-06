#include <veamy/geometry/VeamyPolygon.h>

VeamyPolygon::VeamyPolygon(Polygon p) : Polygon(p){}

std::vector<VeamyTriangle> VeamyPolygon::triangulate(std::vector<Point> points) {
    std::vector<VeamyTriangle> triangles;
    std::vector<int> pointList = this->getPoints();

    while(pointList.size()>=3){
        VeamyTriangle ear = getEar(points, pointList);
        if(ear.isNull()){
            break;
        }
        triangles.push_back(ear);
    }

    return triangles;
}


VeamyTriangle VeamyPolygon::getEar(std::vector<Point> points, std::vector<int> &pointList) {
    int size = (int) pointList.size();

    if(size<3){
        VeamyTriangle t;
        return t;
    }

    if(size==3){
        VeamyTriangle ear (pointList[0], pointList[1], pointList[2]);
        pointList.clear();
        return ear;
    }

    for(int i=0;i<size;i++){
        bool test = false;
        VeamyTriangle t (pointList[(size+i-1)%size], pointList[i%size], pointList[(size+i+1)%size]);

        if(t.isConvex(points)){
            for(int j=0;j<size;j++){
                if(!t.isVertex(pointList[j]) && t.containsPoint(points, points[pointList[j]])){
                    test = true;
                }
            }

            if(!test){
                pointList.erase(pointList.begin() + i);
                return t;
            }

        }
    }

    VeamyTriangle t;
    return t;
}
