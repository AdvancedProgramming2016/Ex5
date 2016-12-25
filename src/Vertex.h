
#ifndef EX1_TASK2_VERTEX_H
#define EX1_TASK2_VERTEX_H


#include "Point.h"
#include <vector>

/**
 * The class represents a vertex in a graph.
 * Contains a Point and list of its relationships with other vertices.
 */
class Vertex {

private:
    Point                 m_point;
    int                   m_num_of_relations;
    bool                  m_is_visited;
    Vertex                *m_father;
    std::vector<Vertex *> m_relationships;

public:

    /*
     * Constructor of Vertex with only a point
     */
    Vertex(Point point);

    /*
     * The method returns a Point
     */
    const Point &getM_point() const;

    /*
     *The method returns the relationship vector
     */
    std::vector<Vertex *> &getM_relations_list();

    /*
     * The method adds a new vertex to the relationship vector
     */
    void add_relation(Vertex &vertex);

    /*
     * The method reserves space for the relationship vector
     */
    void set_relations_num(int num);

    /*
     * The method returns the number of vertices in the relationship vector
     */
    int getNum_of_relations() const;

    /*
     * The method returns whether the vertex was visited
     */
    bool isM_is_visited() const;

    /*
     * The method sets the visited mode to true
     */
    void set_visited();

    /*
     * The method returns the father vertex of the given vertex
     */
    Vertex *getFather() const;

    /*
     * The method sets a father for the vertex
     */
    void setFather(Vertex &father);

};


#endif //EX1_TASK2_VERTEX_H
