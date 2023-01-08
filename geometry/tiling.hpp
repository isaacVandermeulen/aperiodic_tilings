#pragma once

#include "triangle.hpp"

class Tiling
{
public:
    void split(const size_t iterations, const float scale = 1);
    void print_latex_file(const std::string& filename) const;

protected:
    std::vector<std::unique_ptr<Triangle>> m_triangles;

    Tiling() = default;

    virtual void print_tikz_styles(std::ostream& os) const = 0;
    virtual size_t symmetry_number() const = 0;
private:
    void split_once(const float scale);
};
