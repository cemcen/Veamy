#include <veamy/models/constraints/Constraints.h>

void Constraints::addConstraint(SegmentConstraint c, std::vector<Point> p) {
    UniqueList<IndexSegment> segments = c.getSegments();

    for (int i = 0; i < segments.size(); ++i) {
        IndexSegment s = segments[i];
        Angle angle(s.cartesianAngle(p));

        std::vector<IndexSegment>& v = constrained_segments[angle];
        v.push_back(s);

        std::vector<SegmentConstraint>& relatedConstraints = segment_map[segments[i]];
        relatedConstraints.push_back(c);
    }
}

void Constraints::addConstraint(SegmentConstraint c, UniqueList<Point> p) {
    addConstraint(c, p.getList());
}

void Constraints::addConstraint(PointConstraint c) {
    UniqueList<Point> points = c.getPoints();

    for (int i = 0; i < points.size(); ++i) {
        std::vector<PointConstraint>& relatedConstraints = point_map[points[i]];
        relatedConstraints.push_back(c);
    }
}

isConstrainedInfo Constraints::isConstrainedBySegment(std::vector <Point> points, IndexSegment s) {
    Angle angle(s.cartesianAngle(points));
    auto iter = constrained_segments.find(angle);

    if(iter == constrained_segments.end())
        return isConstrainedInfo();

    std::vector<IndexSegment> segments = iter->second;

    for (int i = 0; i < segments.size(); ++i) {
        if(segments[i].contains(points,s)){
            return isConstrainedInfo(segments[i]);
        }
    }

    return isConstrainedInfo();
}

isConstrainedInfo Constraints::isConstrainedByPoint(Point p) {
    auto iter = point_map.find(p);

    if(iter == point_map.end()){
        return isConstrainedInfo();
    }

    return isConstrainedInfo(true);
}

bool Constraints::isConstrained(int dof) {
    return constrained_dofs.contains(dof);
}

std::vector<int> Constraints::getConstrainedDOF() {
    return constrained_dofs.getList();
}

void Constraints::addConstrainedDOF(std::vector <Point> points, int DOF_index, DOF::Axis axis, SegmentPair pair,
                                    int dof_point) {
    bool added1 = addConstrainedDOFBySegment(points, DOF_index, axis, pair.s1);
    bool added2 = addConstrainedDOFBySegment(points, DOF_index, axis, pair.s2);
    bool added3 = addConstrainedDOFByPoint(DOF_index, axis, points[dof_point]);
}

bool Constraints::addConstrainedDOFBySegment(std::vector<Point> points, int DOF_index, DOF::Axis axis, IndexSegment s) {
    isConstrainedInfo info = isConstrainedBySegment(points, s);

    if(info.isConstrained){
        std::vector<SegmentConstraint> constraints = segment_map[info.container];

        for (SegmentConstraint constraint: constraints) {
            Constraint::Direction direction = constraint.getDirection();

            bool insert;

            switch(direction){
                case(Constraint::Direction::Vertical):
                    insert = axis==DOF::Axis::y;
                    break;
                case (Constraint::Direction::Horizontal):
                    insert = axis==DOF::Axis::x;
                    break;
                default:
                    insert = true;
            }

            if(insert){
                constrained_dofs.push_back(DOF_index);
                segment_constraints_map[DOF_index] = constraint;
                return true;
            }
        }
        return false;
    }
    return false;
}

bool Constraints::addConstrainedDOFByPoint(int DOF_index, DOF::Axis axis, Point p) {
    auto iter = point_map.find(p);

    if(iter != point_map.end()){
        std::vector<PointConstraint> constraints = iter->second;

        for(PointConstraint constraint: constraints){
            Constraint::Direction direction = constraint.getDirection();
            bool insert;

            switch(direction){
                case(Constraint::Direction::Vertical):
                    insert = axis==DOF::Axis::y;
                    break;
                case (Constraint::Direction::Horizontal):
                    insert = axis==DOF::Axis::x;
                    break;
                default:
                    insert = true;
            }

            if(insert){
                constrained_dofs.push_back(DOF_index);
                point_constraints_map[DOF_index] = constraint;
            }
        }

        return false;
    }

    return false;
}

std::unordered_map<IndexSegment, std::vector<SegmentConstraint>, SegmentHasher> Constraints::getConstrainedSegments() {
    return this->segment_map;
}

Constraint Constraints::getAssociatedConstraint(int dof_index) {
    auto iter = segment_constraints_map.find(dof_index);

    if(iter != segment_constraints_map.end()){
        return iter->second;
    }

    auto iter2 = point_constraints_map.find(dof_index);
    if(iter2 != point_constraints_map.end()){
        return iter2->second;
    }

    return Constraint();
}

