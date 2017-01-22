
#ifndef EX1_TASK2_BFS_H
#define EX1_TASK2_BFS_H

#include "../graphs/Graph.h"
#include "../graphs/Grid.h"

/**
 * The class represents the BFS algorithm.
 * It iterates through the graph in order the find the shortest path between two given points.
 *
 */
class Bfs {

private:
    Grid              m_graph;
    Point              m_source;
    Point              m_dest;
    std::vector<Point> shortest_path;

    /*
     * The method iterates through the fathers and returns the final path
     */
    std::vector<Point> search_fathers(std::vector<Vertex> vector);

public:

    /*
     * constructor for the bfs algorithm
     */
    Bfs(Grid graph, Point source, Point dest);

    /*
     * The method calculates the shortest path between two points.
     */
    void get_route();

    /*
     * Returns the shortest path from source to dest path.
     */
    std::vector<Point> &getShortestPath();

    /*
     * Prints the points of the shortest path
     */
    void print_points();

};


#endif //EX1_TASK2_BFS_H
