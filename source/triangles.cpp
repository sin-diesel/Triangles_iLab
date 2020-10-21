#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <fstream>
#include "../include/triangles.h"


//---------------------- for debugging

#define DEBUG false
#define ASSERT(test) std::cerr << #test << "FAILED" << std::endl; \
                    std::cerr << "ERROR AT LINE: " << __LINE__ << " FUNCTION: " << __func__ << std::endl; \

#define DUB(expr) if (DEBUG) {expr;};


//---------------------- Point
point_t::point_t(float x, float y, float z) {
    x_ = x;
    y_ = y;
    z_ = z;
    DUB(print())
}

void point_t::print() const {
    fprintf(stderr, "--------------\n");
    fprintf(stderr, "Point %p: (%f, %f, %f)\n", this, x_, y_, z_);
    fprintf(stderr, "--------------\n");
}

bool point_t::is_equal(const point_t& rhs) const {
    return std::abs(x_ - rhs.x_) < TOLERANCE && \
           std::abs(y_ - rhs.y_) < TOLERANCE && \
           std::abs(z_ - rhs.z_) < TOLERANCE ? true : false;
}

//---------------------- Vector 
vector_t::vector_t(const point_t p1,  // vector through 2 point constructor
                   const point_t p2) {
                       x_ = p2.x_ - p1.x_;
                       y_ = p2.y_ - p1.y_;
                       z_ = p2.z_ - p1.z_;
                       DUB(print())
                   };

vector_t::vector_t(float x, float y, float z) { // vector through coordinates constructor
    x_ = x;
    y_ = y;
    z_ = z;
    DUB(print())
}

vector_t operator+(const vector_t& lhs, const vector_t& rhs) {
    float x = lhs.x_ + rhs.x_;
    float y = lhs.y_ + rhs.y_;
    float z = lhs.z_ + rhs.z_;
    return vector_t(x, y, z);
}

vector_t operator-(const vector_t& lhs, const vector_t& rhs) {
    float x = lhs.x_ - rhs.x_;
    float y = lhs.y_ - rhs.y_;
    float z = lhs.z_ - rhs.z_;
    return vector_t(x, y, z);
}

// vector_t operator*(const vector_t& lhs, const vector_t& rhs) {

// }

bool vector_t::is_equal(const vector_t& rhs) const {
    return std::abs(x_ - rhs.x_) < TOLERANCE && \
           std::abs(y_ - rhs.y_) < TOLERANCE && \
           std::abs(z_ - rhs.z_) < TOLERANCE ? true : false;
}

float vector_t::len() const {
    return sqrtf(x_ * x_ + y_ * y_ + z_ * z_);
}


void vector_t::print() const {
    fprintf(stderr, "--------------\n");
    fprintf(stderr, "Vector %p: (%f, %f, %f)\n", this, x_, y_, z_);
    fprintf(stderr, "--------------\n");
}

// triangle constructor through 3 points

triangle_t::triangle_t(const point_t& p1, const point_t& p2, const point_t& p3): v1_(p1), \
                                                                                 v2_(p2), \
                                                                                 v3_(p3) { \
    a1_ = vector_t(p1, p2);
    a2_ = vector_t(p2, p3);
    a3_ = a1_ + a2_;
    DUB(print())

}

bool triangle_t::is_equal(const triangle_t& rhs) const {
    if (a1_.is_equal(rhs.a1_) && a2_.is_equal(rhs.a2_) && a3_.is_equal(rhs.a3_)) {
        return true;
    }
    return false;
}

// handling degenarate triangles
bool triangle_t::is_valid() const {
    vector_t nul(0, 0, 0);
    if ((a3_ - a1_ - a2_).is_equal(nul) != true) {
        return false;
    }

    vector_t v1 = cross_product(a1_, a2_);
    vector_t v2 = cross_product(a2_, a3_);
    vector_t v3 = cross_product(a1_, a3_);

    if(v1.is_equal(nul) || v2.is_equal(nul) || v3.is_equal(nul)) {
        return false;
    }

    return true;
}

