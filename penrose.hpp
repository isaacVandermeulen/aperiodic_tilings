#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "geometry/triangle.hpp"

class PenroseTriangles
{
public:
    PenroseTriangles(std::vector<std::unique_ptr<Triangle>>& initial_triangles);

    void split(const size_t iterations, const float scale = 1);
    void print(const std::string& filename);

private:
    std::vector<std::unique_ptr<Triangle>> m_triangles;
};
