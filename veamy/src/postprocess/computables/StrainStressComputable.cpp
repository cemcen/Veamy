#include <veamy/postprocess/computables/StrainStressComputable.h>
#include <delynoi/models/polygon/Polygon.h>

StrainStressComputable::StrainStressComputable(StrainValue *strain, StressValue *value) {
    this->strainValue = strain;
    this->stressValue = value;
}

double StrainStressComputable::apply(double x, double y, int index, Polygon container) {
    Trio<double> stress = this->stressValue->getValue(Point(x,y));
    Trio<double> strain = this->strainValue->getValue(Point(x,y));

    return stress.dot(strain);
}
