#ifndef MESHER_MESHGENERATOR_H
#define MESHER_MESHGENERATOR_H

#include <mesher/models/PolygonalMesh.h>

class MeshGenerator {
public:
    virtual PolygonalMesh getMesh() = 0;
};


#endif
