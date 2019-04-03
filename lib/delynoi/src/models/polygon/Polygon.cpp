#include <delynoi/models/polygon/Polygon.h>
#include <map>
#include <utilities/UniqueList.h>
#include <utilities/Pair.h>
#include <delynoi/models/neighbourhood/SegmentMap.h>


Polygon::Polygon(std::vector<int>& points, std::vector<Point>& p) {
    if(isSelfIntersecting(p)){
        throw std::invalid_argument("Self intersecting polygons are not supported");
    }

    this->points.assign(points.begin(), points.end());

    this->diameter = -1;
    this->area = -1;
    this->centroid = Point();
    calculateHash();
}

void Polygon::mutate(std::vector<Point> &p) {
    this->points.clear();
    delynoi_utilities::TrivialIndexVector(this->points,p.size());

    if(isSelfIntersecting(p)){
        throw std::invalid_argument("Self intersecting polygons are not supported");
    }

    this->diameter = -1;
    this->area = -1;
    this->centroid = Point();
    calculateHash();
}

Polygon::Polygon(std::vector<Point> &p) {
    if(isSelfIntersecting(p)){
        std::invalid_argument("Self intersecting polygons are not supported");
    }

    delynoi_utilities::TrivialIndexVector(this->points,p.size());

    std::vector<Point> this_points;
    for(int i=0;i<points.size();i++){
        this_points.push_back(p[points[i]]);
    }

    this->diameter = -1;
    this->area = -1;
    this->centroid = Point();
    calculateHash();
}

Polygon::Polygon() {}

Polygon::Polygon(const Polygon &obj) {
    this->area = obj.area;
    this->diameter = obj.diameter;
    this->centroid = obj.centroid;

    this->points.assign(obj.points.begin(), obj.points.end());
    calculateHash();
}

double Polygon::calculateDiameter(std::vector<Point>& p) {
    std::vector<std::pair<Point,Point> > rotatingCalipers = convex::rotatingCalipers(p);
    double max = -1;

    for(int i=0;i<rotatingCalipers.size();i++){
        double distance = delynoi_utilities::norm (rotatingCalipers[i].first - rotatingCalipers[i].second);
        if(distance>max){
            max = distance;
        }
    }

    return max;
}

double Polygon::calculateArea(std::vector<Point>& p) {
    return geometry_functions::area(p,this->points);
}

double Polygon::getArea(std::vector<Point>& points){
    if(this->area == -1){
        std::vector<Point> thisPoints = this->getPoints(points);
        this->calculateArea(thisPoints);
    }

    return this->area;
}

double Polygon::getDiameter(std::vector<Point>& points) {
    if(this->diameter < 0){
        std::vector<Point> thisPoints = this->getPoints(points);
        this->calculateDiameter(thisPoints);
    }

    return this->diameter;
}

Point Polygon::getCentroid(std::vector<Point>& points) {
    if(!this->centroid.isValid()){
        std::vector<Point> thisPoints = this->getPoints(points);
        this->calculateCentroid(thisPoints);
    }

    return this->centroid;
}

double Polygon::signedArea(std::vector<Point>& p) {
    double area = 0;
    int n = (int) this->points.size();

    for(int i=0;i<n;i++){
        area += p[points[i]].getX()*p[points[(i+1)%n]].getY() - p[points[(i+1)%n]].getX()*p[points[i]].getY();
    }

    return 0.5*area;
}

void Polygon::getSegments(std::vector<IndexSegment>& segments) {
    int n = (int) this->points.size();

    for(int i=0;i<n; i++){
        IndexSegment s (this->points[i%n], this->points[(i+1)%n]);
        segments.push_back(s);
    }
}

Point Polygon::calculateCentroid(std::vector<Point>& p) {
    int n = this->points.size();
    double partial_x = 0;
    double partial_y = 0;

    for(int i=0;i<n;i++){
        Point pi = p[points[i]];
        Point pi1 = p[points[(i+1)%n]];

        partial_x += (pi.getX() + pi1.getX())*(pi.getX()*pi1.getY() - pi1.getX()*pi.getY());
        partial_y += (pi.getY() + pi1.getY())*(pi.getX()*pi1.getY() - pi1.getX()*pi.getY());
    }

    double A = this->signedArea(p);
    double cX = partial_x/(6*A);
    double cY = partial_y/(6*A);

    return Point (cX,cY);
}

bool Polygon::containsPoint(std::vector<Point>& p, Point point) {
    int j = points.size() - 1 ;
    bool oddNodes = false;

    for (int i=0; i<points.size(); i++) {
        Point pI = p[points[i]];
        Point pJ = p[points[j]];

        if(pI == pJ){
            continue;
        }

        if (pI.getY()<=point.getY() && pJ.getY()>point.getY()
            || pJ.getY()<=point.getY() && pI.getY()>point.getY()) {

            if (pI.getX() + (point.getY()-pI.getY())/(pJ.getY()-pI.getY())*(pJ.getX()-pI.getX())<point.getX()){
                oddNodes=!oddNodes;
            }
        }
        j = i;
    }

    if(oddNodes){
        return true;
    }

    return inEdges(p,point);
}

