#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

struct Point 
{
    const float x;
    const float y;

    Point(const float _x, const float _y);
    Point operator*(const float scale) const;
    Point operator+(const Point& that) const;
};

class Triangle 
{
public:
    virtual std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const = 0;
    float area() const; // unsigned
    std::ostream& operator<<(std::ostream& os) const;
    virtual std::ostream& print_seahorse(std::ostream& os) const;
    virtual ~Triangle() = default;
protected: 
    Point m_a; // apex
    Point m_b;
    Point m_c;
    float m_area; // signed

    virtual std::string label() const = 0;
    Triangle(const Point& a, const Point& b, const Point& c);
};

// Should have internal angles 36, 36, 72 
class WidePentagonalTriangle : public Triangle
{
public:
    WidePentagonalTriangle(const Point& a, const Point& b, const Point& c);
    std::vector<std::unique_ptr<Triangle>> split(const float scale = 1) const override; 
    std::ostream& print_seahorse(std::ostream& os) const override;
private:
    std::string label() const override;
};

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
