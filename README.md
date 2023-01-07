# aperiodic_tilings

Computes some aperiodic tilings of the plane. They can be based on pentagonal or heptagonal symmetries. Tilings are computed by recursively subdividing triangles. For pentagonal tilings, two triangles are used:
 - WidePentagonalTriangle (internal angles pi/5, pi/5, 3pi/5)
 - TallPentagonalTriangle (internal angles 2pi/5, 2pi/5, pi/5)

For heptagonal tilings, four triangles are used
 - WideHeptagonalTriangle (internal angles pi/7, pi/7 5pi/7)
 - MiddleHeptagonalTriangle (internal angles 2pi/7, 2pi/7, 3pi/7)
 - TallHeptagonalTriangle (internal angles 3pi/7, 3pi/7, pi/7)
 - ScaleneHeptagonalTriangle (internal angles pi/7, 2pi/7, 4pi/)
