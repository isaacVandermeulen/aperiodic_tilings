#include "penrose.hpp"
#include "heptagonal/tall_triangle.hpp"
#include "pentagonal/tall_triangle.hpp"
#include <fstream>

constexpr float phi = 1.618033988749894;
constexpr float phi_inv = phi-1;

constexpr float alpha = 1.8019377358048383;
constexpr float beta = 1.2469796037174672;

Tiling::Tiling(std::vector<std::unique_ptr<Triangle>>& initial_triangles)
{
    for (auto& triangle : initial_triangles) {
        m_triangles.push_back(std::move(triangle));
    }
}

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

void Tiling::print(const std::string& filename)
{
    std::ofstream file;
    file.open (filename);
    for (const auto& triangle : m_triangles) {
        file << *triangle;
    }
}

int main()
{
    std::vector<std::unique_ptr<Triangle>> triangles;
    //triangles.push_back(std::make_unique<pentagonal::TallTriangle>(Point(0,0), Point(phi, 0), Point(phi*cos(36*M_PI/180), phi*sin(36*M_PI/180))));
    //triangles.push_back(std::make_unique<pentagonal::TallTriangle>(Point(0,0), Point(phi, 0), Point(phi*cos(-36*M_PI/180), phi*sin(-36*M_PI/180))));
    triangles.push_back(std::make_unique<heptagonal::TallTriangle>(Point(0,0), Point(alpha*beta,0), Point(alpha*beta*cos(M_PI/7), alpha*beta*sin(M_PI/7))));
    triangles.push_back(std::make_unique<heptagonal::TallTriangle>(Point(0,0), Point(alpha*beta,0), Point(alpha*beta*cos(-M_PI/7), alpha*beta*sin(-M_PI/7))));

    const size_t iterations = 23;
    const float scale = 1;
    const std::string filename = "./latex/heptagonal_data.tex";

    Tiling penrose_triangles(triangles);
    penrose_triangles.split(iterations, scale);
    penrose_triangles.print(filename);
    return 0;
}
