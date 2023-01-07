#include "middle_triangle.hpp"

#include "constants.hpp"
#include "scalene_triangle.hpp"
#include "tall_triangle.hpp"

namespace heptagonal {

MiddleTriangle::MiddleTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> MiddleTriangle::split(const float scale) const
{
    const auto d = m_b*(1.0/(beta*alpha))+m_a*(1.0/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(m_c*scale, m_a*scale, d*scale));
    result.push_back(std::make_unique<ScaleneTriangle>(m_c*scale, m_b*scale, d*scale));
    return result;
}

std::string MiddleTriangle::label() const
{
    return "middleHeptagonal";
}

} // end heptagonal namespace
