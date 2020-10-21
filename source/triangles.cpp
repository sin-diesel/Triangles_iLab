#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <fstream>
#include "../include/triangles.h"


//-------- for debugging

#define DEBUG false
#define ASSERT(test) std::cerr << #test << "FAILED" << std::endl; \
                    std::cerr << "ERROR AT LINE: " << __LINE__ << " FUNCTION: " << __func__ << std::endl; \

#define DUB(expr) if (DEBUG) {expr;};


//-------- point through coordinates constructor
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

//-------- vector through two points constructor
vector_t::vector_t(const point_t p1, 
                   const point_t p2) {
                       x_ = p2.x_ - p1.x_;
                       y_ = p2.y_ - p1.y_;
                       z_ = p2.z_ - p1.z_;
                       DUB(print())
                   };

//-------- vector through coordinates constructor
vector_t::vector_t(float x, float y, float z) {
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

void vector_t::print() const {
    fprintf(stderr, "--------------\n");
    fprintf(stderr, "Vector %p: (%f, %f, %f)\n", this, x_, y_, z_);
    fprintf(stderr, "--------------\n");
}

//-------- triangle constructor through point

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

bool triangle_t::is_valid() const {
    vector_t nul(0, 0, 0);
    if ((a3_ - a1_ - a2_).is_equal(nul) == true) {
        return true;
    } 
    return false;
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

void test() {
    std::fstream log;
    log.open("log.txt", std::ios::out);
    log << "TESTING----------------------------------------\\" << std::endl;

    log << "TEST 1: " << std::endl;
    point_t point_1(0.23, 1.25, -7.32);
    point_t point_2(0.23, 1.25, -7.320000000001);
    if (point_1.is_equal(point_2) == false) {
        ASSERT("TEST 1");
    }
    log << "TEST 1 PASSED" << std::endl;

    log << "TEST 2: " << std::endl;
    point_t point_3(1, -1, 0);
    point_t point_4(1, 5.5, -3.5);
    vector_t vec_1(0.24, -5.21, 1.12);
    vector_t vec_2(point_3, point_4);
    vector_t vec_3 = vec_1 + vec_2;
    vector_t vec_4 = vector_t(0.24, 1.29, -2.38);
    if (vec_3.is_equal(vec_4) == false) {
        ASSERT("TEST 2");
    }
    log << "TEST 2 PASSED" << std::endl;

    log << "TEST 3: " << std::endl;
    point_t p1(1, -1, 0);
    point_t p2(3, 5, -8);
    point_t p3(0, 0, -3);
    triangle_t triangle_1(p1, p2, p3);
    if (triangle_1.is_valid() == false) {
        ASSERT("TEST 3");
    }
    log << "TEST 3 PASSED" << std::endl;

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
        triangle.print();
        triangles.push_back(triangle);
    }
}





