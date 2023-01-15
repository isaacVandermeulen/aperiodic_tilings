#include "heptagonal/tiling.hpp"
#include "pentagonal/tiling.hpp"

int main()
{
    const size_t iterations = 10;
    const float scale = 1;
    //const std::string filename = "./latex/pentagonal.tex";
    const std::string filename = "./latex/heptagonal.tex";

    heptagonal::HeptagonalTiling tiling;
    //pentagonal::PentagonalTiling tiling;
    tiling.split(iterations, scale);
    tiling.print_latex_file(filename);
    return 0;
}
