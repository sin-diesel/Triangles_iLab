#include <cmath>
#include <fstream>


#define DEBUG true
// #define ASSERT(test) std::cerr << #test << "FAILED" << std::endl; \
//                     std::cerr << "ERROR AT LINE: " << __LINE__ << " FUNCTION: " << __func__ << std::endl; \

/* Debugging macro */
#define D(expr) if (DEBUG) {expr;};

/* Comparison tolerance */
#define TOLERANCE 1e-5

//namespace Geometry {
    /*---------------------------------------------------------------*/
    class Point {
        float m_x = NAN, m_y = NAN, m_z = NAN;
    public:
        Point(float x, float y, float z): m_x(x), m_y(y), m_z(z) {};
        Point() = default;

        std::ostream& operator<<(const Point& rhs);

        bool is_equal(const Point& rhs) const;
        std::vector<float> get_coordinates() const;
    };

    /*---------------------------------------------------------------*/
    class Vector {
        float m_x = NAN, m_y = NAN, m_z = NAN;
    public:
        Vector(float x, float y, float z): m_x(x), m_y(y), m_z(z) {};
        Vector(const Point& p1, const Point& p2);
        Vector(const Vector& rhs) = default;

        Vector& operator*=(float num);

        bool is_equal(const Vector& rhs) const;
        std::vector<float> get_coordinates() const;
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
        std::vector<const Point&> get_points();
        void dump() const;
    };

    bool operator==(const Point& p1, const Point& p2);

    /*---------------------------------------------------------------*/
    bool operator==(const Vector& v1, const Vector& v2);

    /*---------------------------------------------------------------*/
    bool operator==(const Triangle& t1, const Triangle& t2);

    /*---------------------------------------------------------------*/
    std::ostream& operator<<(std::ostream& stream, const Point& rhs);

    /*---------------------------------------------------------------*/
    Vector operator*(const Vector& lhs, float num);

    /*---------------------------------------------------------------*/
    Vector operator*(float num, const Vector& rhs);

    //---------------------- Plane
    // struct plane_t:public Printable {

    //     vector_t norm;
    //     float a, b, c, d = NAN;

    //     plane_t(const vector_t& vec1, const vector_t& vec2, const point_t& point);
    //     void print() const override;
    //     bool is_equal(const plane_t& rhs) const;
    // };


    // bool triangle_intersection(const triangle_t& rhs, const triangle_t& lhs);

    // float compute_distance(const plane_t& plane, const point_t& point);

    // void test();

    // void acquire_input();

    // float scalar_multiplication(const vector_t& rhs, const vector_t& lhs);

    // vector_t cross_product(const vector_t& lhs, const vector_t& rhs);

    // vector_t plane_intersection(const plane_t& lhs, const plane_t& rhs);
//}

