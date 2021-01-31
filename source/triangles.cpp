#include <cmath>
#include <iostream>
#include <vector>
#include "triangles.h"


//using namespace Geometry;

/*---------------------------------------------------------------*/
bool Point::is_equal(const Point& rhs) const {
    return std::abs(m_x - rhs.m_x) < TOLERANCE && \
           std::abs(m_y - rhs.m_y) < TOLERANCE && \
           std::abs(m_z - rhs.m_z) < TOLERANCE ? true : false;
}

/*---------------------------------------------------------------*/
void Point::dump() const {
    std::cout << "Dumping point " << this << std::endl;
    std::cout <<  "(" << m_x << ", " << m_y << ", " <<
                         m_z << ")" << std::endl;
}

/*---------------------------------------------------------------*/
// std::ostream& operator<<(std::ostream& stream, const Point& rhs) {
//     std::cout << "Point " << &rhs << std::endl;
//     std::vector<float> coordinates = rhs.get_coordinates();
//     stream << "(" << coordinates[0] << ", " << coordinates[1] << ", " <<
//                         coordinates[2] << ")" << std::endl;
//     return stream;
// }

/*---------------------------------------------------------------*/
// std::ostream& operator<<(std::ostream& stream, const Vector& rhs) {

//     std::cout << "Triangle: " << &rhs << std::endl;

//     std::vector<float> coordinates = rhs.get_coordinates();
//     stream << "(" << coordinates[0] << ", " << coordinates[1] << ", " <<
//                         coordinates[2] << ")" << std::endl;
//     return stream;
// }

/*---------------------------------------------------------------*/
// std::ostream& operator<<(std::ostream& stream, const Line& rhs) {
//     std::cout << 
//     return stream;
// }

/*---------------------------------------------------------------*/
bool operator==(const Point& p1, const Point& p2) {
    return p1.is_equal(p2);
}

/*---------------------------------------------------------------*/
bool operator==(const Plane& pl1, const Plane& pl2) {
    return pl1.is_equal(pl2);
}

/*---------------------------------------------------------------*/
bool operator==(const Vector& v1, const Vector& v2) {
    return v1.is_equal(v2);
}

/*---------------------------------------------------------------*/
bool operator==(const Triangle& t1, const Triangle& t2) {
    return t1.is_equal(t2);
}

Vector& Vector::operator*=(float num) {
    m_x *= num;
    m_y *= num;
    m_z *= num;
    return *this;
}

/*---------------------------------------------------------------*/
Vector operator*(const Vector& lhs, float num) {
    Vector result = lhs;
    result *= num;
    return result;
}

/*---------------------------------------------------------------*/
Vector operator*(float num, const Vector& rhs) {
    return rhs * num;
}


/*---------------------------------------------------------------*/
Vector operator+(const Vector& lhs, const Vector& rhs) {
    std::vector<float> l_coord = lhs.get_coordinates();
    std::vector<float> r_coord = rhs.get_coordinates();

    float x = l_coord[0] + r_coord[0];
    float y = l_coord[1] + r_coord[1];
    float z = l_coord[2] + r_coord[2];
    return Vector(x, y, z);
}

/*---------------------------------------------------------------*/
Vector operator-(const Vector& lhs, const Vector& rhs) {
    std::vector<float> l_coord = lhs.get_coordinates();
    std::vector<float> r_coord = rhs.get_coordinates();

    float x = l_coord[0] - r_coord[0];
    float y = l_coord[1] - r_coord[1];
    float z = l_coord[2] - r_coord[2];
    return Vector(x, y, z);
}

/*---------------------------------------------------------------*/
bool Vector::is_equal(const Vector& rhs) const {
    return std::abs(m_x - rhs.m_x) < TOLERANCE && \
           std::abs(m_y - rhs.m_y) < TOLERANCE && \
           std::abs(m_z - rhs.m_z) < TOLERANCE ? true : false;
}

void Vector::dump() const {
    std::cout << "Dumping vector " << this << std::endl;
    std::cout <<  "(" << m_x << ", " << m_y << ", " <<
                         m_z << ")" << std::endl;
}

std::vector<float> Vector::get_coordinates() const {
    std::vector<float> coordinates = {m_x, m_y, m_z};
    return coordinates;
}

std::vector<float> Point::get_coordinates() const {
    std::vector<float> coordinates = {m_x, m_y, m_z};
    return coordinates;
}

Vector::Vector(const Point& p1, const Point& p2) {
    std::vector<float> begin = p1.get_coordinates();
    std::vector<float> end = p2.get_coordinates();
    
    m_x = end[0] - begin[0];
    m_y = end[1] - begin[1];
    m_z = end[2] - begin[2];

}

