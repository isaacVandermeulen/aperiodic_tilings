#pragma once

#include <iostream>

struct Point 
{
    const float x;
    const float y;

    Point(const float _x, const float _y);
    Point operator*(const float scale) const;
    Point operator+(const Point& that) const;

};

std::ostream& operator<<(std::ostream& os, const Point& p);