IndexSegment Polygon::containerEdge(std::vector<Point>& p, Point point){
    std::vector<IndexSegment> segments;
    this->getSegments(segments);

    for(int i=0; i<segments.size(); i++){
        if(segments[i].contains(p,point)){
            return segments[i];
        }
    }

    return IndexSegment(-1, -1);
}

bool Polygon::inEdges(std::vector<Point>& p, Point point) {
    IndexSegment container = containerEdge(p, point);

    return container.getFirst()!= -1 && container.getSecond()!= -1;
}

bool Polygon::isConvex(std::vector<Point>& p) {
    int n = (int) this->points.size();

    double determinant = delynoi_utilities::orientation(p[this->points[0]],p[this->points[1]],p[this->points[2]]);

    for(int i=1;i<n; i++){
        double newResult = delynoi_utilities::orientation(p[this->points[i]],p[this->points[(i+1)%n]],p[this->points[(i+2)%n]]);

        if(determinant*newResult<0){
            return false;
        }
    }

    return true;
}

std::vector<int> Polygon::getPoints() const{
    return this->points;
}

std::vector<int> &Polygon::getPoints() {
    return this->points;
}

int Polygon::numberOfSides() const{
    return (int) points.size();
}


bool Polygon::isClockwise(std::vector<Point> &p) {
    int n = (int) points.size();

    Point pI = p[points[0]];
    Point pI1 = p[points[n-1]];

    double sum = (pI.getX() - pI1.getX())*(pI.getY() + pI1.getY());

    for(int i=0; i<n-1; i++){
        pI1 = p[points[(i+1)%n]];
        pI = p[points[i]];

        sum += (pI1.getX() - pI.getX())*(pI1.getY() + pI.getY());
    }

    return sum>0;
}

bool Polygon::operator==(const Polygon &other) const{
    return this->hash==other.hash;
}

std::string Polygon::getString() {
    std::string base = utilities::toString<double>(this->points.size());

    for(int i=0;i<this->points.size();i++){
        base += " " + utilities::toString<double>(this->points[i]);
    }

    return base;
}

bool Polygon::isVertex(int index) {
    return std::find(points.begin(), points.end(), index) != points.end();
}

void Polygon::calculateHash() {
    std::size_t hash = 0;

    for (int i = 0; i < points.size(); ++i) {
        hash+= utilities::hash32(points[i]);
    }

    this->hash = hash;
}

void Polygon::fixCCW(std::vector<Point> &p) {
    if(isClockwise(p)){
        std::reverse(this->points.begin(), this->points.end());
        this->area = -this->area;
    }
}

std::vector<Point> Polygon::getPoints(std::vector<Point> &p) {
    std::vector<Point> returnPoints;

    for (int i = 0; i < this->points.size(); ++i) {
        returnPoints.push_back(p[this->points[i]]);
    }

    return returnPoints;
}

bool Polygon::operator<(const Polygon &other) const {
    return this->hash<other.hash;
}

bool Polygon::isSelfIntersecting(std::vector<Point>& points) {
    std::vector<IndexSegment> segments;
    this->getSegments(segments);
    int n = segments.size();
    Point intersection;

    for (int i = 0; i < n; ++i) {
        IndexSegment s = segments[i];

        for (int j = 0; j < n; ++j) {
            if(i==j || j==(i-1+n)%n || j==(i+1)%n){
                continue;
            }

            if(s.intersection(points,segments[j],intersection)){
                return true;
            }
        }
    }
    return false;
}

bool Polygon::containsEdge(IndexSegment &s) {
    int n = this->numberOfSides();

    int i = utilities::indexOf(this->points, s.getFirst());
    int j = utilities::indexOf(this->points, s.getSecond());

    return i!=-1 && j!=-1 && (std::abs(i-j)==1 || std::abs(i-j)==(n-1));
}

Point Polygon::getAverage(std::vector<Point> &p) {
    double x = 0;
    double y = 0;

    for (int v: points){
        Point vertex = p[v];

        x += vertex.getX();
        y += vertex.getY();
    }

    x = x/this->numberOfSides(); y = y/this->numberOfSides();

    return Point(x,y);
}

double Polygon::getMaxDistance(std::vector<Point> &points) {
    int n = this->points.size();
    double maxEdge = LLONG_MIN;

    for (int i = 0; i < this->points.size(); ++i) {
        double distance = IndexSegment(this->points[i], this->points[(i+1)%n]).length(points);

        if(distance > maxEdge){
            maxEdge = distance;
        }
    }

    return maxEdge;
}
