#include <mesher/voronoi/TriangleMeshGenerator.h>

TriangleMeshGenerator::TriangleMeshGenerator(std::vector<Point>& point_list, Region region) {
    this->region = region;
    char switches[] = "pzeDQ";
    callTriangle(point_list, std::vector<PointSegment>(), switches);
}

TriangleMeshGenerator::TriangleMeshGenerator(std::vector<Point> &point_list, Region region,
                                             std::vector<PointSegment> restrictedSegments) {
    this->region = region;
    char switches[] = "pzeQ";
    callTriangle(point_list, restrictedSegments, switches);
}

TriangleMeshGenerator::~TriangleMeshGenerator() {}

PolygonalMesh TriangleMeshGenerator::getMesh() {
    if(!this->mesh.isFull()){
        this->mesh = delaunayToVoronoi();
    }

    return this->mesh;
}

Triangulation TriangleMeshGenerator::getDelaunayTriangulation() {
    return Triangulation(this->meshPoints, this->triangles, delaunayEdges);
}

void TriangleMeshGenerator::callTriangle(std::vector<Point> &point_list, std::vector<PointSegment> restrictedSegments,
                                         char switches[]) {
    struct triangulateio in, out;

    std::vector<Point> regionPoints = region.getRegionPoints();
    UniqueList<Point> pointList;
    pointList.push_list(point_list);
    std::vector<int> regionIndex = pointList.push_list(regionPoints);

    writeInputInFile(pointList, region, regionIndex);

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
        Neighbours neighbours(data.t1, data.t2);

        this->delaunayEdges.insert(segment, neighbours);
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

PolygonalMesh TriangleMeshGenerator::delaunayToVoronoi() {
    for(int i=0;i<this->realPoints.size(); i++) {
        std::vector<IndexSegment> thisEdges;

        int index = this->realPoints[i];
        UniqueList<int> cellPoints;
        Point regionCenter = this->meshPoints[index];
        EdgeData init_edge = this->edges[this->points[index].edge];

        int t1 = init_edge.t1;
        int t2 = init_edge.t2;

        Point c1 = getCircumcenter(t1,this->points[index].edge,meshPoints);
        Point c2 = getCircumcenter(t2,this->points[index].edge,meshPoints);

        int index1 = voronoiPoints.push_back(c1);
        int index2 = voronoiPoints.push_back(c2);

        if(index1!=index2){
            IndexSegment e (index2,index1);
            thisEdges.push_back(e);

            cellPoints.push_back(index2);
        }

        cellPoints.push_back(index1);
        EdgeData edge = this->edges[triangles[t1].nextEdge(index, init_edge, edgeMap)];

        while(!(edge==init_edge)){
            t2 = t1;
            t1 = edge.t1!=t2? edge.t1 : edge.t2;

            int currentEdge = edgeMap[Key(edge.p1, edge.p2)];

            c1 = getCircumcenter(t1,currentEdge,meshPoints);
            c2 = getCircumcenter(t2,currentEdge,meshPoints);

            index1 = voronoiPoints.push_back(c1);
            index2 = voronoiPoints.push_back(c2);

            if(index1!=index2){
                IndexSegment e (index2, index1);
                thisEdges.push_back(e);

                cellPoints.push_back(index2);
            }

            cellPoints.push_back(index1);

            if(t1!=-1){
                edge = this->edges[triangles[t1].nextEdge(index, edge, edgeMap)];
            }else{
                break;
            }
        }

        if(edge.t2==-1){
            int firstPoint = cellPoints[0];
            int lastPoint = cellPoints[cellPoints.size()-1];

            if(geometry_functions::collinear(voronoiPoints[firstPoint],regionCenter,voronoiPoints[lastPoint])){
                IndexSegment e (lastPoint, firstPoint);
                thisEdges.push_back(e);
            } else{
                regionCenter.setBoundary();
                int regionIndex = voronoiPoints.push_back(regionCenter);
                cellPoints.push_back(regionIndex);

                IndexSegment e1(lastPoint, regionIndex);
                IndexSegment e2(regionIndex, firstPoint);

                thisEdges.push_back(e1);
                thisEdges.push_back(e2);
            }
        }

        std::vector<Point> pointList = voronoiPoints.getList();
        std::vector<int> cellPointsList = cellPoints.getList();

        Polygon p = Polygon(cellPointsList, pointList);
        p.fixCCW(pointList);

        int cellIndex = this->voronoiCells.push_back(p);

        for (int j = 0; j < thisEdges.size(); ++j) {
            voronoiEdges.insert(thisEdges[j], cellIndex);
        }
    }

    std::vector<Point> points = this->voronoiPoints.getList();
    std::vector<Polygon> cells = this->voronoiCells.getList();

    edges.clear();
    this->points.clear();
    realPoints.getList().clear();
    edgeMap.clear();

    return PolygonalMesh(points, cells, voronoiEdges, this->region);
}

Point TriangleMeshGenerator::getCircumcenter(int triangle, int edge, std::vector<Point> &points) {
    if(triangle!=-1){
        return this->triangles[triangle].getCircumcenter();
    }else{
        Point middlePoint = IndexSegment(this->edges[edge].p1, this->edges[edge].p2).middlePoint(points);
        middlePoint.setBoundary();

        return middlePoint;
    }
}

void
TriangleMeshGenerator::writeInputInFile(UniqueList<Point> &point_list, Region region, std::vector<int> regionIndex) {
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

