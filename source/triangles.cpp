#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include "../include/triangles.h"

bool point_t::is_equal(const point_t& rhs) const {
    return std::abs(x_ - rhs.x_) < TOLERANCE && \
           std::abs(y_ - rhs.y_) < TOLERANCE && \
           std::abs(z_ - rhs.z_) < TOLERANCE ? true : false;
}

void point_t::print_point() {
    fprintf(stderr, "Point (%f, %f, %f)\n", x_, y_, z_);
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
    x_ = p2.x_ - p1.x_;
    y_ = p2.y_ - p1.y_;
    z_ = p2.z_ - p1.z_;
    len = sqrtf(pow(p2.x_ - p1.x_, 2) + pow(p2.y_ - p1.y_, 2) + pow(p2.z_ - p1.z_, 2)); // fix
}

void vector_t::print_vector() {
    fprintf(stderr, "Vector: (%f, %f, %f)\n", x_, y_, z_);
}

void test_vector() {
    fprintf(stderr, "\n\n\n");
    point_t p1{1, -1, 2};
    point_t p2{3, 0.5, -1};
    vector_t vec{p1, p2};
    vec.print_vector();
    fprintf(stderr, "\n\n\n");
}

line_t::line_t(const point_t& p1, const point_t& p2): vector(p1, p2) {}

line_t::line_t(const vector_t& a) {
    vector = a;
}

triangle_t::triangle_t(const point_t& p1, \
                       const point_t& p2, \
                       const point_t& p3): vec_1(p1, p2), vec_2(p2, p3), vec_3(p1, p3) {}
bool triangle_t::is_valid() {
    if (vec_1.x_ + vec_2.x_ - vec_3.x_ < TOLERANCE && \
        vec_1.y_ + vec_2.y_ - vec_3.y_ < TOLERANCE && \
        vec_1.y_ + vec_2.y_ - vec_3.y_ < TOLERANCE) {
            return true;
        }
    return false;
}

void triangle_t::print_triangle() {
    fprintf(stderr, "\n\n\n");
    fprintf(stderr, "Printing triangle vectors:\n");
    vec_1.print_vector();
    vec_2.print_vector();
    vec_3.print_vector();
    fprintf(stderr, "\n\n\n");
}

void test_triangle() {
    triangle_t triangle{point_t(-2, 1, 4), point_t(0, 0, 5), point_t(1, 1, 1)};
    triangle.print_triangle();
    assert(triangle.is_valid());
}

void test() {
    std::vector<triangle_t> triangles;
    int N = 0;
    float x1, y1, z1 = NAN;
    float x2, y2, z2 = NAN;
    float x3, y3, z3 = NAN;
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        std::cin >> x1 >> y1 >> z1;
        point_t vertice_1(x1, y1, z1);
        std::cin >> x2 >> y2 >> z2;
        point_t vertice_2(x2, y2, z2);
        std::cin >> x3 >> y3 >> z3;
        point_t vertice_3(x3, y3, z3);

        triangle_t triangle(vertice_1, vertice_2, vertice_3);
        triangle.print_triangle();
        triangles.push_back(triangle);
    }
}






