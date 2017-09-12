#ifndef VEAMY_FEAMER_H
#define VEAMY_FEAMER_H

#include <veamy/Calculator2D.h>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <delynoi/models/polygon/Triangle.h>

class Feamer : public Calculator2D<Triangle,BodyForce>{

};

#endif