/*---------------------------------------------------------------*/
Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3): m_p1(p1), \
                                                                       m_p2(p2), \
                                                                       m_p3(p3) {}; \


/*---------------------------------------------------------------*/
bool Line::is_equal(const Line& rhs) const {
    if (m_a.is_equal(rhs.m_a) && m_p.is_equal(rhs.m_p)) {
        return true;
    }
    return false;
}

/*---------------------------------------------------------------*/
void Line::dump() const {
    std::cout << "Dumping line: " << this << std::endl;
    m_p.dump();
    m_a.dump();
}

/*---------------------------------------------------------------*/
bool operator==(const Line& l1, const Line& l2) {
    return l1.is_equal(l2);
}

/*---------------------------------------------------------------*/
Line::Line(const Point& p1, const Point& p2) {
    m_p = p1;
    m_a = Vector(p1, p2);
}

/* Intersection via two planes */
/*---------------------------------------------------------------*/
Line::Line(const Plane& pl1, const Plane& pl2) {
    m_a = cross_product(pl1.get_normal(), pl2.get_normal());
}

/*---------------------------------------------------------------*/
Triangle::Triangle(const Point& p, const Vector& v1, const Vector& v2): m_p1(p) {
    std::vector<float> from = p.get_coordinates();
    std::vector<float> end_1 = v1.get_coordinates();
    std::vector<float> end_2 = v2.get_coordinates();

    /* calculate other points coordinates */
    float x2 = from[0] + end_1[0];
    float y2 = from[1] + end_1[1];
    float z2 = from[2] + end_1[2];
    float x3 = from[0] + end_2[0];
    float y3 = from[1] + end_2[1];
    float z3 = from[2] + end_2[2];

    m_p2 = Point(x2, y2, z2);
    m_p3 = Point(x3, y3, z3);

}

/*---------------------------------------------------------------*/
// std::vector<const Point&> Triangle::get_points() {

// }

/*---------------------------------------------------------------*/
bool Triangle::is_equal(const Triangle& rhs) const {
    if (m_p1.is_equal(rhs.m_p1) && m_p2.is_equal(rhs.m_p2) && m_p3.is_equal(rhs.m_p3)) {
        return true;
    }
    return false;
}

/*---------------------------------------------------------------*/
void Triangle::dump() const {
    std::cout << "Dumping triangle: " << this << std::endl;
    m_p1.dump();
    m_p2.dump();
    m_p3.dump();
}

/*---------------------------------------------------------------*/
Plane::Plane(const Point& p1, const Point& p2, const Point& p3): m_p(p1) {
    m_v1 = Vector(p1, p2);
    m_v2 = Vector(p1, p3);
}

/*---------------------------------------------------------------*/
void Plane::dump() const {
    std::cout << "Dumping plane " << this << std::endl;
    m_p.dump();
    m_v1.dump();
    m_v2.dump();
}

/*---------------------------------------------------------------*/
bool Plane::is_equal(const Plane& rhs) const {
    if (m_v1.is_equal(rhs.m_v1) && m_v2.is_equal(rhs.m_v2)) {
        return true;
    }
    return false;
}



// float Vector::len() const {
//     return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
// }


// void Vector::print() const {
//     fprintf(stderr, "--------------\n");
//     fprintf(stderr, "Vector %p: (%f, %f, %f)\n", this, m_x, m_y, m_z);
//     fprintf(stderr, "--------------\n");
// }

// triangle constructor through 3 points

/*---------------------------------------------------------------*/
// Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3): m_p1(p1), \
//                                                                        m_p2(p2), \
//                                                                        m_p3(p3) {};

// handling degenarate triangles
// bool triangle_t::is_valid() const {
//     Vector nul(0, 0, 0);
//     if ((a3_ - a1_ - a2_).is_equal(nul) != true) {
//         return false;
//     }

//     Vector v1 = cross_product(a1_, a2_);
//     Vector v2 = cross_product(a2_, a3_);
//     Vector v3 = cross_product(a1_, a3_);

//     if(v1.is_equal(nul) || v2.is_equal(nul) || v3.is_equal(nul)) {
//         return false;
//     }

//     return true;
// }