void triangle_t::print() const {
    fprintf(stderr, "--------------\n");
    fprintf(stderr, "Triangle %p:\n\n\n", this);
    a1_.print();
    a2_.print();
    a3_.print();
    fprintf(stderr, "\n\n\n");
    fprintf(stderr, "--------------\n");
}
//---------------------- Plane
plane_t::plane_t(const vector_t& vec1, const vector_t& vec2, const point_t& point) {
    norm = cross_product(vec1, vec2);
    a = norm.x_;
    b = norm.y_;
    c = norm.z_;
    d = -1 * (a * point.x_ + b * point.y_ + c * point.z_);
    DUB(print())
}

void plane_t::print() const {
    fprintf(stderr, "--------------\n");
    fprintf(stderr, "Plane %p: %fx + %fy + %fz + %f = 0\n\n\n", this, a, b, c, d);
    //norm.print();
    fprintf(stderr, "\n\n\n");
    fprintf(stderr, "--------------\n");
}


bool plane_t::is_equal(const plane_t& rhs) const {
    if (abs(a - rhs.a) < TOLERANCE && abs(b - rhs.b) < TOLERANCE && abs(c - rhs.c) < TOLERANCE && \
                abs(d - rhs.d) < TOLERANCE) {
        return true;      
    }
    return false;
}

void test() {
    std::fstream log;
    log.open("log.txt", std::ios::out);
    log << "TESTING----------------------------------------\\" << std::endl;

    //log << "TEST 1: " << std::endl;
    point_t p1(0.23, 1.25, -7.32);
    point_t p2(0.23, 1.25, -7.320000000001);
    if (p1.is_equal(p2) == false) {
        ASSERT("TEST 1");
        log << "TEST 1 FAILED" << std::endl;
        exit(-1);
    }
    log << "TEST 1 PASSED" << std::endl;
//--------------------------------
    //log << "TEST 2: " << std::endl;
    p1 = point_t(1, -1, 0);
    p2 = point_t(1, 5.5, -3.5);
    vector_t nul(0, 0, 0);
    vector_t v1(0.24, -5.21, 1.12);
    vector_t v2(p1, p2);
    vector_t v3 = v1 + v2;
    vector_t v4 = vector_t(0.24, 1.29, -2.38);
    if (v3.is_equal(v4) == false) {
        ASSERT("TEST 2");
        log << "TEST 2 FAILED";
        exit(-1);
    }
    log << "TEST 2 PASSED" << std::endl;
//--------------------------------
    //log << "TEST 3: " << std::endl;
    p1 = point_t(1, -1, 0);
    p2 = point_t(3, 5, -8);
    point_t p3(0, 0, -3);
    triangle_t triangle_1(p1, p2, p3);
    if (triangle_1.is_valid() == false) {
        ASSERT("TEST 3");
        log << "TEST 3 FAILED";
        exit(-1);
    }
    log << "TEST 3 PASSED" << std::endl;
//--------------------------------
    //log << "TEST 4: " << std::endl;
    v1 = vector_t(1, 1, -3);
    v2 = vector_t(-1, 3, -1);
    v3 = vector_t(cross_product(v1, v2));
    DUB(v3.print();)
    v4 = vector_t(8, 4, 4);

    if (v3.is_equal(v4) == false) {
        ASSERT("TEST 4");
        log << "TEST 4 FAILED";
        exit(-1);
    }
    log << "TEST 4 PASSED" << std::endl;
//--------------------------------
    //log << "TEST 5: " << std::endl;
    v1 = vector_t(1, 1, -3);
    v2 = vector_t(8, 8, -24);
    v3 = cross_product(v1, v2);
    DUB(v3.print();)

    if (v3.is_equal(nul) == false) {
        ASSERT("TEST 5");
        log << "TEST 5 FAILED";
        exit(-1);
    }
    log << "TEST 5 PASSED" << std::endl;
//--------------------------------
    //log << "TEST 6: " << std::endl;
    p1 = point_t(2, 3, 4);
    v1 = vector_t(1, 2, 5);
    v2 = vector_t(0, -4, 2);

    p2 = point_t(0, 0, 0);
    v3 = vector_t(1, -2, -2);
    v4 = vector_t(-4, -5, 0);

    plane_t plane1(v1, v2, p1);
    plane_t plane2(v3, v4, p2);

    //plane1.print();
    //plane2.print();


    vector_t intersect = plane_intersection(plane1, plane2);
    //intersect.print();
    log << "TEST 6 PASSED" << std::endl;
//--------------------------------
    p1 = point_t(3, -3, 2);
    p2 = point_t(0, 0, 1);
    v1 = vector_t(1, 2, 5);
    v2 = vector_t(0, -4, 2);

    plane1 = plane_t(v1, v2, p2);
    //plane1.print();

    float dist = compute_distance(plane1, p1);
    fprintf(stderr, "Dist: %f\n", dist);
    if (abs(dist - 3.031158) > TOLERANCE * 1000) {
        ASSERT("TEST 7");
        log << "TEST 7 FAILED";
        exit(-1);
    }
    log << "TEST 7 PASSED" << std::endl;

    p1 = point_t(3, -3, 2);
    p2 = point_t(3, -3, 2.01);

    v1 = vector_t(1, 2, 5);
    v2 = vector_t(0, -4, 2);

    plane1 = plane_t(v1, v2, p1);
    plane2 = plane_t(v1, v2, p2);
    //plane1.print();
    //plane2.print();

//--------------------------------

    if (plane1.is_equal(plane2)) {
        ASSERT("TEST 8");
        log << "TEST 8 FAILED";
        exit(-1);
    }
     log << "TEST 8 PASSED" << std::endl;
//--------------------------------


    log << "ALL TESTS PASSED" << std::endl;
    log.close();
}

