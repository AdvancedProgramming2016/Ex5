
#include "Vertex.h"

Vertex::Vertex(Point point) : m_point(point), m_num_of_relations(0),
                              m_father(0) {

}

void Vertex::add_relation(Vertex &vertex) {

    m_relationships.push_back(&vertex);
    m_num_of_relations++;
}

const Point &Vertex::getM_point() const {
    return m_point;
}

std::vector<Vertex *> &Vertex::getM_relations_list() {
    return m_relationships;
}

void Vertex::set_relations_num(int num) {

    m_relationships.reserve(num);

}

int Vertex::getNum_of_relations() const {
    return m_num_of_relations;
}

bool Vertex::isM_is_visited() const {
    return m_is_visited;
}

void Vertex::set_visited() {
    Vertex::m_is_visited = true;
}

Vertex *Vertex::getFather() const {
    return m_father;
}

void Vertex::setFather(Vertex &father) {
    Vertex::m_father = &father;
}





