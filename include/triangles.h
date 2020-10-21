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
    point_t p1_;
    point_t p2_;

    float x_, y_, z_ = NAN;

    vector_t() = default;
    vector_t(point_t const p1, point_t const p2);
    vector_t(float x, float y, float z);
    ~vector_t() = default;

    void print() const override;

};

void test();
