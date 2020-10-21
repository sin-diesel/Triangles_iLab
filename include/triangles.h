#include <iostream>
#include <stdlib.h>
#include <math.h>

#define TOLERANCE 1e-7

struct Printable {
public:
    virtual void print() const = 0;
    virtual ~Printable() {};
};

struct point_t: public Printable {
public:
    float x_ = NAN, y_ = NAN, z_ = NAN;

    point_t() = default;
    point_t(float x, float y, float z);
    ~point_t() = default;

    bool is_equal(const point_t& rhs) const;
    void print() const override;
};

struct vector_t:public Printable {
public:

    float x_, y_, z_ = NAN;

    vector_t() = default;
    ~vector_t() = default;
    vector_t(point_t const p1, point_t const p2);
    vector_t(float x, float y, float z);

    bool is_equal(const vector_t& rhs) const;
    void print() const override;

};

struct triangle_t:public Printable {
public:

    point_t v1_;
    point_t v2_;
    point_t v3_;

    vector_t a1_;
    vector_t a2_;
    vector_t a3_;

    triangle_t() = default;
    triangle_t(const vector_t& a1, const vector_t& a2);
    triangle_t(const point_t& p1, const point_t& p2, const point_t& p3);

    bool is_equal(const triangle_t& rhs) const;
    bool is_valid() const;
    void print() const override;

};

void test();

void acquire_input();
