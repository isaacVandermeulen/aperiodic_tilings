#include "wide_triangle.hpp"

#include "constants.hpp"
#include "scalene_triangle.hpp"
#include "tall_triangle.hpp"

namespace heptagonal {

WideTriangle::WideTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> WideTriangle::split(const float scale) const
{
    const auto d = m_b*(1.0/(beta*alpha))+m_c*(1.0/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(m_b*scale, m_a*scale, d*scale));
    result.push_back(std::make_unique<ScaleneTriangle>(m_c*scale, m_a*scale, d*scale));
    return result;
}

std::string WideTriangle::label() const
{
    return "wideHeptagonal";
}

} // end heptagonal namespace
