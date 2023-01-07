#include "penrose.hpp"
#include "heptagonal/tall_triangle.hpp"
#include "pentagonal/tall_triangle.hpp"
#include <fstream>

constexpr float phi = 1.618033988749894;
constexpr float phi_inv = phi-1;

constexpr float alpha = 1.8019377358048383;
constexpr float beta = 1.2469796037174672;

PenroseTriangles::PenroseTriangles(std::vector<std::unique_ptr<Triangle>>& initial_triangles)
{
    for (auto& triangle : initial_triangles) {
        m_triangles.push_back(std::move(triangle));
    }
}

void PenroseTriangles::split(const size_t iterations, const float scale)
{
    for (size_t i = 0; i != iterations; ++i) {
        std::vector<std::unique_ptr<Triangle>> subdivided_triangles;
        const float largest_area = m_triangles.front()->area();
        const float eps = 1e-6;
        for (auto& triangle : m_triangles) {
            if (std::abs(largest_area-triangle->area()) > eps) {
                break;
            }
            auto subdivided = triangle->split(scale);
            for (auto& subdivided_triangle : subdivided) {
                subdivided_triangles.push_back(std::move(subdivided_triangle));
            }
            triangle = nullptr;
        }
        m_triangles.erase(std::remove(m_triangles.begin(), m_triangles.end(), nullptr), m_triangles.end());
        for (auto& triangle : subdivided_triangles) {
            m_triangles.push_back(std::move(triangle));
        }
        std::sort(m_triangles.begin(),m_triangles.end(), 
                [](const std::unique_ptr<Triangle>& triangle_0, 
                   const std::unique_ptr<Triangle>& triangle_1) {
                return triangle_0->area() > triangle_1->area();});
    }
}

void PenroseTriangles::print(const std::string& filename)
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

    PenroseTriangles penrose_triangles(triangles);
    penrose_triangles.split(iterations, scale);
    penrose_triangles.print(filename);
    return 0;
}
