#pragma once

#include "../geometry/tiling.hpp"

namespace heptagonal {

class HeptagonalTiling : public Tiling
{
public:
    HeptagonalTiling();

protected:
    void print_tikz_styles(std::ostream& os) const override;
    size_t symmetry_number() const override;
};

} // end heptagonal tiling
