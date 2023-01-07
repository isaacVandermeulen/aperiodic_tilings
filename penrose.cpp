#include "./penrose.hpp"
#include <fstream>

constexpr float phi = 1.618033988749894;
constexpr float phi_inv = phi-1;

constexpr float alpha = 1.8019377358048383;
constexpr float beta = 1.2469796037174672;

WidePentagonalTriangle::WidePentagonalTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> WidePentagonalTriangle::split(const float scale) const
{
    const auto d = m_b*(1-phi_inv)+m_c*phi_inv;
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallPentagonalTriangle>(m_b*scale, m_a*scale, d*scale));
    result.push_back(std::make_unique<WidePentagonalTriangle>(d*scale, m_c*scale, m_a*scale));
    return result;
}

std::string WidePentagonalTriangle::label() const
{
    return "widePentagonal";
}

std::ostream& WidePentagonalTriangle::print_seahorse(std::ostream& os) const
{
    if (m_area > 0) {
        float r = sqrt(m_b.y*m_b.y + m_b.x*m_b.x);
        float theta = atan2(m_b.y, m_b.x)*180/M_PI;
        float alpha = atan2(m_c.y-m_b.y, m_c.x-m_b.x)*180/M_PI;
        os << "\\smallSeahorse{color\\one}{(" << theta << "+72*\\x:" << r << ")}{" << alpha << "+72*\\x}" << std::endl;
    }
    return os;
}

TallPentagonalTriangle::TallPentagonalTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> TallPentagonalTriangle::split(const float scale) const
{
    const auto d = m_a*(1-phi_inv)+m_b*phi_inv;
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<WidePentagonalTriangle>(d*scale, m_c*scale, m_a*scale));
    result.push_back(std::make_unique<TallPentagonalTriangle>(m_c*scale, d*scale, m_b*scale));
    return result;
}

std::string TallPentagonalTriangle::label() const
{
    return "tallPentagonal";
}

std::ostream& TallPentagonalTriangle::print_seahorse(std::ostream& os) const
{
    if (m_area < 0) {
        float r = sqrt(m_a.y*m_a.y + m_a.x*m_a.x);
        float theta = atan2(m_a.y, m_a.x)*180/M_PI;
        float alpha = atan2(m_c.y-m_a.y, m_c.x-m_a.x)*180/M_PI;
        os << "\\bigSeahorse{color\\one}{(" << theta << "+72*\\x:" << r << ")}{" << alpha << "+72*\\x}" << std::endl;
    }
    return os;
}

WideHeptagonalTriangle::WideHeptagonalTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> WideHeptagonalTriangle::split(const float scale) const
{
    const auto d = m_b*(1.0/(beta*alpha))+m_c*(1.0/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallHeptagonalTriangle>(m_b*scale, d*scale, m_a*scale));
    result.push_back(std::make_unique<ScaleneHeptagonalTriangle>(m_c*scale, m_a*scale, d*scale));
    return result;
}

std::string WideHeptagonalTriangle::label() const
{
    return "wideHeptagonal";
}

MiddleHeptagonalTriangle::MiddleHeptagonalTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> MiddleHeptagonalTriangle::split(const float scale) const
{
    const auto d = m_b*(1.0/(beta*alpha))+m_a*(1.0/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<TallHeptagonalTriangle>(m_c*scale, d*scale, m_a*scale));
    result.push_back(std::make_unique<ScaleneHeptagonalTriangle>(m_c*scale, m_b*scale, d*scale));
    return result;
}

std::string MiddleHeptagonalTriangle::label() const
{
    return "middleHeptagonal";
}

TallHeptagonalTriangle::TallHeptagonalTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> TallHeptagonalTriangle::split(const float scale) const
{
    const auto d = m_a*(1/(alpha*beta))+m_b*(1/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<WideHeptagonalTriangle>(d*scale, m_c*scale, m_a*scale));
    result.push_back(std::make_unique<MiddleHeptagonalTriangle>(m_b*scale, d*scale, m_c*scale));
    return result;
}

std::string TallHeptagonalTriangle::label() const
{
    return "tallHeptagonal";
}

ScaleneHeptagonalTriangle::ScaleneHeptagonalTriangle(const Point& a, const Point& b, const Point& c)
    : Triangle(a, b, c)
{}

std::vector<std::unique_ptr<Triangle>> ScaleneHeptagonalTriangle::split(const float scale) const
{
    const auto d = m_b*(1/(alpha*beta))+m_a*(1/alpha);
    std::vector<std::unique_ptr<Triangle>> result;
    result.push_back(std::make_unique<WideHeptagonalTriangle>(d*scale, m_a*scale, m_c*scale));
    result.push_back(std::make_unique<MiddleHeptagonalTriangle>(m_c*scale, d*scale, m_b*scale));
    return result;
}

std::string ScaleneHeptagonalTriangle::label() const
{
    return "scaleneHeptagonal";
}

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
        file << triangle;
    }
}

int main()
{
    std::vector<std::unique_ptr<Triangle>> triangles;
    //triangles.push_back(std::make_unique<TallPentagonalTriangle>(Point(0,0), Point(phi, 0), Point(phi*cos(36*M_PI/180), phi*sin(36*M_PI/180))));
    //triangles.push_back(std::make_unique<TallPentagonalTriangle>(Point(0,0), Point(phi, 0), Point(phi*cos(-36*M_PI/180), phi*sin(-36*M_PI/180))));
    triangles.push_back(std::make_unique<TallHeptagonalTriangle>(Point(0,0), Point(alpha*beta,0), Point(alpha*beta*cos(M_PI/7), alpha*beta*sin(M_PI/7))));
    triangles.push_back(std::make_unique<TallHeptagonalTriangle>(Point(0,0), Point(alpha*beta,0), Point(alpha*beta*cos(-M_PI/7), alpha*beta*sin(-M_PI/7))));

    const size_t iterations = 61;
    const float scale = 1;
    const std::string filename = "./latex/heptagonal_data.tex";

    PenroseTriangles penrose_triangles(triangles);
    penrose_triangles.split(iterations, scale);
    penrose_triangles.print(filename);
    return 0;
}
