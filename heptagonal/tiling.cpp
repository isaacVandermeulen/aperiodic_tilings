#include "tiling.hpp"

#include "constants.hpp"
#include "tall_triangle.hpp"

#include <cmath>
#include <fstream>

namespace heptagonal {

HeptagonalTiling::HeptagonalTiling()
{
    const float scale = 10;
    m_triangles.push_back(std::make_unique<heptagonal::TallTriangle>(Point(0,0), Point(scale*alpha*beta,0), Point(scale*alpha*beta*cos(M_PI/7), scale*alpha*beta*sin(M_PI/7))));
    m_triangles.push_back(std::make_unique<heptagonal::TallTriangle>(Point(0,0), Point(scale*alpha*beta,0), Point(scale*alpha*beta*cos(-M_PI/7), scale*alpha*beta*sin(-M_PI/7))));
}

void HeptagonalTiling::print_tikz_styles(std::ostream& os) const
{
    os << "    \\tikzset{wideHeptagonal/.style={triangle=olive!90!black}}" << std::endl;
    os << "    \\tikzset{middleHeptagonal/.style={triangle=olive!70!white}}" << std::endl;
    os << "    \\tikzset{tallHeptagonal/.style={triangle=olive!30!white}}" << std::endl;
    os << "    \\tikzset{reverseHeptagonal/.style={triangle=olive!50!white}}" << std::endl;
    os << "    \\tikzset{scaleneHeptagonal/.style={triangle=olive!15!white}}" << std::endl;
}

size_t HeptagonalTiling::symmetry_number() const
{
    return 7;
}

} // end heptagonal namespace
