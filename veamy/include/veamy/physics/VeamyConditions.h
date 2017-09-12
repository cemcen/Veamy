#ifndef THESIS_PROBLEMCONDITIONS_H
#define THESIS_PROBLEMCONDITIONS_H

#include <veamy/physics/bodyforces/VariableBodyForce.h>
#include <veamy/physics/materials/Material.h>
#include <veamy/physics/bodyforces/None.h>
#include <veamy/physics/bodyforces/VeamyBodyForce.h>
#include "Conditions.h"

struct VeamyConditions : Conditions<VeamyBodyForce>{

};


#endif 
