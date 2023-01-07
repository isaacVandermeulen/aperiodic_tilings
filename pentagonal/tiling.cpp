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

void PentagonalTiling::print_start_of_latex_file(std::ostream& os) const
{
    os << "\\documentclass[border=0.1cm]{standalone}" << std::endl;
    os << "    \\usepackage{tikz}" << std::endl;
    os << "    \\tikzset{widePentagonal/.style={ultra thin, line join=round,fill=violet!80!black}}" << std::endl;
    os << "    \\tikzset{tallPentagonal/.style={ultra thin, line join=round,fill=violet!60!white}}" << std::endl;
    os << "\\begin{document}" << std::endl;
    os << std::endl;
    os << "\\begin{tikzpicture}" << std::endl;
    os << "\\foreach" << std::endl;
    os << "\\x in {0,1,2,3,4}{" << std::endl;
    os << "\\begin{scope}[rotate around={72*\\x:((0,0))}]" << std::endl;
}

void PentagonalTiling::print_end_of_latex_file(std::ostream& os) const
{
    os << "\\end{scope}" << std::endl;
    os << "}" << std::endl;
    os << std::endl;
    os << "\\end{tikzpicture}" << std::endl;
    os << "\\end{document}" << std::endl;
}

} // end pentagonal namespace
