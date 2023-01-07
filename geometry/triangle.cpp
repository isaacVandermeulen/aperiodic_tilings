#include "triangle.hpp"
#include <fstream>
#include <cmath>

Triangle::Triangle(const Point& a, const Point& b, const Point& c)
    : m_a(a)
    , m_b(b)
    , m_c(c)
{
    m_area = (m_b.x-m_a.x)*(m_c.y-m_a.y) - (m_c.x-m_a.x)*(m_b.y-m_a.y);
}

float Triangle::area() const
{
    return std::abs(m_area);
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
    os << "\\draw[" << t.label() << "]" << t.m_a << "--" << t.m_b << "--" << t.m_c << "--cycle;" << std::endl;
    return os;
}

std::ostream& Triangle::print_seahorse(std::ostream& os) const
{
    return os;
}
