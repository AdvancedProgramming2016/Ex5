
#ifndef EX1_TASK2_GRID_H
#define EX1_TASK2_GRID_H

#include "Graph.h"

/**
 * The class represents a 2D grid.
 * It inherits from the Graph class.
 */
class Grid : public Graph {

private:
    int                m_length;
    int                m_width;
    std::vector<Point> obstacles;

    /*
     * The method builds the relations between the cells of the grid.
     */
    void build_relations();

public:

    /*
     * Constructor which receives the size of the matrix.
     */
    Grid(unsigned int length, unsigned int width,
         std::vector<Point> &obstacles);

    /*
     * Returns the obstacles that appear on the map.
     */
    const std::vector<Point> &getObstacles() const;

};


#endif //EX1_TASK2_GRID_H