// void triangle_t::print() const {
//     fprintf(stderr, "--------------\n");
//     fprintf(stderr, "Triangle %p:\n\n\n", this);
//     a1_.print();
//     a2_.print();
//     a3_.print();
//     fprintf(stderr, "\n\n\n");
//     fprintf(stderr, "--------------\n");
// }
//---------------------- Plane
// plane_t::plane_t(const Vector& vec1, const Vector& vec2, const point_t& point) {
//     norm = cross_product(vec1, vec2);
//     a = norm.m_x;
//     b = norm.m_y;
//     c = norm.m_z;
//     d = -1 * (a * point.m_x + b * point.m_y + c * point.m_z);
//     DUB(print())
// }

// void plane_t::print() const {
//     fprintf(stderr, "--------------\n");
//     fprintf(stderr, "Plane %p: %fx + %fy + %fz + %f = 0\n\n\n", this, a, b, c, d);
//     //norm.print();
//     fprintf(stderr, "\n\n\n");
//     fprintf(stderr, "--------------\n");
// }


// bool plane_t::is_equal(const plane_t& rhs) const {
//     if (abs(a - rhs.a) < TOLERANCE && abs(b - rhs.b) < TOLERANCE && abs(c - rhs.c) < TOLERANCE && \
//                 abs(d - rhs.d) < TOLERANCE) {
//         return true;      
//     }
//     return false;
// }

// void test() {
//     std::fstream log;
//     log.open("log.txt", std::ios::out);
//     log << "TESTING----------------------------------------\\" << std::endl;

//     //log << "TEST 1: " << std::endl;
//     point_t p1(0.23, 1.25, -7.32);
//     point_t p2(0.23, 1.25, -7.320000000001);
//     if (p1.is_equal(p2) == false) {
//         ASSERT("TEST 1");
//         log << "TEST 1 FAILED" << std::endl;
//         exit(-1);
//     }
//     log << "TEST 1 PASSED" << std::endl;
// //--------------------------------
//     //log << "TEST 2: " << std::endl;
//     p1 = point_t(1, -1, 0);
//     p2 = point_t(1, 5.5, -3.5);
//     Vector nul(0, 0, 0);
//     Vector v1(0.24, -5.21, 1.12);
//     Vector v2(p1, p2);
//     Vector v3 = v1 + v2;
//     Vector v4 = Vector(0.24, 1.29, -2.38);
//     if (v3.is_equal(v4) == false) {
//         ASSERT("TEST 2");
//         log << "TEST 2 FAILED";
//         exit(-1);
//     }
//     log << "TEST 2 PASSED" << std::endl;
// //--------------------------------
//     //log << "TEST 3: " << std::endl;
//     p1 = point_t(1, -1, 0);
//     p2 = point_t(3, 5, -8);
//     point_t p3(0, 0, -3);
//     triangle_t triangle_1(p1, p2, p3);
//     if (triangle_1.is_valid() == false) {
//         ASSERT("TEST 3");
//         log << "TEST 3 FAILED";
//         exit(-1);
//     }
//     log << "TEST 3 PASSED" << std::endl;
// //--------------------------------
//     //log << "TEST 4: " << std::endl;
//     v1 = Vector(1, 1, -3);
//     v2 = Vector(-1, 3, -1);
//     v3 = Vector(cross_product(v1, v2));
//     DUB(v3.print();)
//     v4 = Vector(8, 4, 4);

//     if (v3.is_equal(v4) == false) {
//         ASSERT("TEST 4");
//         log << "TEST 4 FAILED";
//         exit(-1);
//     }
//     log << "TEST 4 PASSED" << std::endl;
// //--------------------------------
//     //log << "TEST 5: " << std::endl;
//     v1 = Vector(1, 1, -3);
//     v2 = Vector(8, 8, -24);
//     v3 = cross_product(v1, v2);
//     DUB(v3.print();)

//     if (v3.is_equal(nul) == false) {
//         ASSERT("TEST 5");
//         log << "TEST 5 FAILED";
//         exit(-1);
//     }
//     log << "TEST 5 PASSED" << std::endl;
// //--------------------------------
//     //log << "TEST 6: " << std::endl;
//     p1 = point_t(2, 3, 4);
//     v1 = Vector(1, 2, 5);
//     v2 = Vector(0, -4, 2);

//     p2 = point_t(0, 0, 0);
//     v3 = Vector(1, -2, -2);
//     v4 = Vector(-4, -5, 0);

//     plane_t plane1(v1, v2, p1);
//     plane_t plane2(v3, v4, p2);

//     //plane1.print();
//     //plane2.print();


//     Vector intersect = plane_intersection(plane1, plane2);
//     //intersect.print();
//     log << "TEST 6 PASSED" << std::endl;
// //--------------------------------
//     p1 = point_t(3, -3, 2);
//     p2 = point_t(0, 0, 1);
//     v1 = Vector(1, 2, 5);
//     v2 = Vector(0, -4, 2);

