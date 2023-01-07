#include "tiling.hpp"

#include <cmath>
#include <fstream>

static std::vector<std::unique_ptr<Triangle>> get_largest_triangles(std::vector<std::unique_ptr<Triangle>>& sorted_triangles)
{
    std::vector<std::unique_ptr<Triangle>> largest_triangles;
    const float largest_area = sorted_triangles.front()->area();
    const float eps = 1e-6;
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
    print_start_of_latex_file(file); 
    for (const auto& triangle : m_triangles) {
        file << *triangle;
    }
    print_end_of_latex_file(file); 
}
