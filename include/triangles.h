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
    //~point_t();

};

void test_points();

struct vector_t {
public:
    point_t p1_;
    point_t p2_;

    float len = NAN;

    vector_t() = default;
    vector_t(const point_t& p1, const point_t& p2);
};

void test_vector();

struct line_t {
public:
    vector_t vector;
    line_t(const vector_t& a);
    line_t(const point_t& p1, const point_t& p2);

    bool is_valid();
};