//     plane1 = plane_t(v1, v2, p2);
//     //plane1.print();

//     float dist = compute_distance(plane1, p1);
//     fprintf(stderr, "Dist: %f\n", dist);
//     if (abs(dist - 3.031158) > TOLERANCE * 1000) {
//         ASSERT("TEST 7");
//         log << "TEST 7 FAILED";
//         exit(-1);
//     }
//     log << "TEST 7 PASSED" << std::endl;

//     p1 = point_t(3, -3, 2);
//     p2 = point_t(3, -3, 2.01);

//     v1 = Vector(1, 2, 5);
//     v2 = Vector(0, -4, 2);

//     plane1 = plane_t(v1, v2, p1);
//     plane2 = plane_t(v1, v2, p2);
//     //plane1.print();
//     //plane2.print();

// //--------------------------------

//     if (plane1.is_equal(plane2)) {
//         ASSERT("TEST 8");
//         log << "TEST 8 FAILED";
//         exit(-1);
//     }
//      log << "TEST 8 PASSED" << std::endl;
// //--------------------------------


//     log << "ALL TESTS PASSED" << std::endl;
//     log.close();
// }

// //-------- get data
// void acquire_input() {
//     std::vector<triangle_t> triangles;
//     int n = 0;
//     float x, y, z = 0;
//     std::cin >> n;
//     for (int i = 0; i < n; ++i) {
//         std::cin >> x >> y >> z;
//         point_t p1(x, y, z);
//         std::cin >> x >> y >> z;
//         point_t p2(x, y, z);
//         std::cin >> x >> y >> z;
//         point_t p3(x, y, z);
//         triangle_t triangle(p1, p2, p3);
//         //triangle.print();
//         if (triangle.is_valid() == false) {
//             ASSERT("TRIANGLE FAILURE");
//         } else {
//             triangles.push_back(triangle);
//         }
//     }
// }


// float scalar_multiplication(const Vector& rhs, const Vector& lhs) {
//     return rhs.m_x * lhs.m_x + rhs.m_y * lhs.m_y + rhs.m_z * lhs.m_z;
// }

// float compute_distance(const plane_t& plane, const point_t& point) {
//     float norm_len = plane.norm.len();
//     assert(norm_len != 0);
//     Vector v(point.m_x, point.m_y, point.m_z);
//     v.print();
//     plane.norm.print();

//     return (scalar_multiplication(plane.norm, v) + plane.d) / (1.0 * norm_len);
// }

// Vector cross_product(const Vector& lhs, const Vector& rhs) {
//     float x, y, z = NAN;

//     x = lhs.m_y * rhs.m_z - lhs.m_z * rhs.m_y;
//     y = lhs.m_z * rhs.m_x - lhs.m_x * rhs.m_z;
//     z = lhs.m_x * rhs.m_y - lhs.y_ * rhs.m_x;

//     return Vector(x, y, z);
// }

// Vector plane_intersection(const plane_t& lhs, const plane_t& rhs) {
//     return cross_product(lhs.norm, rhs.norm);
// }       

// bool triangle_intersection(const triangle_t& rhs, const triangle_t& lhs) {
//     /* 1) triangles are not degenerate, already checked  DONE
//         2) compute plane equation of rhs: T1 DONE
//         3) compute signed distances of vertices of lhs to T1 DONE
//         4) compate signs of distances. If they are all the same, return false DONE
//         5) compute plane equation of lhs: T2 DONE
//         6) compare both planes. If they coincide, project triagles on a plane and perform 2d triangle intersection test
//         7) if parallel, return false DONE
//         8) compute intersection line of planes
//         9) compute intervals
//         10) if they do not overlap, return false */

//         plane_t T1(rhs.a1_, rhs.a2_, rhs.v1_);
//         Vector nul(0, 0, 0);
//         float d1 = compute_distance(T1, lhs.v1_);
//         float d2 = compute_distance(T1, lhs.v2_);
//         float d3 = compute_distance(T1, lhs.v3_);

//         if ((d1 < 0 && d2 < 0 && d3 < 0) || (d1 > 0 && d2 > 0 && d3 > 0)) {
//             return false;
//         }

//         plane_t T2(lhs.a1_, lhs.a2_, lhs.v1_);

//         vector_t cross = cross_product(T1.norm, T2.norm);
//         if (cross.is_equal(nul)) { // may be parallel or the same plane
//             if (T1.is_equal(T2)) {
//                         // TODO: 2d triangular intersection
//             } else {
//                 return false;
//             }
//         }

// }





