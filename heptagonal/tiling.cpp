#include "tiling.hpp"

#include "constants.hpp"
#include "tall_triangle.hpp"

#include <cmath>
#include <fstream>

namespace heptagonal {

HeptagonalTiling::HeptagonalTiling()
{
    m_triangles.push_back(std::make_unique<heptagonal::TallTriangle>(Point(0,0), Point(alpha*beta,0), Point(alpha*beta*cos(M_PI/7), alpha*beta*sin(M_PI/7))));
    m_triangles.push_back(std::make_unique<heptagonal::TallTriangle>(Point(0,0), Point(alpha*beta,0), Point(alpha*beta*cos(-M_PI/7), alpha*beta*sin(-M_PI/7))));
}

void HeptagonalTiling::print_start_of_latex_file(std::ostream& os) const
{
    os << "\\documentclass[border=0.1cm]{standalone}" << std::endl;
    os << "    \\usepackage{tikz}" << std::endl;
    os << "    \\tikzset{wideHeptagonal/.style={line join=round,fill=orange!80!black}}" << std::endl;
    os << "    \\tikzset{middleHeptagonal/.style={line join=round,fill=orange}}" << std::endl;
    os << "    \\tikzset{tallHeptagonal/.style={line join=round,fill=orange!60!white}}" << std::endl;
    os << "    \\tikzset{scaleneHeptagonal/.style={line join=round,fill=orange!80!white}}" << std::endl;
    os << "\\begin{document}" << std::endl;
    os << std::endl;
    os << "\\begin{tikzpicture}" << std::endl;
    os << "\\foreach" << std::endl;
    os << "\\x in {0,1,2,3,4,5,6}{" << std::endl;
    os << "\\begin{scope}[rotate around={51.4285714286*\\x:((0,0))}]" << std::endl;
}

void HeptagonalTiling::print_end_of_latex_file(std::ostream& os) const
{
    os << "\\end{scope}" << std::endl;
    os << "}" << std::endl;
    os << std::endl;
    os << "\\end{tikzpicture}" << std::endl;
    os << "\\end{document}" << std::endl;
}

} // end heptagonal namespace
