#include "tiling.hpp"

#include <cmath>
#include <fstream>

static std::vector<std::unique_ptr<Triangle>> get_largest_triangles(std::vector<std::unique_ptr<Triangle>>& sorted_triangles)
{
    std::vector<std::unique_ptr<Triangle>> largest_triangles;
    const float largest_area = sorted_triangles.front()->area();
    const float eps = 1e-4*largest_area;
    for (auto& triangle : sorted_triangles) {
        if (std::abs(largest_area-triangle->area()) < eps) {
            largest_triangles.push_back(std::move(triangle));
        } else {
            break;
        }
    }
    sorted_triangles.erase(std::remove(sorted_triangles.begin(), sorted_triangles.end(), nullptr), sorted_triangles.end());
    return largest_triangles;
}

static std::vector<std::unique_ptr<Triangle>> split_triangles(const std::vector<std::unique_ptr<Triangle>>& input_triangles, const float scale = 1)
{
    std::vector<std::unique_ptr<Triangle>> result;
    for (const auto& triangle : input_triangles) {
        auto subdivided = triangle->split(scale);
        for (auto& subdivided_triangle : subdivided) {
            result.push_back(std::move(subdivided_triangle));
        }
    }
    return result;
}

static void sort_by_area(std::vector<std::unique_ptr<Triangle>>& triangles)
{
    std::sort(triangles.begin(), triangles.end(),
            [](const std::unique_ptr<Triangle>& triangle_0,
               const std::unique_ptr<Triangle>& triangle_1) {
            return triangle_0->area() > triangle_1->area();});
}

void Tiling::split_once(const float scale)
{
    sort_by_area(m_triangles);
    const auto largest_triangles = get_largest_triangles(m_triangles);
    auto subdivided_triangles = split_triangles(largest_triangles, scale);
    for (auto& triangle : subdivided_triangles) {
        m_triangles.push_back(std::move(triangle));
    }
}

void Tiling::split(const size_t iterations, const float scale)
{
    for (size_t i = 0; i != iterations; ++i) {
        split_once(scale);
    }
}

void Tiling::print_latex_file(const std::string& filename) const
{
    std::ofstream file;
    file.open (filename);
    file << "\\documentclass[border=0.1cm]{standalone}" << std::endl;
    file << "    \\usepackage{tikz}" << std::endl;
    file << "    \\tikzset{triangle/.style={ultra thin, line join=round, fill=#1}}" << std::endl;
    print_tikz_styles(file);
    file << "\\begin{document}" << std::endl;
    file << std::endl;
    file << "\\begin{tikzpicture}" << std::endl;
    file << "\\foreach" << std::endl;
    file << "\\x in {0,1,...," << symmetry_number()-1 << "}{" << std::endl;
    file << "\\begin{scope}[rotate around={" << 360.0/symmetry_number() << "*\\x:((0,0))}]" << std::endl;
    for (const auto& triangle : m_triangles) {
        file << *triangle;
    }
    file << "\\end{scope}" << std::endl;
    file << "}" << std::endl;
    file << std::endl;
    file << "\\end{tikzpicture}" << std::endl;
    file << "\\end{document}" << std::endl;
}
