#include "wide_triangle.hpp"

#include "constants.hpp"
#include "reverse_triangle.hpp"
#include "scalene_triangle.hpp"
#include "tall_triangle.hpp"
#include "middle_triangle.hpp"

namespace heptagonal {

WideTriangle::WideTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

static std::vector<std::unique_ptr<Triangle>> split_triangle(const Point& a, const Point& b, const Point& c)
{
    const auto d = c*(chi*psi)+b*(chi); // closer to b
    const auto e = b*(chi*psi)+c*(chi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(b, e, a));
    result.push_back(std::make_unique<ScaleneTriangle>(c, a, e));
    return result;
}

std::vector<std::unique_ptr<Triangle>> WideTriangle::split(const float scale) const
{
    return split_triangle(m_a, m_c, m_b);
}

std::string WideTriangle::label() const
{
    return "wideHeptagonal";
}

} // end heptagonal namespace
