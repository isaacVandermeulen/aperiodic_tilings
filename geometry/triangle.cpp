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

std::ostream& Triangle::oriented_path(std::ostream& os) const
{
    Point p_a = m_a*0.5+m_b*0.25+m_c*0.25;
    Point p_b = m_a*0.25+m_b*0.5+m_c*0.25;
    Point p_c = m_a*0.25+m_b*0.25+m_c*0.5;
    os << "\\draw[->]" << p_a << "--" << p_b << "--" << p_c << ";" << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
    os << "\\draw[" << t.label() << "]" << t.m_a << "--" << t.m_b << "--" << t.m_c << "--cycle; \\\\" << t.area() << std::endl;
    //t.oriented_path(os);
    return os;
}

std::ostream& Triangle::print_seahorse(std::ostream& os) const
{
    return os;
}

std::ostream& Triangle::print_rhombus(std::ostream& os) const
{
    if (m_area > 0) {
        const Point d = m_b + m_c + m_a*-1;
        os << "\\draw[" << label() << "]" << m_a << "--" << m_b << "--" << d << "--" << m_c << "--cycle;" << std::endl;
    }
    return os;
}

std::ostream& Triangle::print_kite(std::ostream& os) const
{
    if (m_area > 0) {
        Point delta_b = m_b + m_a*-1;
        Point delta_c = m_c + m_a*-1;
        const float dot = delta_b.x*delta_c.x + delta_b.y*delta_c.y;
        const float norm = delta_b.x*delta_b.x + delta_b.y*delta_b.y;
        Point projection = m_a + (delta_b)*dot*(1/norm);
        Point e = projection*2 + m_c*-1;
        os << "\\draw[" << label() << "]" << m_a << "--" << m_c << "--" << m_b << "--" << e << "--cycle;" << std::endl;
    }
    return os;
}
