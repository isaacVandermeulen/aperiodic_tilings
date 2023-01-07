#pragma once

#include "../geometry/tiling.hpp"

namespace pentagonal {

class PentagonalTiling : public Tiling
{
public:
    PentagonalTiling();

protected:
    void print_start_of_latex_file(std::ostream& os) const override;
    void print_end_of_latex_file(std::ostream& os) const override;
};

} // end pentagonal tiling
