#include "tiling.hpp"

#include "constants.hpp"
#include "tall_triangle.hpp"

#include <cmath>
#include <fstream>

namespace pentagonal {

PentagonalTiling::PentagonalTiling()
{
    m_triangles.push_back(std::make_unique<pentagonal::TallTriangle>(Point(0,0), Point(phi, 0), Point(phi*cos(36*M_PI/180), phi*sin(36*M_PI/180))));
    m_triangles.push_back(std::make_unique<pentagonal::TallTriangle>(Point(0,0), Point(phi, 0), Point(phi*cos(-36*M_PI/180), phi*sin(-36*M_PI/180))));
}

void PentagonalTiling::print_tikz_styles(std::ostream& os) const
{
    os << "    \\tikzset{widePentagonal/.style={triangle=violet!80!black}}" << std::endl;
    os << "    \\tikzset{tallPentagonal/.style={triangle=violet!60!white}}" << std::endl;
}

size_t PentagonalTiling::symmetry_number() const
{
    return 5;
}

} // end pentagonal namespace
