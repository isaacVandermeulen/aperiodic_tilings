#include "scalene_triangle.hpp"

#include "constants.hpp"
#include "middle_triangle.hpp"
#include "tall_triangle.hpp"
#include "wide_triangle.hpp"

namespace heptagonal {

ScaleneTriangle::ScaleneTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

static std::vector<std::unique_ptr<Triangle>> split_triangle(const Point& a, const Point& b, const Point& c)
{
    const auto d = b*(chi*psi)+a*(chi); // closer to a
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<WideTriangle>(d, a, c));
    result.push_back(std::make_unique<MiddleTriangle>(c, d, b));
    return result;
}

std::vector<std::unique_ptr<Triangle>> ScaleneTriangle::split(const float scale) const
{
    return split_triangle(m_a, m_b, m_c);
}

std::string ScaleneTriangle::label() const
{
    return "scaleneHeptagonal";
}

} // end heptagonal namespace
