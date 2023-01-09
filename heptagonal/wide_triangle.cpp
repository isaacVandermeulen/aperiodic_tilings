#include "wide_triangle.hpp"

#include "constants.hpp"
#include "scalene_triangle.hpp"
#include "tall_triangle.hpp"
#include "middle_triangle.hpp"

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

static std::vector<std::unique_ptr<Triangle>> split_multi_1(const Point& a, const Point& b, const Point& c)
{
    const auto d = c*(chi*psi)+b*(chi); // closer to b
    const auto e = b*(chi*psi)+c*(chi); // closer to c
    const auto f = b*(chi*chi*psi*psi)+a*(psi); // closer to a
    const auto g = c*(chi*chi*psi*psi)+a*(psi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(a, d, e));
    result.push_back(std::make_unique<TallTriangle>(b, f, d));
    result.push_back(std::make_unique<TallTriangle>(c, g, e));
    result.push_back(std::make_unique<ScaleneTriangle>(d, a, f));
    result.push_back(std::make_unique<ScaleneTriangle>(e, a, g));
    return result;
}

static std::vector<std::unique_ptr<Triangle>> split_multi_2(const Point& a, const Point& b, const Point& c)
{
    const auto d = b*(chi/psi)+c*(chi*chi); // closer to b
    const auto e = c*(chi/psi)+b*(chi*chi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<MiddleTriangle>(a, d, e));
    result.push_back(std::make_unique<WideTriangle>(d, b, a));
    result.push_back(std::make_unique<WideTriangle>(e, a, c));
    return result;
}

std::vector<std::unique_ptr<Triangle>> WideTriangle::split(const float scale) const
{
    //return split_1(m_a, m_b, m_c);
    //return split_1(m_a, m_c, m_b);
    //return split_2(m_a, m_b, m_c);
    //return split_2(m_a, m_c, m_b);
    return split_multi_1(m_a, m_c, m_b);
    //return split_multi_2(m_a, m_c, m_b);
}

std::string WideTriangle::label() const
{
    return "wideHeptagonal";
}

} // end heptagonal namespace
