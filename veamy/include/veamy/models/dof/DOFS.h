#ifndef VEAMY_DOFS_H
#define VEAMY_DOFS_H

#include <array>
#include <algorithm>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/models/constraints/ConstraintsContainer.h>

/*
 * Class that contains all the degrees of freedom of the system
 */
class DOFS {
protected:
    /*
     * List with all DOF instances
     */
    UniqueList<DOF> list;

    /*
     * Map relating point and the first DOF assigned to it
     */
    std::unordered_map<int, int> occupied_point_indexes;

    /*
     * Number of degrees of freedom per point
     */
    int n_dofs;
public:
    /*
     * Constructor
     */
    DOFS();

    /*
     * Adds a new DOF associated to a point
     * @param constraints constraints conditions of the system
     * @param points mesh points
     * @param point_index index of the point which DOF will be created
     * @param pair pair of segments containing the point (so that segment constraints can be checked)
     * @return list with the indexes of the created DOF
     */
    std::vector<int> addDOF(ConstraintsContainer &constraints, std::vector<Point> &points, int point_index,
                            SegmentPair pair);

    /*
     *@return list with all DOF instances
     */
    UniqueList<DOF> getDOFS() const;

    /*
     *@return a reference to the list with all DOF instances
     */
    UniqueList<DOF>& getDOFS();

    /*
     * @return number of DOF contained
     */
    int size();

    /* Returns the DOF at a given index
     * @param i index
     * @return DOF at the i-th position
     */
    DOF get(int i);

    /* Returns the DOF indexes associated to a point
     * @param point point to lookup
     * @return list with the indexes of the DOFs associated to point
     */
    std::vector<int> pointToDOFS(int point);

    /* Sets the number of degrees of freedom per point
     * @param n_dofs number to set
     */
    void setNumberOfDOFS(int n_dofs);

    /*
     * @return number of degrees of freedom per point
     */
    int getNumberOfDOFS();
};


#endif
