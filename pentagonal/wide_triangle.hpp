#pragma once

#include "../geometry/triangle.hpp"

namespace pentagonal {

// Should have internal angles 36, 36, 72 
class WideTriangle : public Triangle
{
public:
    WideTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override; 
    std::ostream& print_seahorse(std::ostream& os) const override;
private:
    std::string label() const override;
};

} // end pentagonal namespace
