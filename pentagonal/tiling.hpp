#pragma once

#include "../geometry/tiling.hpp"

namespace pentagonal {

class PentagonalTiling : public Tiling
{
public:
    PentagonalTiling();

protected:
    void print_tikz_styles(std::ostream& os) const override;
    size_t symmetry_number() const override;
};

} // end pentagonal tiling
