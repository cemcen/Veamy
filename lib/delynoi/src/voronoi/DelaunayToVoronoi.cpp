#include "delynoi/voronoi/DelaunayToVoronoi.h"

DelaunayToVoronoi::DelaunayToVoronoi(DelaunayInfo del) {
    UniqueList<Point> voronoiPoints;
    SegmentMap voronoiEdges;
    PointMap pointMap;
    UniqueList<Polygon> voronoiCells;

    for(int i=0;i<del.realPoints.size(); i++) {
        std::vector<IndexSegment> thisEdges;

        int index = del.realPoints[i];
        UniqueList<int> cellPoints;
        Point regionCenter = del.meshPoints[index];
        EdgeData init_edge = del.edges[del.points[index].edge];

        int t1 = init_edge.t1;
        int t2 = init_edge.t2;

        Point c1 = getCircumcenter(del, t1,del.points[index].edge);
        Point c2 = getCircumcenter(del, t2,del.points[index].edge);

        int index1 = voronoiPoints.push_back(c1);
        int index2 = voronoiPoints.push_back(c2);

        if(index1!=index2){
            IndexSegment e (index2,index1);
            thisEdges.push_back(e);

            cellPoints.push_back(index2);
        }

        cellPoints.push_back(index1);
        EdgeData edge = del.edges[del.triangles[t1].nextEdge(index, init_edge, del.edgeMap)];

        while(!(edge==init_edge)){
            t2 = t1;
            t1 = edge.t1!=t2? edge.t1 : edge.t2;

            int currentEdge = del.edgeMap[Key(edge.p1, edge.p2)];

            c1 = getCircumcenter(del,t1,currentEdge);
            c2 = getCircumcenter(del,t2,currentEdge);

            index1 = voronoiPoints.push_back(c1);
            index2 = voronoiPoints.push_back(c2);

            if(index1!=index2){
                IndexSegment e (index2, index1);
                thisEdges.push_back(e);

                cellPoints.push_back(index2);
            }

            cellPoints.push_back(index1);

            if(t1!=-1){
                edge = del.edges[del.triangles[t1].nextEdge(index, edge, del.edgeMap)];
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

        int cellIndex = voronoiCells.push_back(p);

        for (int j = 0; j < thisEdges.size(); ++j) {
            voronoiEdges.insert(thisEdges[j], cellIndex);
        }

        for (int k = 0; k < cellPoints.size(); ++k) {
            pointMap.insert(voronoiPoints[cellPoints[k]], cellIndex);
        }
    }

    std::vector<Point> points = voronoiPoints.getList();
    std::vector<Polygon> cells = voronoiCells.getList();

    this->mesh = Mesh<Polygon>(points, cells, voronoiEdges, pointMap);
}


Point DelaunayToVoronoi::getCircumcenter(DelaunayInfo del, int triangle, int edge) {
    if(triangle!=-1){
        return del.triangles[triangle].getCircumcenter();
    }else{
        Point middlePoint = IndexSegment(del.edges[edge].p1, del.edges[edge].p2).middlePoint(del.meshPoints);
        middlePoint.setBoundary();

        return middlePoint;
    }
}

Mesh<Polygon> DelaunayToVoronoi::getMesh() {
    return this->mesh;
}
