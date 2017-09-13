#include <delynoi/models/Mesh.h>

template <typename T>
Mesh<T>::Mesh() {}

template <typename T>
Mesh<T>::Mesh(std::vector<Point> &p, std::vector<T> &e, SegmentMap s, PointMap pM) {
    this->points.push_list(p);
    this->polygons.assign(e.begin(), e.end());
    this->edges = s;
    this->pointMap = pM;
}

template <typename T>
Mesh<T>::Mesh(UniqueList<Point> p, std::vector<T> &e, SegmentMap s, PointMap pM) {
    this->points.push_list(p);
    this->polygons.assign(e.begin(), e.end());
    this->edges = s;
    this->pointMap = pM;
}

template <typename T>
Mesh<T>::Mesh(const Mesh &m) {
    this->points = m.getPoints();
    this->polygons = m.getPolygons();
    this->edges = m.getSegments();
    this->pointMap = m.getPointMap();
}

template <typename T>
void Mesh<T>::createFromFile(std::string fileName) {
    std::ifstream infile = utilities::openFile(fileName);

    createFromStream(infile);

    infile.close();
}

template <typename T>
void Mesh<T>::createFromStream(std::ifstream &infile) {
    std::string line;
    std::getline(infile, line);
    int numberMeshPoints = std::atoi(line.c_str());
    for (int i = 0; i < numberMeshPoints; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

        Point newPoint(std::atof(splittedLine[0].c_str()), std::atof(splittedLine[1].c_str()));
        this->points.push_back(newPoint);
    }

    std::getline(infile, line);
    int numberMeshPolygons = std::atoi(line.c_str());

    for (int i = 0; i < numberMeshPolygons; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

        std::vector<int> polygonPoints;
        for (int j = 1; j < splittedLine.size(); ++j) {
            polygonPoints.push_back(std::atoi(splittedLine[j].c_str()) - 1);
        }

        T newPolygon(polygonPoints, this->points.getList());
        this->polygons.push_back(newPolygon);
        std::vector<IndexSegment> segments;
        newPolygon.getSegments(segments);

        for (IndexSegment s: segments){
            this->edges.insert(s, i);
        }
    }
}

template <typename T>
void Mesh<T>::printInFile(std::string fileName) {
    std::string path = utilities::getPath();
    path +=  fileName;

    std::ofstream file;
    file.open(path, std::ios::out);
    file << std::fixed << std::setprecision(DelynoiConfig::instance()->getPrecision());

    printInStream(file);
    file.close();
}

template <typename T>
std::vector<T>& Mesh<T>::getPolygons() {
    return this->polygons;
}

template <typename T>
std::vector<T> Mesh<T>::getPolygons() const {
    return this->polygons;
}

template <typename T>
T& Mesh<T>::getPolygon(int index) {
    return this->polygons[index];
}

template <typename T>
void Mesh<T>::printInStream(std::ofstream &file) {
    file << points.size() << std::endl;
    for(int i=0;i<points.size();i++){
        file << points[i].getString() << std::endl;
    }

    file << this->edges.size() << std::endl;
    for(auto e: this->edges.getMap()){
        IndexSegment edge = e.first;
        file << edge.getString() << std::endl;
    }

    file << this->polygons.size() << std::endl;
    for(int i=0;i<this->polygons.size();i++){
        file << this->polygons[i].getString() << std::endl;
    }
}

template <typename T>
SegmentMap &Mesh<T>::getSegments() {
    return this->edges;
}

template <typename T>
SegmentMap Mesh<T>::getSegments() const {
    return this->edges;
}

template <typename T>
PointMap &Mesh<T>::getPointMap() {
    return this->pointMap;
}

template <typename T>
PointMap Mesh<T>::getPointMap() const {
    return this->pointMap;
}

template <typename T>
UniqueList <Point> &Mesh<T>::getPoints() {
    return this->points;
}

template <typename T>
UniqueList <Point> Mesh<T>::getPoints() const {
    return this->points;
}

template <typename T>
Point Mesh<T>::getPoint(int i) {
    return this->points[i];
}

template <typename T>
NeighboursBySegment Mesh<T>::getNeighbours(IndexSegment s) {
    return this->edges.get(s);
}

template class Mesh<Polygon>;
template class Mesh<Triangle>;