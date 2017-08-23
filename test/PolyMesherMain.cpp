#include <veamy/Veamer.h>

int main(){
    Veamer v;
    Material m(1e7, 0.3);

    //By default, the file is read from home/, to read from somewhere else, for example, /home/user/Documents/Veamy,
    //create the fileName variable as "/Documents/Veamy/parabolic24x12.txt". All files follow the same idea.
    PolygonalMesh mesh = v.initProblemFromFile("/CLionProjects/Veamy/polymesher/polymesher2veamy_simple.txt", m);
    mesh.printInFile("mesh.txt");

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = "displacements.txt";
    v.writeDisplacements(fileName, x);
}
