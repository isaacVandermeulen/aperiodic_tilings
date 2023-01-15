#pragma once

#include "../geometry/triangle.hpp"

namespace heptagonal {

// Should have internal angles 1*pi/7, 2*pi/7, 4*pi/7 
class ReverseTriangle : public Triangle
{
public:
    ReverseTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override;
private:
    std::string label() const override;
};

} // end heptagonal namespace
