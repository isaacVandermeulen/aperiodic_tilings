#pragma once

#include "../geometry/triangle.hpp"

namespace heptagonal {

// Should have internal angles 1*pi/7, 2*pi/7, 4*pi/7 
// Same as Scalane triangle but with reversed orientation. In this
// case we need a separate class since the angles are different.
// For an isoceles triangle we can reverse the orientation by
// entering the points in order (a, c, b)
class ReverseTriangle : public Triangle
{
public:
    ReverseTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override;
    std::ostream& oriented_path(std::ostream& os) const override;
private:
    std::string label() const override;
};

} // end heptagonal namespace
