#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "geometry/triangle.hpp"

// Should have internal angles 72, 72, 36
class TallPentagonalTriangle : public Triangle
{
public:
    TallPentagonalTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override;
    std::ostream& print_seahorse(std::ostream& os) const override;
private:
    std::string label() const override;
};

// Should have internal angles pi/7, pi/7, 5*pi/7 
class WideHeptagonalTriangle : public Triangle
{
public:
    WideHeptagonalTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override;
private:
    std::string label() const override;
};

// Should have internal angles 2*pi/7, 2*pi/7, 3*pi/7 
class MiddleHeptagonalTriangle : public Triangle
{
public:
    MiddleHeptagonalTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override;
private:
    std::string label() const override;
};

// Should have internal angles 3*pi/7, 3*pi/7, 1*pi/7 
class TallHeptagonalTriangle : public Triangle
{
public:
    TallHeptagonalTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override;
private:
    std::string label() const override;
};

// Should have internal angles 1*pi/7, 2*pi/7, 4*pi/7 
class ScaleneHeptagonalTriangle : public Triangle
{
public:
    ScaleneHeptagonalTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override;
private:
    std::string label() const override;
};

class PenroseTriangles
{
public:
    PenroseTriangles(std::vector<std::unique_ptr<Triangle>>& initial_triangles);

    void split(const size_t iterations, const float scale = 1);
    void print(const std::string& filename);

private:
    std::vector<std::unique_ptr<Triangle>> m_triangles;
};
