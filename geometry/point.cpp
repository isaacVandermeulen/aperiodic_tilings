#include "point.hpp"

Point::Point(const float _x, const float _y)
    : x(_x)
    , y(_y)
{}

Point Point::operator*(const float scale) const
{
    return Point(scale*x, scale*y);
}

Point Point::operator+(const Point& that) const
{
    return Point(x+that.x, y+that.y);
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
