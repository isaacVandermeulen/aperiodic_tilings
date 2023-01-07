#pragma once

#include "../geometry/triangle.hpp"

namespace heptagonal {

// Should have internal angles 3*pi/7, 3*pi/7, 1*pi/7 
class TallTriangle : public Triangle
{
public:
    TallTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override;
private:
    std::string label() const override;
};

} // end heptagonal namespace
