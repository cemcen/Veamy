#include <veamy/models/constraints/ConstraintsContainer.h>
#include <utilities/maputils.h>

ConstraintsContainer::ConstraintsContainer() {
    this->natural = NaturalConstraints();
    this->essential = EssentialConstraints();
}

void ConstraintsContainer::addConstrainedDOF(std::vector<Point> &points, int DOF_index, int axis, SegmentPair pair,
                                             int point_index) {
    natural.addConstrainedDOF(points, DOF_index, axis, pair, point_index);
    essential.addConstrainedDOF(points, DOF_index, axis, pair, point_index);
}

EssentialConstraints& ConstraintsContainer::getEssentialConstraints() {
    return essential;
}

NaturalConstraints& ConstraintsContainer::getNaturalConstraints() {
    return natural;
}

EssentialConstraints ConstraintsContainer::getEssentialConstraints() const{
    return essential;
}

NaturalConstraints ConstraintsContainer::getNaturalConstraints() const{
    return natural;
}

bool ConstraintsContainer::areConsistent(NaturalConstraints n, EssentialConstraints e, UniqueList<Point> &points) {
    Point inter;
    std::vector<IndexSegment> naturalSegments;
    std::transform(n.getConstrainedSegments().begin(), n.getConstrainedSegments().end(), std::back_inserter(naturalSegments), map_utils::GetKeys());

    std::vector<IndexSegment> essentialSegments;
    std::transform(e.getConstrainedSegments().begin(), e.getConstrainedSegments().end(), std::back_inserter(essentialSegments), map_utils::GetKeys());

    for (int i = 0; i < naturalSegments.size(); ++i) {
        for (int j = 0; j < essentialSegments.size(); ++j) {
            if(naturalSegments[i].intersection(points.getList(),essentialSegments[j],inter)){
                return false;
            }
        }
    }

    return true;
}

