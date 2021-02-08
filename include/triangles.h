#pragma once

#include <cmath>
#include <fstream>


#define DEBUG true
// #define ASSERT(test) std::cerr << #test << "FAILED" << std::endl; \
//                     std::cerr << "ERROR AT LINE: " << __LINE__ << " FUNCTION: " << __func__ << std::endl; \

/* Debugging macro */
#define D(expr) if (DEBUG) {expr;};

/* Comparison tolerance */
#define TOLERANCE 1e-4

//namespace Geometry {

    class Point;
    class Triangle;
    class Plane;
    class Line;
    /*---------------------------------------------------------------*/
    class Vector {
        float m_x = NAN, m_y = NAN, m_z = NAN;
    public:
        Vector(float x, float y, float z);
        Vector(const Point& p1, const Point& p2);
        Vector(const Vector& rhs) = default;
        Vector(float num);
        Vector() = default;

        Vector& operator*=(float num);
        Vector& operator/=(float num);
        // explicit operator float() const {

        // }

        bool is_equal(const Vector& rhs) const;
        float len() const;
        std::vector<float> get_coordinates() const;
        void dump() const;
    };

    /*---------------------------------------------------------------*/
    class Point {
        float m_x = NAN, m_y = NAN, m_z = NAN;
    public:
        Point(float x, float y, float z);
        Point(const Plane& pl, const Line& l);
        Point() = default;
        Point(const Point& rhs) = default;

        std::ostream& operator<<(const Point& rhs);
        Point& operator+=(const Point& rhs);
        Point& operator-=(const Point& rhs);
        explicit operator Vector() const {
            return Vector(m_x, m_y, m_z);
        }

        bool is_equal(const Point& rhs) const;
        std::vector<float> get_coordinates() const;
        void dump() const;
    };

    /*---------------------------------------------------------------*/
    class Plane {
        Point m_p;
        Vector m_v1;
        Vector m_v2;
    public:
        Plane(const Point& p, const Vector& v1, const Vector& v2);
        Plane(const Point& p1, const Point& p2, const Point& p3);
        Plane(const Triangle& T);

        Point get_point() const;
        Vector get_normal() const;
        bool is_parallel(const Plane& rhs) const;
        bool is_equal(const Plane& rhs) const;
        void dump() const;

    };

    /*---------------------------------------------------------------*/
    class Line {
        Point m_p;
        Vector m_a;

    public:
        Line() = default;
        Line(const Point& p, const Vector& a);
        Line(const Point& p1, const Point& p2);
        Line(const Plane& pl1, const Plane& pl2); // const?

        bool is_equal(const Line& rhs) const;
        Vector get_direction() const {
            return m_a;
        }
        Point get_point() const {
            return m_p;
        }
        void dump() const;
    };

    /*---------------------------------------------------------------*/
    class Triangle {
        Point m_p1;
        Point m_p2;
        Point m_p3;

    public:
        Triangle(const Point& p1, const Point& p2, const Point& p3);
        Triangle(const Point& p, const Vector& v1, const Vector& v2);


        bool is_equal(const Triangle& rhs) const;
        bool degenerate() const;
        std::vector<Point> get_points() const;
        void dump() const;
    };

    bool operator==(const Point& p1, const Point& p2);

    /*---------------------------------------------------------------*/
    bool operator==(const Vector& v1, const Vector& v2);

    /*---------------------------------------------------------------*/
    bool operator==(const Plane& pl1, const Plane& pl2);

    /*---------------------------------------------------------------*/
    bool operator==(const Triangle& t1, const Triangle& t2);

    /*---------------------------------------------------------------*/
    bool operator==(const Line& l1, const Line& l2);

    /*---------------------------------------------------------------*/
    Point operator+(const Point& lhs, const Point& rhs);

    /*---------------------------------------------------------------*/
    Point operator-(const Point& lhs, const Point& rhs);

    /*---------------------------------------------------------------*/
    //std::ostream& operator<<(std::ostream& stream, const Point& rhs);

    /*---------------------------------------------------------------*/
    Vector operator*(const Vector& lhs, float num);

    /*---------------------------------------------------------------*/
    Vector operator*(float num, const Vector& rhs);

    /*---------------------------------------------------------------*/
    Vector operator/(const Vector& lhs, float num);

    /*---------------------------------------------------------------*/
    Vector operator/(float num, const Vector& rhs);

    /*---------------------------------------------------------------*/
    Vector cross_product(const Vector& v1, const Vector& v2);

    /*---------------------------------------------------------------*/
    float dot_product(const Vector& lhs, const Vector& rhs);

    /*---------------------------------------------------------------*/
    float compute_distance(const Point& p, const Plane& pl);

    /*---------------------------------------------------------------*/
    bool intersect(const Triangle& lhs, const Triangle& rhs);

    /*---------------------------------------------------------------*/
    bool intersect_2d(const Triangle& T0, const Triangle& T1);

    /*---------------------------------------------------------------*/
    std::pair<Line, Line> get_lines(const Triangle& t, const Plane& pl);

    