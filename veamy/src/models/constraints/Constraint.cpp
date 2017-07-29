#include <veamy/models/constraints/Constraint.h>
#include <assert.h>


Constraint::Constraint() {}

Constraint::Constraint(IndexSegment s, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
    this->constraints.push_back(s);
}

Constraint::Constraint(std::vector<IndexSegment> s, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
    this->constraints.push_list(s);
}

Constraint::Constraint(PointSegment s, std::vector<Point> points, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
    IndexSegment int_segment = fromPointToInt(s, points);
    this->constraints.push_back(int_segment);
}

Constraint::Constraint(PointSegment s, UniqueList<Point> points, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
    IndexSegment int_segment = fromPointToInt(s, points.getList());
    this->constraints.push_back(int_segment);
}

Constraint::Constraint(std::vector<PointSegment> s, std::vector<Point> points, Constraint::Direction d,
                       ConstraintValue *value) {
    this->v = value;
    this->direction = d;

    for(int i = 0; i<s.size(); i++){
        IndexSegment int_segment = fromPointToInt(s[i], points);
        this->constraints.push_back(int_segment);
    }
}

Constraint::Constraint(std::vector<PointSegment> s, UniqueList<Point> points, Constraint::Direction d,
                       ConstraintValue *value) {
    this->v = value;
    this->direction = d;

    for(int i = 0; i<s.size(); i++){
        IndexSegment int_segment = fromPointToInt(s[i], points.getList());
        this->constraints.push_back(int_segment);
    }
}

double Constraint::getValue(Point p) {
    return v->getValue(p);
}

Constraint::Direction Constraint::getDirection() {
    return direction;
}

UniqueList<IndexSegment> Constraint::getSegments() {
    return this->constraints;
}

IndexSegment Constraint::fromPointToInt(PointSegment s, std::vector<Point> points) {
    int p1 = utilities::indexOf(points, s.getFirst());
    int p2 = utilities::indexOf(points, s.getSecond());

    if(p1<0 || p2<0){
        throw std::invalid_argument("Please don't go around making up nonexistent points");
    }

    return IndexSegment(p1, p2);
}

int Constraint::isAffected(DOF::Axis axis) {
    switch (direction){
        case Total:
            return 1;
        case Horizontal:
            return axis == DOF::Axis::x? 1 : 0;
        case Vertical:
            return axis == DOF::Axis::y? 1 : 0;
    }
}



