#include <iostream>
#include <vector>
#include "triangles.h"

/* TODO 
1) overload << operator for points
2) overload << operator for triangles 
3) maybe fix dumps and << operator 
4) split into modules: geometry, algorithm 
5) add module function to calculate length 
6) fix name resolution conflicts, fix VectorConversion test
7) maybe add unary - operator for vectors
8) add a little exception handling
9) add 0 to vector conversion DONE
10) add computing distances from plane to point DONE 
11) add parallel planes method
12) add 2d triangles intersection test
13) refactor plane::is_equal function DONE
14) Line-plane intersection, check if parallel
15) t parameter computation, check if point is on a line
16) fix line constructor via two planes
17) Handle cases where to points are coincident in triangle intersecton interval computation
18) remove code duplication in intervals test  */

/* ASK
1) const qualifier in plane.get_normal(), how to fix properly (or const Plane&)
2) name resoulution conflicts
3) throw an exception in constructors when, for instance when point can't be computed in 
constructor because a plane and a line a parallel */
int main(int argc, char** argv) {

    int N = 0;
    float x = NAN;
    float y = NAN;
    float z = NAN;

    std::cin >> N;

    D(std::cout << "Number of triangles: " << N << std::endl);

    std::vector<Triangle> triangles;
    std::vector<Point> points;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cin >> x;
            std::cin >> y;
            std::cin >> z;
            points.push_back(Point(x, y, z));
        }
        triangles.push_back(Triangle(points[0], points[1], points[2]));
        points.clear();
        D(std::cout << "Triangle [" << i << "] = \n\n\n");
        D(triangles[i].dump());
    }

    return 0;
}