//-------- get data
void acquire_input() {
    std::vector<triangle_t> triangles;
    int n = 0;
    float x, y, z = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y >> z;
        point_t p1(x, y, z);
        std::cin >> x >> y >> z;
        point_t p2(x, y, z);
        std::cin >> x >> y >> z;
        point_t p3(x, y, z);
        triangle_t triangle(p1, p2, p3);
        //triangle.print();
        if (triangle.is_valid() == false) {
            ASSERT("TRIANGLE FAILURE");
        } else {
            triangles.push_back(triangle);
        }
    }
}


float scalar_multiplication(const vector_t& rhs, const vector_t& lhs) {
    return rhs.x_ * lhs.x_ + rhs.y_ * lhs.y_ + rhs.z_ * lhs.z_;
}

float compute_distance(const plane_t& plane, const point_t& point) {
    float norm_len = plane.norm.len();
    assert(norm_len != 0);
    vector_t v(point.x_, point.y_, point.z_);
    v.print();
    plane.norm.print();

    return (scalar_multiplication(plane.norm, v) + plane.d) / (1.0 * norm_len);
}

vector_t cross_product(const vector_t& lhs, const vector_t& rhs) {
    float x, y, z = NAN;

    x = lhs.y_ * rhs.z_ - lhs.z_ * rhs.y_;
    y = lhs.z_ * rhs.x_ - lhs.x_ * rhs.z_;
    z = lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_;

    return vector_t(x, y, z);
}

vector_t plane_intersection(const plane_t& lhs, const plane_t& rhs) {
    return cross_product(lhs.norm, rhs.norm);
}

bool triangle_intersection(const triangle_t& rhs, const triangle_t& lhs) {
    /* 1) triangles are not degenerate, already checked  DONE
        2) compute plane equation of rhs: T1 DONE
        3) compute signed distances of vertices of lhs to T1 DONE
        4) compate signs of distances. If they are all the same, return false DONE
        5) compute plane equation of lhs: T2 DONE
        6) compare both planes. If they coincide, project triagles on a plane and perform 2d triangle intersection test
        7) if parallel, return false DONE
        8) compute intersection line of planes
        9) compute intervals
        10) if they do not overlap, return false */

        plane_t T1(rhs.a1_, rhs.a2_, rhs.v1_);
        vector_t nul(0, 0, 0);
        float d1 = compute_distance(T1, lhs.v1_);
        float d2 = compute_distance(T1, lhs.v2_);
        float d3 = compute_distance(T1, lhs.v3_);

        if ((d1 < 0 && d2 < 0 && d3 < 0) || (d1 > 0 && d2 > 0 && d3 > 0)) {
            return false;
        }

        plane_t T2(lhs.a1_, lhs.a2_, lhs.v1_);

        vector_t cross = cross_product(T1.norm, T2.norm);
        if (cross.is_equal(nul)) { // may be parallel or the same plane
            if (T1.is_equal(T2)) {
                        // TODO: 2d triangular intersection
            } else {
                return false;
            }
        }

}





