#include "middle_triangle.hpp"

#include "constants.hpp"
#include "scalene_triangle.hpp"
#include "tall_triangle.hpp"

namespace heptagonal {

MiddleTriangle::MiddleTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

static std::vector<std::unique_ptr<Triangle>> split_1(const Point& a, const Point& b, const Point& c)
{
    const auto d = c*(1.0/(beta*alpha))+a*(1.0/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(b, a, d));
    result.push_back(std::make_unique<ScaleneTriangle>(b, c, d));
    return result;
}

static std::vector<std::unique_ptr<Triangle>> split_2(const Point& a, const Point& b, const Point& c)
{
    const auto d = c*(1.0/(beta*beta*alpha))+b*(1.0/(beta*beta));
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<MiddleTriangle>(d, a, c));
    result.push_back(std::make_unique<ScaleneTriangle>(a, b, d));
    return result;
}

std::vector<std::unique_ptr<Triangle>> MiddleTriangle::split(const float scale) const
{
    return split_1(m_a, m_b, m_c);
    //return split_1(m_a, m_c, m_b);
    //return split_2(m_a, m_b, m_c);
    //return split_2(m_a, m_c, m_b);
}

std::string MiddleTriangle::label() const
{
    return "middleHeptagonal";
}

} // end heptagonal namespace
