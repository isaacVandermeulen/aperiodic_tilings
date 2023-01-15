#include "middle_triangle.hpp"

#include "constants.hpp"
#include "reverse_triangle.hpp"
#include "scalene_triangle.hpp"
#include "tall_triangle.hpp"

namespace heptagonal {

MiddleTriangle::MiddleTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

static std::vector<std::unique_ptr<Triangle>> split_triangle(const Point& a, const Point& b, const Point& c)
{
    const auto d = a*(chi)+c*(chi*psi); // closer to a
    const auto e = b*(chi*psi*psi)+c*(psi*psi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(b, d, a));
    result.push_back(std::make_unique<ScaleneTriangle>(b, d, e));
    result.push_back(std::make_unique<MiddleTriangle>(e, c, d));
    return result;
}

std::vector<std::unique_ptr<Triangle>> MiddleTriangle::split(const float scale) const
{
    return split_triangle(m_a, m_b, m_c);
}

std::string MiddleTriangle::label() const
{
    return "middleHeptagonal";
}

} // end heptagonal namespace
