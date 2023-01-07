#include "wide_triangle.hpp"

#include "constants.hpp"
#include "tall_triangle.hpp"

#include <cmath>

namespace pentagonal {

WideTriangle::WideTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> WideTriangle::split(const float scale) const
{
    const auto d = m_b*(1-phi_inv)+m_c*phi_inv;
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallTriangle>(m_b*scale, m_a*scale, d*scale));
    result.push_back(std::make_unique<WideTriangle>(d*scale, m_c*scale, m_a*scale));
    return result;
}

std::string WideTriangle::label() const
{
    return "widePentagonal";
}

std::ostream& WideTriangle::print_seahorse(std::ostream& os) const
{
    if (m_area > 0) {
        float r = sqrt(m_b.y*m_b.y + m_b.x*m_b.x);
        float theta = atan2(m_b.y, m_b.x)*180/M_PI;
        float alpha = atan2(m_c.y-m_b.y, m_c.x-m_b.x)*180/M_PI;
        os << "\\smallSeahorse{color\\one}{(" << theta << "+72*\\x:" << r << ")}{" << alpha << "+72*\\x}" << std::endl;
    }
    return os;
}

} // end pentagonal namespace
