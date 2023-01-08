#include "wide_triangle.hpp"

#include "constants.hpp"
#include "scalene_triangle.hpp"
#include "tall_triangle.hpp"

namespace heptagonal {

WideTriangle::WideTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

static std::vector<std::unique_ptr<Triangle>> split_1(const Point& a, const Point& b, const Point& c)
{
    const auto d = b*(chi*psi)+c*(chi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(b, a, d));
    result.push_back(std::make_unique<ScaleneTriangle>(c, a, d));
    return result;
}

static std::vector<std::unique_ptr<Triangle>> split_2(const Point& a, const Point& b, const Point& c)
{
    const auto d = c*(chi/psi)+b*(chi*chi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<ScaleneTriangle>(b, d, a));
    result.push_back(std::make_unique<WideTriangle>(d, a, c));
    return result;
}

std::vector<std::unique_ptr<Triangle>> WideTriangle::split(const float scale) const
{
    return split_1(m_a, m_b, m_c);
    //return split_1(m_a, m_c, m_b);
    //return split_2(m_a, m_b, m_c);
    //return split_2(m_a, m_c, m_b);
}

std::string WideTriangle::label() const
{
    return "wideHeptagonal";
}

} // end heptagonal namespace
