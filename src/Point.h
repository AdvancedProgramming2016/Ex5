
#ifndef EX1_TASK2_POINT_H
#define EX1_TASK2_POINT_H

#include <iostream>

/**
* The class "Point" is supposed to represent a point in a two dimensional space.
* Contains two axis, x and y.
*
*/
class Point {

private:
    int m_x;
    int m_y;

public:

    /*
     * Constructor of a specific 2D point.
     */
    Point(int x, int y);

    int getXCoordinate();

    int getYCoordinate();

    /*
     * Overloads the "==" operator in order to evaluate two Points.
     */
    friend bool operator==(Point p1, Point p2);

    /*
     * Overloads the "!=" operator in order to evaluate two Points.
     */
    friend bool operator!=(Point p1, Point p2);

    /*
     * Overloads the ostream operator in order to print a Point directly.
     */
    friend std::ostream &operator<<(std::ostream &os, const Point &point);

};


#endif //EX1_TASK2_POINT_H
