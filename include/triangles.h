#include <iostream>
#include <stdlib.h>
#include <math.h>

#define TOLERANCE 1e-7

struct point_t {
public:
    float x_ = NAN, y_ = NAN, z_ = NAN;
    bool is_equal(const point_t& rhs) const;
    
    point_t(float x, float y, float z);
    point_t() = default;
    void print_point();
    //~point_t();

};

void test_points();

struct vector_t {
public:
    point_t p1_;
    point_t p2_;

    float x_ = NAN;
    float y_ = NAN;
    float z_ = NAN;

    float len = NAN;

    void print_vector();
    vector_t() = default;
    vector_t(const point_t& p1, const point_t& p2);
};

void test_vector();

struct line_t {
public:
    vector_t vector;
    line_t(const vector_t& a);
    line_t(const point_t& p1, const point_t& p2);

};

struct triangle_t {
public:
    point_t p1_;
    point_t p2_;
    point_t p3_;
    vector_t vec_1;
    vector_t vec_2;
    vector_t vec_3;

    triangle_t(const point_t& p1, const point_t& p2, const point_t& p3);
    bool is_valid();
    void print_triangle();
    float square();
};

void test_triangle();

void test();

