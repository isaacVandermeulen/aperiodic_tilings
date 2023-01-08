#include "tall_triangle.hpp"

#include "constants.hpp"
#include "middle_triangle.hpp"
#include "scalene_triangle.hpp"
#include "wide_triangle.hpp"

namespace heptagonal {

TallTriangle::TallTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

static std::vector<std::unique_ptr<Triangle>> split_1(const Point& a, const Point& b, const Point& c)
{
    const auto d = a*(chi*psi)+c*(chi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<WideTriangle>(d, b, a));
    result.push_back(std::make_unique<MiddleTriangle>(c, d, b));
    return result;
}

static std::vector<std::unique_ptr<Triangle>> split_2(const Point& a, const Point& b, const Point& c)
{
    const auto d = a*(chi*chi*psi*psi)+c*(psi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<ScaleneTriangle>(a, b, d));
    result.push_back(std::make_unique<TallTriangle>(b, d, c));
    return result;
}

std::vector<std::unique_ptr<Triangle>> TallTriangle::split(const float scale) const
{
    return split_1(m_a, m_b, m_c);
    //return split_1(m_a, m_c, m_b);
    //return split_2(m_a, m_b, m_c);
    //return split_2(m_a, m_c, m_b);
}

std::string TallTriangle::label() const
{
    return "tallHeptagonal";
}

} // end heptagonal namespace
