#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <fstream>
#include "../include/triangles.h"


//-------- for debugging

#define DEBUG true
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
    fprintf(stderr, "Point %p: (%f, %f, %f)\n", this, x_, y_, z_);
}

bool point_t::is_equal(const point_t& rhs) const {
    return std::abs(x_ - rhs.x_) < TOLERANCE && \
           std::abs(y_ - rhs.y_) < TOLERANCE && \
           std::abs(z_ - rhs.z_) < TOLERANCE ? true : false;
}

//-------- vector through two points constructor
vector_t::vector_t(const point_t p1, 
                   const point_t p2): p1_(p1), p2_(p2) {
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
    float x = lhs.p1_.x_ + rhs.p2_.x_;
    float y = lhs.p1_.y_ + rhs.p2_.y_;
    float z = lhs.p1_.z_ + rhs.p2_.z_;
    return vector_t(x, y, z);
}

void vector_t::print() const {
    fprintf(stderr, "Vector %p: (%f, %f, %f)\n", this, x_, y_, z_);
    fprintf(stderr, "Beginning: (%f, %f, %f), end: (%f, %f, %f)\n", p1_.x_, \
                                                                    p1_.y_, \
                                                                    p1_.z_, \
                                                                    p2_.x_, \
                                                                    p2_.y_, \
                                                                    p2_.z_);
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
    vector_t vec_1(0.24, -5.21, 1.12);
    vector_t vec_2(point_1, point_2);
    vector_t vec_3 = vec_1 + vec_2;
    log << "TEST 2 PASSED" << std::endl;

    log << "ALL TESTS PASSED" << std::endl;
    log.close();
}




