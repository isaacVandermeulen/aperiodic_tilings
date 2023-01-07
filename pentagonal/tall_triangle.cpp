#include "tall_triangle.hpp"

#include "constants.hpp"
#include "wide_triangle.hpp"

#include <cmath>

namespace pentagonal {

TallTriangle::TallTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> TallTriangle::split(const float scale) const
{
    const auto d = m_a*(1-phi_inv)+m_b*phi_inv;
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<WideTriangle>(d*scale, m_c*scale, m_a*scale));
    result.push_back(std::make_unique<TallTriangle>(m_c*scale, d*scale, m_b*scale));
    return result;
}

std::string TallTriangle::label() const
{
    return "tallPentagonal";
}

std::ostream& TallTriangle::print_seahorse(std::ostream& os) const
{
    if (m_area < 0) {
        float r = sqrt(m_a.y*m_a.y + m_a.x*m_a.x);
        float theta = atan2(m_a.y, m_a.x)*180/M_PI;
        float alpha = atan2(m_c.y-m_a.y, m_c.x-m_a.x)*180/M_PI;
        os << "\\bigSeahorse{color\\one}{(" << theta << "+72*\\x:" << r << ")}{" << alpha << "+72*\\x}" << std::endl;
    }
    return os;
}

} // end pentagonal namespace
