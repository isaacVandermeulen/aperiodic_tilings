#include "reverse_triangle.hpp"

#include "constants.hpp"
#include "middle_triangle.hpp"
#include "tall_triangle.hpp"
#include "wide_triangle.hpp"

namespace heptagonal {

ReverseTriangle::ReverseTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

static std::vector<std::unique_ptr<Triangle>> split_triangle(const Point& a, const Point& b, const Point& c)
{
    const auto d = b*(chi*psi)+a*(chi); // closer to a
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<WideTriangle>(d, c, a));
    result.push_back(std::make_unique<MiddleTriangle>(c, b, d));
    return result;
}

std::vector<std::unique_ptr<Triangle>> ReverseTriangle::split(const float scale) const
{
    return split_triangle(m_a, m_b, m_c);
}

std::string ReverseTriangle::label() const
{
    return "reverseHeptagonal";
}

std::ostream& ReverseTriangle::oriented_path(std::ostream& os) const
{
    Point p_a = m_a*0.5+m_b*0.25+m_c*0.25;
    Point p_b = m_a*0.25+m_b*0.5+m_c*0.25;
    Point p_c = m_a*0.25+m_b*0.25+m_c*0.5;
    os << "\\draw[->]" << p_a << "--" << p_c << "--" << p_b << ";" << std::endl;
    return os;
}



} // end heptagonal namespace
