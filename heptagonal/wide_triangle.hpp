#pragma once

#include "../geometry/triangle.hpp"

namespace heptagonal {

// Should have internal angles pi/7, pi/7, 5*pi/7 
class WideTriangle : public Triangle
{
public:
    WideTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override;
private:
    std::string label() const override;
};

} // end heptagonal namespace
