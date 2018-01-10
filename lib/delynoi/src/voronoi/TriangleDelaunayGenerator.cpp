#include "delynoi/voronoi/TriangleDelaunayGenerator.h"

TriangleDelaunayGenerator::TriangleDelaunayGenerator(const std::vector<Point>& points, Region region) {
    this->region = region;
    this->seedPoints = points;
    this->delaunayEdges = new SegmentMap;
}

void TriangleDelaunayGenerator::callTriangle(std::vector<Point> &point_list, char *switches) {
    this->empty = true;
    this->callTriangle(point_list, switches, std::vector<PointSegment>());
}

void TriangleDelaunayGenerator::callTriangle(std::vector<Point> &point_list, char *switches,
                                             std::vector<PointSegment> restrictedSegments) {
    this->empty = true;
    struct triangulateio in, out;

    std::vector<Point> regionPoints = region.getRegionPoints();
    UniqueList<Point> pointList;
    pointList.push_list(point_list);
    std::vector<int> regionIndex = pointList.push_list(regionPoints);

    in.numberofpoints = pointList.size();
    in.pointlist = (REAL*)malloc(in.numberofpoints*2*sizeof(REAL));
    in.numberofpointattributes = 1;
    in.pointattributelist = (REAL *) malloc(in.numberofpoints*in.numberofpointattributes*sizeof(REAL));
    int points = 0;

    for(int i=0;i<pointList.size();i++){
        in.pointlist[points] = pointList[i].getX();
        in.pointlist[points+1] = pointList[i].getY();
        in.pointattributelist[i] = 0.0;
        points+=2;
    }

    in.pointmarkerlist = (int *)NULL;

    std::vector<IndexSegment> segments;
    region.getSegments(segments);

    in.numberofsegments = (int) (segments.size() + restrictedSegments.size());
    in.segmentlist = (int*)malloc(in.numberofsegments*2*sizeof(int));
    in.segmentmarkerlist = (int*) NULL;
    int k;
    for(k=0;k<segments.size();k++){
        in.segmentlist[2*k] = regionIndex[segments[k].getFirst()];
        in.segmentlist[2*k+1] = regionIndex[segments[k].getSecond()];
    }

    for (int j=0; j<restrictedSegments.size(); j++){
        PointSegment s = restrictedSegments[j];

        in.segmentlist[2*k] = pointList.indexOf(s.getFirst());
        in.segmentlist[2*k+1] = pointList.indexOf(s.getSecond());
        k++;
    }

    std::vector<Hole>& holes = region.getHoles();
    in.numberofholes = (int) holes.size();
    in.holelist = (REAL*)malloc(in.numberofholes*2*sizeof(REAL));
    for(int i=0;i<holes.size();i++){
        in.holelist[2*i] = holes[i].getCenter().getX();
        in.holelist[2*i+1] = holes[i].getCenter().getY();
    }

    in.numberofregions = 0;

    out.pointlist = (REAL *) NULL;
    out.pointattributelist = (REAL *) NULL;
    out.pointmarkerlist = (int *) NULL;
    out.trianglelist = (int *) NULL;
    out.triangleattributelist = (REAL *) NULL;
    out.segmentmarkerlist = (int *) NULL;
    out.segmentlist = (int *) NULL;
    out.edgelist = (int *) NULL;
    out.edgemarkerlist = (int *) NULL;

    triangulate(switches, &in, &out, (struct triangulateio *)NULL);

    for(int i=0;i<out.numberofpoints;i++){
        PointData data (i);
        this->points.push_back(data);
        this->meshPoints.push_back(Point(out.pointlist[i*2], out.pointlist[i*2+1]));
        if(out.pointmarkerlist[i]==1){
            this->meshPoints.back().setBoundary();
        }
    }

    for(int i=0;i<out.numberofedges;i++) {
        EdgeData data(out.edgelist[2*i], out.edgelist[2*i+1]);
        this->edges.push_back(data);
        edgeMap.insert(std::make_pair(Key(out.edgelist[2*i], out.edgelist[2*i+1]),i));
        this->points[out.edgelist[2*i]].setEdge(i, out.edgemarkerlist[i]);
        this->points[out.edgelist[2*i+1]].setEdge(i, out.edgemarkerlist[i]);
    }

    for(int i=0;i<out.numberoftriangles;i++){
        std::vector<int> triangle_points = {out.trianglelist[3*i], out.trianglelist[3*i+1],
                                            out.trianglelist[3*i+2]};
        realPoints.push_back(out.trianglelist[3*i]);
        realPoints.push_back(out.trianglelist[3*i+1]);
        realPoints.push_back(out.trianglelist[3*i+2]);

        Triangle triangle (triangle_points, this->meshPoints);
        int i1 = edgeMap[Key(out.trianglelist[3*i], out.trianglelist[3*i+1])];
        int i2 = edgeMap[Key(out.trianglelist[3*i+1], out.trianglelist[3*i+2])];
        int i3 = edgeMap[Key(out.trianglelist[3*i+2], out.trianglelist[3*i])];

        this->edges[i1].setTriangle(i);
        this->edges[i2].setTriangle(i);
        this->edges[i3].setTriangle(i);

        this->triangles.push_back(triangle);
    }

    for (int i = 0; i < edges.size(); ++i) {
        EdgeData data = edges[i];
        IndexSegment segment (data.p1, data.p2);
        NeighboursBySegment neighbours(data.t1, data.t2);

        this->delaunayEdges->insert(segment, neighbours);
    }

    free(in.pointlist);
    free(in.pointattributelist);
    free(in.pointmarkerlist);
    free(in.segmentlist);
    free(in.segmentmarkerlist);
    free(in.holelist);

    free(out.pointlist);
    free(out.pointattributelist);
    free(out.pointmarkerlist);
    free(out.trianglelist);
    free(out.triangleattributelist);
    free(out.segmentmarkerlist);
    free(out.segmentlist);
    free(out.edgelist);
    free(out.edgemarkerlist);
}

