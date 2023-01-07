#include "scalene_triangle.hpp"

#include "constants.hpp"
#include "middle_triangle.hpp"
#include "wide_triangle.hpp"

namespace heptagonal {

ScaleneTriangle::ScaleneTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> ScaleneTriangle::split(const float scale) const
{
    const auto d = m_b*(1/(alpha*beta))+m_a*(1/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<WideTriangle>(d*scale, m_a*scale, m_c*scale));
    result.push_back(std::make_unique<MiddleTriangle>(m_c*scale, d*scale, m_b*scale));
    return result;
}

std::string ScaleneTriangle::label() const
{
    return "scaleneHeptagonal";
}

} // end heptagonal namespace
