#pragma once

#include "../geometry/tiling.hpp"

namespace heptagonal {

class HeptagonalTiling : public Tiling
{
public:
    HeptagonalTiling();

protected:
    void print_start_of_latex_file(std::ostream& os) const override;
    void print_end_of_latex_file(std::ostream& os) const override;
};

} // end heptagonal tiling
