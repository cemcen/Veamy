#include <delynoi/models/generator/PointGenerator.h>

PointGenerator::PointGenerator(Functor* lX, Functor* lY) {
    this->lX = lX;
    this->lY = lY;

    this->variable = functions::independent_variable::both;
}

PointGenerator::PointGenerator(Functor *l, functions::independent_variable variable) {
    this->variable = variable;

    switch(variable){
        case functions::independent_variable::x:
            this->lY = l;
            break;
        case functions::independent_variable::y:
            this->lX = l;
            break;
        case functions::independent_variable::both:
            throw std::invalid_argument("Both free variables and only one generator function given");
    }
}

void PointGenerator::generate(std::vector <Point> &vector, BoundingBox box, int nX, int nY) {
    double dX = box.getWidth()/(nX-1);
    double dY = box.getHeight()/(nY-1);

    for(int i = 0; i<nY; i++){
        for(int j = 0; j<nX; j++){
            double x = box.xMin() + j*dX;
            double y = box.yMin() + i*dY;

            vector.push_back(result(x,y));
        }
    }
}

Point PointGenerator::result(double x, double y) {
    switch(variable){
        case functions::independent_variable::x:
            return Point(x, y + this->lY->apply(x));
        case functions::independent_variable::y:
            return Point(x + this->lX->apply(y), y);
        case functions::independent_variable::both:
            return Point(this->lX->apply(x), this->lY->apply(y));

    }
}