Mesh<Triangle> TriangleDelaunayGenerator::getConformingDelaunayTriangulation()  {
    if(!this->empty){
        char switches[] = "pzejDQ";
        callTriangle(seedPoints, switches);
    }

    return initializeMesh<Triangle>();
}

void
TriangleDelaunayGenerator::writeTriangleInputFile(UniqueList<Point> &point_list, Region region, std::vector<int> regionIndex) {
    std::string path = utilities::getPath();
    path +=  "toTriangle.poly";

    std::ofstream file;
    file.open(path, std::ios::out);

    file << point_list.size() << " 2 0 0" << std::endl;
    for (int i = 0; i < point_list.size(); ++i) {
        file << i << " " << point_list[i].getString() << std::endl;
    }

    std::vector<IndexSegment> segments;
    region.getSegments(segments);

    file << segments.size() << " 0" << std::endl;
    for (int i = 0; i < segments.size(); ++i) {
        file << i << " " <<  regionIndex[segments[i].getFirst()] << " " << regionIndex[segments[i].getSecond()]<< std::endl;
    }

    file.close();
}

DelaunayInfo TriangleDelaunayGenerator::getConformingDelaunay() {
    if(!this->empty){
        char switches[] = "pzejDQ";
        callTriangle(seedPoints, switches);
    }

    return DelaunayInfo(triangles, meshPoints, delaunayEdges, points, realPoints, edges, edgeMap);
}

Mesh<Triangle> TriangleDelaunayGenerator::getConstrainedDelaunayTriangulation() {
    if(!this->empty){
        char switches[] = "pzejQ";
        callTriangle(seedPoints, switches);
    }

    return initializeMesh<Triangle>();
}

Mesh<Triangle>
TriangleDelaunayGenerator::getConstrainedDelaunayTriangulation(std::vector<PointSegment> restrictedSegments) {
    if(!this->empty){
        char switches[] = "pzejQ";
        callTriangle(seedPoints, switches, restrictedSegments);
    }

    return initializeMesh<Triangle>();
}
