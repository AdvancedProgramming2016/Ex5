
#include "Point.h"

Point::Point(int x, int y) : m_x(x), m_y(y) {}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    return os << '(' << point.m_x << "," << point.m_y << ')';
}

int Point::getXCoordinate() {
    return this->m_x;
}

int Point::getYCoordinate() {
    return this->m_y;
}

bool operator==(Point p1, Point p2) {
    return ((p1.m_x == p2.m_x) && (p1.m_y == p2.m_y));
}

bool operator!=(Point p1, Point p2) {
    return !(p1 == p2);
}


