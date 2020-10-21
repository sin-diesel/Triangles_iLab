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
    point_t p_1_;
    point_t p_2_;
    point_t p_3_;

    vector_t() = default;
    vector_t(point_t const p1, point_t const p2, point_t const p3);
    ~vector_t() = default;

    void print() const override;

};

void test();
