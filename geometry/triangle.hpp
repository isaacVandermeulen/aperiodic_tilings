#include "point.hpp"
#include <iostream>
#include <vector>
#include <memory>

class Triangle 
{
public:
    virtual std::vector<std::unique_ptr<Triangle> > split(const float scale = 1) const = 0;
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

   friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
};

std::ostream& operator<<(std::ostream& os, const Triangle& t);
