#include "tall_triangle.hpp"

#include "constants.hpp"
#include "middle_triangle.hpp"
#include "reverse_triangle.hpp"
#include "scalene_triangle.hpp"
#include "wide_triangle.hpp"

namespace heptagonal {

TallTriangle::TallTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

static std::vector<std::unique_ptr<Triangle>> split_triangle(const Point& a, const Point& b, const Point& c)
{
    const auto d = a*(chi*chi*psi*psi)+c*(psi); // closer to c
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<ReverseTriangle>(a, b, d));
    result.push_back(std::make_unique<TallTriangle>(b, c, d));
    return result;
}

std::vector<std::unique_ptr<Triangle>> TallTriangle::split(const float scale) const
{
    return split_triangle(m_a, m_b, m_c);
}

std::string TallTriangle::label() const
{
    return "tallHeptagonal";
}

} // end heptagonal namespace
