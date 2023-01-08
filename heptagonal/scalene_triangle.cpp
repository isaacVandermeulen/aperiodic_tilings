#include "scalene_triangle.hpp"

#include "constants.hpp"
#include "middle_triangle.hpp"
#include "tall_triangle.hpp"
#include "wide_triangle.hpp"

namespace heptagonal {

ScaleneTriangle::ScaleneTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

static std::vector<std::unique_ptr<Triangle>> split_1(const Point& a, const Point& b, const Point& c)
{
    const auto d = b*(1/(alpha*beta))+a*(1/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<WideTriangle>(d, a, c));
    result.push_back(std::make_unique<MiddleTriangle>(c, d, b));
    return result;
}

static std::vector<std::unique_ptr<Triangle>> split_2(const Point& a, const Point& b, const Point& c)
{
    const auto d = a*(1/(alpha*alpha*beta*beta))+b*(1/beta);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<ScaleneTriangle>(c, b, d));
    result.push_back(std::make_unique<TallTriangle>(a, d, c));
    return result;
}

static std::vector<std::unique_ptr<Triangle>> split_3(const Point& a, const Point& b, const Point& c)
{
    const auto d = a*(1/(alpha*beta*beta))+b*(1/(beta*beta));
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<ScaleneTriangle>(a, c, d));
    result.push_back(std::make_unique<MiddleTriangle>(d, b, c));
    return result;
}

static std::vector<std::unique_ptr<Triangle>> split_4(const Point& a, const Point& b, const Point& c)
{
    const auto d = a*(1/(alpha*alpha))+c*(beta/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<ScaleneTriangle>(b, d, c));
    result.push_back(std::make_unique<WideTriangle>(d, a, b));
    return result;
}

std::vector<std::unique_ptr<Triangle>> ScaleneTriangle::split(const float scale) const
{
    //return split_1(m_a, m_b, m_c);
    //return split_2(m_a, m_b, m_c);
    //return split_3(m_a, m_b, m_c);
    return split_4(m_a, m_b, m_c);
}

std::string ScaleneTriangle::label() const
{
    return "scaleneHeptagonal";
}

} // end heptagonal namespace
