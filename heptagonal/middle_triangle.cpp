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
    const auto d = c*(chi*psi)+a*(chi); // closer to a
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(b, a, d));
    result.push_back(std::make_unique<ScaleneTriangle>(b, c, d));
    return result;
}

static std::vector<std::unique_ptr<Triangle>> split_2(const Point& a, const Point& b, const Point& c)
{
    const auto d = c*(chi*psi*psi)+b*(psi*psi); // closer to b
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<MiddleTriangle>(d, a, c));
    result.push_back(std::make_unique<ScaleneTriangle>(a, b, d));
    return result;
}

static std::vector<std::unique_ptr<Triangle>> split_multi(const Point& a, const Point& b, const Point& c)
{
    const auto d = c*(chi*psi*psi)+b*(psi*psi); // closer to b
    const auto e = b*(chi*psi*psi)+c*(psi*psi); // closer to c
    const auto f = a*(chi*chi*psi*psi)+b*(psi); // closer to b
    const auto g = a*(chi*chi*psi*psi)+c*(psi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(a, f, d));
    result.push_back(std::make_unique<TallTriangle>(a, e, d));
    result.push_back(std::make_unique<TallTriangle>(a, e, g));
    result.push_back(std::make_unique<ScaleneTriangle>(d, b, f));
    result.push_back(std::make_unique<ScaleneTriangle>(e, c, g));
    return result;
}

std::vector<std::unique_ptr<Triangle>> MiddleTriangle::split(const float scale) const
{
    //return split_1(m_a, m_b, m_c);
    //return split_1(m_a, m_c, m_b);
    //return split_2(m_a, m_b, m_c);
    //return split_2(m_a, m_c, m_b);
    return split_multi(m_a, m_c, m_b);
}

std::string MiddleTriangle::label() const
{
    return "middleHeptagonal";
}

} // end heptagonal namespace
