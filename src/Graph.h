
#ifndef EX1_TASK2_GRAPH_H
#define EX1_TASK2_GRAPH_H

#include "Vertex.h"
#include <vector>
#include <list>

/**
 * The class represents the data structure "Graph".
 * It contains the edges of the graph, which contain vertices.
 */
class Graph {

protected:
    std::vector<Vertex> m_edges;

public:

    /*
     * The method returns the edges vector
     */
    std::vector<Vertex> get_edges();

    /*
     * The method returns a vertex from a given point on the graph
     */
    Vertex *get_vertex(Point point);

};


#endif //EX1_TASK2_GRAPH_H
