#include <veamy/models/constraints/Constraints.h>

void Constraints::addConstraint(Constraint c, std::vector<Point> p) {
    UniqueList<IndexSegment> segments = c.getSegments();

    for (int i = 0; i < segments.size(); ++i) {
        IndexSegment s = segments[i];
        Angle angle(s.cartesianAngle(p));

        std::vector<IndexSegment>& v = constrained_segments[angle];
        v.push_back(s);

        std::vector<Constraint>& relatedConstraints = segment_map[segments[i]];
        relatedConstraints.push_back(c);
    }
}

void Constraints::addConstraint(Constraint c, UniqueList<Point> p) {
    addConstraint(c, p.getList());
}

isConstrainedInfo Constraints::isConstrained(std::vector<Point> points, IndexSegment s) {
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

bool Constraints::isConstrained(int dof) {
    return constrained_dofs.contains(dof);
}

std::vector<int> Constraints::getConstrainedDOF() {
    return constrained_dofs.getList();
}

void Constraints::addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair pair) {
    addConstrainedDOFBySegment(points, DOF_index, axis, pair.s1);
    addConstrainedDOFBySegment(points, DOF_index, axis, pair.s2);
}

void Constraints::addConstrainedDOFBySegment(std::vector<Point> points, int DOF_index, DOF::Axis axis, IndexSegment s) {
    isConstrainedInfo info = isConstrained(points, s);

    if(info.isConstrained){
        std::vector<Constraint> constraints = segment_map[info.container];

        for (Constraint constraint: constraints) {
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
                constraints_map.insert(std::pair<int,Constraint>(DOF_index, constraint));
            }
        }
    }
}

std::unordered_map<IndexSegment, std::vector<Constraint>, SegmentHasher> Constraints::getConstrainedSegments() {
    return this->segment_map;
}

