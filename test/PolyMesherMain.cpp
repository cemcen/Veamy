#include <veamy/Veamer.h>
#include <veamy/physics/MaterialPlaneStrain.h>

int main(){
    Veamer v;
    Material* material = new MaterialPlaneStrain(1e7, 0.3);

    //By default, the file is read from home/, to read from somewhere else, for example, /home/user/Documents/Veamy,
    //create the fileName variable as "/Documents/Veamy/polymesher2veamy.txt". All files follow the same idea.
    PolygonalMesh mesh = v.initProblemFromFile("polymesher2veamy2.txt", material);
    mesh.printInFile("mesh.txt");

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = "displacements.txt";
    v.writeDisplacements(fileName, x);
}
