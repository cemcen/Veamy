#include "delynoi/voronoi/DelaunayToVoronoi.h"

DelaunayToVoronoi::DelaunayToVoronoi(DelaunayInfo& del) {
    SegmentMap* voronoiEdges = new SegmentMap;
    PointMap* pointMap = new PointMap;
    std::vector<Polygon> voronoiCells;

    for(int i=0;i<del.realPoints.size(); i++) {
        int cellIndex = voronoiCells.size();
        std::vector<IndexSegment> thisEdges;

        int index = del.realPoints[i];
        UniqueList<int> cellPoints;
        Point regionCenter = del.meshPoints[index];
        EdgeData init_edge = del.edges[del.points[index].edge];

        int t1 = init_edge.t1;
        int t2 = init_edge.t2;

        int index1 = getCircumcenter(del, t1,del.points[index].edge);
        int index2 = getCircumcenter(del, t2,del.points[index].edge);

        if(index1!=index2){
            IndexSegment e (index2,index1);
            thisEdges.push_back(e);
            voronoiEdges->insert(e, cellIndex);

            cellPoints.push_back(index2);
            pointMap->insert(del.circumcenters[index2], cellIndex);
        }

        cellPoints.push_back(index1);
        pointMap->insert(del.circumcenters[index1], cellIndex);

        EdgeData edge = del.edges[del.triangles[t1].nextEdge(index, init_edge, del.edgeMap)];

        while(!(edge==init_edge)){
            t2 = t1;
            t1 = edge.t1!=t2? edge.t1 : edge.t2;

            int currentEdge = del.edgeMap[Key(edge.p1, edge.p2)];

            index1 = getCircumcenter(del,t1,currentEdge);
            index2 = getCircumcenter(del,t2,currentEdge);

            if(index1!=index2){
                IndexSegment e (index2, index1);

                thisEdges.push_back(e);
                voronoiEdges->insert(e, cellIndex);

                cellPoints.push_back(index2);
                pointMap->insert(del.circumcenters[index2], cellIndex);
            }

            cellPoints.push_back(index1);
            pointMap->insert(del.circumcenters[index1], cellIndex);

            if(t1!=-1){
                edge = del.edges[del.triangles[t1].nextEdge(index, edge, del.edgeMap)];
            }else{
                break;
            }
        }

        if(edge.t2==-1){
            int firstPoint = cellPoints[0];
            int lastPoint = cellPoints[cellPoints.size()-1];

            if(geometry_functions::collinear(del.circumcenters[firstPoint],regionCenter,del.circumcenters[lastPoint])){
                IndexSegment e (lastPoint, firstPoint);
                thisEdges.push_back(e);

                voronoiEdges->insert(e, cellIndex);
            } else{
                regionCenter.setBoundary();
                int regionIndex = del.circumcenters.push_back(regionCenter);

                cellPoints.push_back(regionIndex);
                pointMap->insert(del.circumcenters[regionIndex], cellIndex);

                IndexSegment e1(lastPoint, regionIndex);
                IndexSegment e2(regionIndex, firstPoint);

                thisEdges.push_back(e1);
                voronoiEdges->insert(e1, cellIndex);

                thisEdges.push_back(e2);
                voronoiEdges->insert(e2, cellIndex);
            }
        }

        std::vector<Point>& pointList = del.circumcenters.getList();
        std::vector<int>& cellPointsList = cellPoints.getList();

        Polygon p = Polygon(cellPointsList, pointList);
        p.fixCCW(pointList);

        voronoiCells.push_back(p);
    }

    UniqueList<Point>& points = del.circumcenters;

    this->mesh = Mesh<Polygon>(points, voronoiCells, voronoiEdges, pointMap);
}


int DelaunayToVoronoi::getCircumcenter(DelaunayInfo& del, int triangle, int edge) {
    if(triangle!=-1){
        return del.triangles[triangle].getCircumcenterIndex();
    }else{
        Point middlePoint = IndexSegment(del.edges[edge].p1, del.edges[edge].p2).middlePoint(del.meshPoints);
        middlePoint.setBoundary();

        int circumcenterIndex = del.circumcenters.push_back(middlePoint);

        return circumcenterIndex;
    }
}

Mesh<Polygon>& DelaunayToVoronoi::getMesh() {
    return this->mesh;
}
