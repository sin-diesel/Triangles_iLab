#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "../include/triangles.h"

bool point_t::is_equal(const point_t& rhs) const {
    return std::abs(x_ - rhs.x_) < TOLERANCE && \
           std::abs(y_ - rhs.y_) < TOLERANCE && \
           std::abs(z_ - rhs.z_) < TOLERANCE ? true : false;
}

point_t::point_t(float x, float y, float z) {
    x_ = x;
    y_ = y;
    z_ = z;
}


void test_points() {
    point_t p1{1, -1, 2};
    point_t p2{3, 0.5, -1};
    point_t p3{1, -1, 2.000000000000001};

    assert(p1.is_equal(p3));
}

vector_t::vector_t(const point_t& p1, const point_t& p2) {
    p1_ = p1;
    p2_ = p2;
    len = sqrtf(pow(p2.x_ - p1.x_, 2) + pow(p2.y_ - p1.y_, 2) + pow(p2.z_ - p1.z_, 2)); // fix
}

void test_vector() {
    point_t p1{1, -1, 2};
    point_t p2{3, 0.5, -1};
    vector_t vec{p1, p2};

    std::cout << "Vector length: " << vec.len << std::endl;

}

line_t::line_t(const point_t& p1, const point_t& p2): vector(p1, p2) {}

line_t::line_t(const vector_t& a) {
    vector = a;
}

triangle_t::triangle_t(const point_t& p1, \
                       const point_t& p2, \
                       const point_t& p3): vec_1(p1, p2), vec_2(p2, p3), vec_3(p1, p3) {}






