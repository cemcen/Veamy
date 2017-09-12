#include <delynoi/models/hole/clipper/ClipperWrapper.h>

ClipperLib::Paths ClipperWrapper::polyIntersection(std::vector<Point> parent, std::vector<Point> child, int maxScale) {
    ClipperLib::Path region, hole;
    ClipperLib::Paths solution;

    for(int i=0;i<parent.size(); i++){
        region << scalePoint(parent[i], maxScale);
    }

    for(int i=0;i<child.size();i++){
        hole << scalePoint(child[i], maxScale);
    }

    ClipperLib::Clipper clipper;
    clipper.AddPath(region, ClipperLib::ptSubject, true);
    clipper.AddPath(hole, ClipperLib::ptClip, true);
    clipper.Execute(ClipperLib::ctDifference, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

    return solution;
}

ClipperLib::IntPoint ClipperWrapper::scalePoint(Point point, int maxScale) {
    return ClipperLib::IntPoint((int)(maxScale*point.getX()), (int)(maxScale*point.getY()));
}


