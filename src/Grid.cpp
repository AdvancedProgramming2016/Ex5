
#include "Grid.h"

Grid::Grid(unsigned int length, unsigned int width,
           std::vector<Point> &obstacles) : m_length(length), m_width(width),
                                            obstacles(obstacles) {

    for (int i = length - 1; i >= 0; i--) {

        for (int j = 0; j < width; ++j) {

            Vertex v = Vertex(Point(i, j));
            v.set_relations_num(4);
            m_edges.push_back(v);
        }
    }

    build_relations();
    this->insertObstacles();

}

void Grid::build_relations() {

    int counter = 0;

    for (int i = m_length - 1; i >= 0; i--) {

        for (int j = 0; j < m_width; ++j) {

            if (i > 0) {

                //upper relationship
                m_edges.at(counter).add_relation(*get_vertex(Point(i - 1, j)));
            }

            if (j < m_width - 1) {

                //right relationship
                m_edges.at(counter).add_relation(*get_vertex(Point(i, j + 1)));
            }

            if (i < m_length - 1) {

                //lower relationship
                m_edges.at(counter).add_relation(*get_vertex(Point(i + 1, j)));
            }

            if (j > 0) {

                //left relationship
                m_edges.at(counter).add_relation(*get_vertex(Point(i, j - 1)));
            }

            counter++;
        }
    }
}

void Grid::insertObstacles() {
    int i = 0;
    std::vector<Point> obstacleVec = this->getObstacles();

    // Mark all obstacles on grid as visited
    for (i = 0; i < obstacleVec.size(); i++) {
        this->get_vertex(obstacleVec.at(i))->set_visited();
    }
}

const std::vector<Point> &Grid::getObstacles() const {
    return obstacles;
}

bool Grid::isObstacle(const Point &point) {

    for (int i = 0; i < this->obstacles.size(); ++i) {

        if(obstacles[i] == point){
            return true;
        }
    }

    return false;
}

