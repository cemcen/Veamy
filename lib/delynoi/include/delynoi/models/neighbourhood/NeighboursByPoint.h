#ifndef DELYNOI_NEIGHBOURSBYPOINT_H
#define DELYNOI_NEIGHBOURSBYPOINT_H

#include <vector>

/*
 * Class that models polygon neighbourhood by point, meaning, it lists all polygons (referred by their indexes) that share
 * a point.
 */
class NeighboursByPoint {
private:
    /*
     * List of neighbours
     */
    std::vector<int> neighbours;
public:
    /*
     * Default constructor
     */
    NeighboursByPoint();

    /*
     * Constructor. Receives one neighbour
     */
    NeighboursByPoint(int n);

    /*
     * Constructor. Receives a list of neighbours
     */
    NeighboursByPoint(std::vector<int> n);

    /* Adds a new neighbour to the list
     * @param n neighbour to add
     */
    void add(int n);

    /* Adds a list of neighbours to the class list
     * @param n list of neighbours to add
     */
    void insert(std::vector<int> n);

    /*
     * @return list of neighbours
     */
    std::vector<int> getNeighbours() const;

    /*
     * @return reference to the list of neighbours
     */
    std::vector<int>& getNeighbours();
};

#endif