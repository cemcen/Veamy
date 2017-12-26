#ifndef VEAMY_DOF_H
#define VEAMY_DOF_H

#include <utilities/Pair.h>
#include <delynoi/models/polygon/Polygon.h>

class DOF {
public:
    enum Axis {x, y};

    DOF(int index, int point_index, DOF::Axis a);
    DOF(int index, int point_index);
    int globalIndex() const;
    int pointIndex();
    bool operator==(const DOF& other) const;
    bool operator<(const DOF& other) const;
    DOF::Axis getAxis();
protected:
    int index;
    int point_index;
    DOF::Axis d;
};


#endif
