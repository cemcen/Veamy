#include <mesher/models/generator/PointGenerator.h>

PointGenerator::PointGenerator(Functor* lX, Functor* lY) {
    this->lX = lX;
    this->lY = lY;
}

void PointGenerator::generate(std::vector <Point> &vector, BoundingBox box, int nX, int nY) {
    double dX = box.getWidth()/(nX-1);
    double dY = box.getHeight()/(nY-1);

    for(int i = 0; i<nY; i++){
        for(int j = 0; j<nX; j++){
            double x = box.xMin() + j*dX;
            double y = box.yMin() + i*dY;

            vector.push_back(Point(lX->apply(x), lY->apply(y)));
        }
    }
}



