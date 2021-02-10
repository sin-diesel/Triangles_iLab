#include <cmath>
#include <iostream>
#include <vector>
#include "triangles.h"


//using namespace Geometry;

/*---------------------------------------------------------------*/
bool Point::is_equal(const Point& rhs) const {
    return std::abs(m_x - rhs.m_x) < TOLERANCE && \
           std::abs(m_y - rhs.m_y) < TOLERANCE && \
           std::abs(m_z - rhs.m_z) < TOLERANCE ? true : false;
}

/*---------------------------------------------------------------*/
Point::Point(float x, float y, float z): m_x(x), m_y(y), m_z(z) {};

/*---------------------------------------------------------------*/
Point::Point(const Plane& pl, const Line& l) {
    /* check if parallel */
    // D(pl.dump()); 
    // D(std::cout << std::endl);

    Vector normal = pl.get_normal();
    // D(std::cout << "Normal n: " << std::endl);
    // D(normal.dump());
    // D(std::cout << std::endl); 

    Vector direction = l.get_direction();
    // D(std::cout << "direction vector d: " << std::endl);
    // D(direction.dump());
    // D(std::cout << std::endl); 

    Point P = l.get_point();
    // D(std::cout << "Point on line P: " << std::endl);
    // D(P.dump());
    // D(std::cout << std::endl); 

    Point p_plane = pl.get_point();
    // D(std::cout << "Point on plane PL: " << std::endl);
    // D(p_plane.dump());
    // D(std::cout << std::endl); 

    float d = (-1) * dot_product(normal, static_cast<Vector>(p_plane));

    //D(std::cout << "d from plane equation: " << d << std::endl);

    float normal_module = normal.len();
    // normalize
    //normal = normal / normal_module;


    /* Calculate dot product of normal vector and direction, and also normal vector and point on plane */
    float dot = dot_product(normal, direction);

    /* fix later */
    assert(std::abs(dot) > TOLERANCE);

    float t = (-1) * (dot_product(normal, static_cast<Vector>(P)) + d) / dot;

    //D(std::cout << "Calculated t: " << t << std::endl);

    Vector multiplied = t * direction;
    std::vector<float> coordinates = multiplied.get_coordinates();
    m_x = P.m_x + coordinates[0];
    m_y = P.m_y + coordinates[1];
    m_z = P.m_z + coordinates[2];
}

/*---------------------------------------------------------------*/
void Point::dump() const {
    std::cout << "Dumping point " << this << std::endl;
    std::cout <<  "(" << m_x << ", " << m_y << ", " <<
                         m_z << ")" << std::endl;
}

/*---------------------------------------------------------------*/
Point& Point::operator+=(const Point& rhs) {
    m_x += rhs.m_x;
    m_y += rhs.m_y;
    m_z += rhs.m_z;
    return *this;
}

/*---------------------------------------------------------------*/
Point& Point::operator-=(const Point& rhs) {
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
    m_z -= rhs.m_z;
    return *this;
}

/*---------------------------------------------------------------*/
Point operator+(const Point& lhs, const Point& rhs) {
    Point tmp{lhs};
    tmp += rhs;
    return tmp;
}

/*---------------------------------------------------------------*/
Point operator-(const Point& lhs, const Point& rhs) {
    Point tmp{lhs};
    tmp -= rhs;
    return tmp;
}


/*---------------------------------------------------------------*/
bool operator==(const Point& p1, const Point& p2) {
    return p1.is_equal(p2);
}

/*---------------------------------------------------------------*/
bool operator==(const Plane& pl1, const Plane& pl2) {
    return pl1.is_equal(pl2);
}

/*---------------------------------------------------------------*/
bool operator==(const Vector& v1, const Vector& v2) {
    return v1.is_equal(v2);
}

/*---------------------------------------------------------------*/
bool operator==(const Triangle& t1, const Triangle& t2) {
    return t1.is_equal(t2);
}

Vector& Vector::operator*=(float num) {
    m_x *= num;
    m_y *= num;
    m_z *= num;
    return *this;
}

Vector& Vector::operator/=(float num) {
    /* add exception */
    if (std::abs(num) >= TOLERANCE) {
        m_x /= num;
        m_y /= num;
        m_z /= num;
        return *this;
    }
    return *this;
}

/*---------------------------------------------------------------*/
Vector::Vector(float x, float y, float z): m_x(x), m_y(y), m_z(z) {};

/*---------------------------------------------------------------*/
Vector operator*(const Vector& lhs, float num) {
    Vector result = lhs;
    result *= num;
    return result;
}

/*---------------------------------------------------------------*/
Vector operator*(float num, const Vector& rhs) {
    return rhs * num;
}

/*---------------------------------------------------------------*/
Vector operator/(const Vector& lhs, float num) {
    Vector result = lhs;
    result /= num;
    return result;
}

/*---------------------------------------------------------------*/
Vector operator/(float num, const Vector& rhs) {
    return rhs / num;
}


/*---------------------------------------------------------------*/
Vector operator+(const Vector& lhs, const Vector& rhs) {
    std::vector<float> l_coord = lhs.get_coordinates();
    std::vector<float> r_coord = rhs.get_coordinates();

    float x = l_coord[0] + r_coord[0];
    float y = l_coord[1] + r_coord[1];
    float z = l_coord[2] + r_coord[2];
    return Vector(x, y, z);
}


/*---------------------------------------------------------------*/
Vector operator-(const Vector& lhs, const Vector& rhs) {
    std::vector<float> l_coord = lhs.get_coordinates();
    std::vector<float> r_coord = rhs.get_coordinates();

    float x = l_coord[0] - r_coord[0];
    float y = l_coord[1] - r_coord[1];
    float z = l_coord[2] - r_coord[2];
    return Vector(x, y, z);
}

/*---------------------------------------------------------------*/
bool Vector::is_equal(const Vector& rhs) const {
    return std::abs(m_x - rhs.m_x) < TOLERANCE && \
           std::abs(m_y - rhs.m_y) < TOLERANCE && \
           std::abs(m_z - rhs.m_z) < TOLERANCE ? true : false;
}

void Vector::dump() const {
    std::cout << "Dumping vector " << this << std::endl;
    std::cout <<  "(" << m_x << ", " << m_y << ", " <<
                         m_z << ")" << std::endl;
}

std::vector<float> Vector::get_coordinates() const {
    std::vector<float> coordinates = {m_x, m_y, m_z};
    return coordinates;
}

std::vector<float> Point::get_coordinates() const {
    std::vector<float> coordinates = {m_x, m_y, m_z};
    return coordinates;
}

Vector::Vector(const Point& p1, const Point& p2) {
    std::vector<float> begin = p1.get_coordinates();
    std::vector<float> end = p2.get_coordinates();
    
    m_x = end[0] - begin[0];
    m_y = end[1] - begin[1];
    m_z = end[2] - begin[2];
}

/*---------------------------------------------------------------*/
float Vector::len() const {
    return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector::Vector(float num): m_x(num), m_y(num), m_z(num) {}

/*---------------------------------------------------------------*/
Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3): m_p1(p1), \
                                                                       m_p2(p2), \
                                                                       m_p3(p3) {}; \


/*---------------------------------------------------------------*/
bool Line::is_equal(const Line& rhs) const {
    if ((m_a.is_equal(rhs.m_a) || m_a.is_equal(rhs.m_a * (-1))) && m_p.is_equal(rhs.m_p)) {
        return true;
    }
    return false;
}

/*---------------------------------------------------------------*/
void Line::dump() const {
    std::cout << "Dumping line: " << this << std::endl;
    m_p.dump();
    m_a.dump();
}

/*---------------------------------------------------------------*/
bool operator==(const Line& l1, const Line& l2) {
    return l1.is_equal(l2);
}

/*---------------------------------------------------------------*/
Line::Line(const Point& p1, const Point& p2) {
    m_p = p1;
    m_a = Vector(p1, p2);
}

/*---------------------------------------------------------------*/
Point Plane::get_point() const {
    return m_p;
}

/*---------------------------------------------------------------*/
Plane::Plane(const Point& p, const Vector& v1, const Vector& v2): m_p(p), m_v1(v1), m_v2(v2) {}

Plane::Plane(const Triangle& T) {
    std::vector<Point> points = T.get_points();
    m_p = points[0];
    m_v1 = Vector(points[0], points[1]);
    m_v2 = Vector(points[0], points[2]);
}

/* Intersection via two planes */
/*---------------------------------------------------------------*/
Line::Line(const Plane& pl1, const Plane& pl2) {

    Vector n1 = pl1.get_normal();
    Vector n2 = pl2.get_normal();
    // D(n1.dump());
    // D(n2.dump());
    /* testing with the opposite direction */

    m_a = cross_product(n1, n2);
    D(m_a.dump());
    if (m_a == 0) {
        // throw exception?
        m_p = Point();
    } else {
         // normalizing 
        n1 = n1 / n1.len();
        n2 = n2 / n2.len();
        
        float n1_n2_dot = dot_product(n1, n2);
        float n1_normsqr = dot_product(n1, n1);
        float n2_normsqr = dot_product(n2, n2);


        Point p1 = pl1.get_point();
        Point p2 = pl2.get_point();

        /* no implicit cast for point-vector conversion */
        float s1 = dot_product(n1, static_cast<Vector>(p1));
        float s2 = dot_product(n2, static_cast<Vector>(p2));
        // D(std::cout << "s1 = " << s1 << std::endl);
        // D(std::cout << "s2 = " << s2 << std::endl);

        float a = (s2 * n1_n2_dot - s1 * n2_normsqr) / (n1_n2_dot * n1_n2_dot
                                                    - n1_normsqr * n2_normsqr);
        float b = (s1 * n1_n2_dot - s2 * n2_normsqr) / (n1_n2_dot * n1_n2_dot
                                                    - n1_normsqr * n2_normsqr);

        Vector temp(a * n1 + b * n2);
        /* constructing point as a vector */
        std::vector<float> coordinates = temp.get_coordinates();
        m_p = Point(coordinates[0], coordinates[1], coordinates[2]);
    }
}

Line::Line(const Point& p, const Vector& a): m_p(p), m_a(a) {}

/*---------------------------------------------------------------*/
Triangle::Triangle(const Point& p, const Vector& v1, const Vector& v2): m_p1(p) {
    std::vector<float> from = p.get_coordinates();
    std::vector<float> end_1 = v1.get_coordinates();
    std::vector<float> end_2 = v2.get_coordinates();

    /* calculate other points coordinates */
    float x2 = from[0] + end_1[0];
    float y2 = from[1] + end_1[1];
    float z2 = from[2] + end_1[2];
    float x3 = from[0] + end_2[0];
    float y3 = from[1] + end_2[1];
    float z3 = from[2] + end_2[2];

    m_p2 = Point(x2, y2, z2);
    m_p3 = Point(x3, y3, z3);

}

std::vector<Point> Triangle::get_points() const {
    std::vector<Point> points;
    points.push_back(m_p1);
    points.push_back(m_p2);
    points.push_back(m_p3);
    return points;
}



/*---------------------------------------------------------------*/
bool Triangle::is_equal(const Triangle& rhs) const {
    if (m_p1.is_equal(rhs.m_p1) && m_p2.is_equal(rhs.m_p2) && m_p3.is_equal(rhs.m_p3)) {
        return true;
    }
    return false;
}

/*---------------------------------------------------------------*/
void Triangle::dump() const {
    std::cout << "Dumping triangle: " << this << std::endl;
    m_p1.dump();
    m_p2.dump();
    m_p3.dump();
}

/*---------------------------------------------------------------*/
std::pair<Line, Line> get_lines(const Triangle& t, const Plane& pl) {
    std::vector<Point> points = t.get_points();

    Point A = points[0];
    Point B = points[1];
    Point C = points[2];
    // D(A.dump());
    // D(B.dump());
    // D(C.dump());

    // D(pl.dump());

    float da = compute_distance(A, pl);
    float db = compute_distance(B, pl);
    float dc = compute_distance(C, pl);

    // D(std::cout << "da = " << da << std::endl);
    // D(std::cout << "db = " << db << std::endl);
    // D(std::cout << "dc = " << dc << std::endl);

    /* Determine which lines intersect the plane */
    Line l1;
    Line l2;

    if ((da < 0 && db < 0 && dc > 0) ||
        (da > 0 && db > 0 && dc < 0) ) {
        l1 = Line(C, A);
        l2 = Line(C, B);
    } else if ((da < 0 && db > 0 && dc < 0) ||
                (da > 0 && db < 0 && dc > 0)) {
        l1 = Line(B, A);
        l2 = Line(B, C);
    } else if ((da > 0 && db < 0 && dc < 0) ||
                (da < 0 && db > 0 && dc > 0)) {
        l1 = Line(A, B);
        l2 = Line(A, C);
    }
    /* handle cases where point belongs to a plane */
    if (std::abs(da) < TOLERANCE) {
        l1 = Line(A, B);
        l2 = Line(A, C);
    } else if (std::abs(db) < TOLERANCE) {
        l1 = Line(B, A);
        l2 = Line(B, C);
    } else if (std::abs(dc) < TOLERANCE) {
        l1 = Line(C, A);
        l2 = Line(C, B);
    }
    return std::make_pair(l1, l2);
}

/*---------------------------------------------------------------*/
Plane::Plane(const Point& p1, const Point& p2, const Point& p3): m_p(p1) {
    m_v1 = Vector(p1, p2);
    m_v2 = Vector(p1, p3);
}

/*---------------------------------------------------------------*/
void Plane::dump() const {
    std::cout << "Dumping plane " << this << std::endl;
    m_p.dump();
    m_v1.dump();
    m_v2.dump();
}

/*---------------------------------------------------------------*/
bool Plane::is_equal(const Plane& rhs) const {
    /* check also dot product */
    Vector n1 = get_normal();
    Vector n2 = rhs.get_normal();

    Vector cross = cross_product(n1, n2);

    Vector diff = static_cast<Vector>(m_p - rhs.m_p);

    float dot1 = dot_product(diff, n1);
    float dot2 = dot_product(diff, n2);

    if ((std::abs(dot1) < TOLERANCE && std::abs(dot2) < TOLERANCE) && cross == 0) {
        return true;
    }
    return false;
}

/*---------------------------------------------------------------*/
bool Plane::is_parallel(const Plane& rhs) const {

    if (is_equal(rhs)) {
        return false;
    }

    Vector n1 = get_normal();
    Vector n2 = rhs.get_normal();
    
    Vector cross = cross_product(n1, n2);
    if (cross == 0) {
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------*/
Vector cross_product(const Vector& v1, const Vector& v2) {

    std::vector<float> v1_coord = v1.get_coordinates();
    std::vector<float> v2_coord = v2.get_coordinates();
    float x = v1_coord[1] * v2_coord[2] - v1_coord[2] * v2_coord[1];
    float y = v1_coord[2] * v2_coord[0] - v1_coord[0] * v2_coord[2];
    float z = v1_coord[0] * v2_coord[1] - v1_coord[1] * v2_coord[0];

    return Vector(x, y, z);
}

/*---------------------------------------------------------------*/
float dot_product(const Vector& lhs, const Vector& rhs) {
    std::vector<float> l_coord = lhs.get_coordinates();
    std::vector<float> r_coord = rhs.get_coordinates();

    return l_coord[0] * r_coord[0] + l_coord[1] * r_coord[1] + l_coord[2] * r_coord[2];
}

/*---------------------------------------------------------------*/
Vector Plane::get_normal() const {
    Vector normal;
    normal = cross_product(m_v1, m_v2);
    return normal;
}

/* Determine whether the triangle is degenerate or not */
/*---------------------------------------------------------------*/
bool Triangle::degenerate() const {
    /* check if they form a line? */
    if (m_p1 == m_p2 || m_p1 == m_p3 || m_p2 == m_p3) {
        return true;
    }
    return false;
}

/*---------------------------------------------------------------*/
float compute_parameter(const Point& Q, const Line& l) {
    Vector d = l.get_direction();
    Point p0 = l.get_point();

    Vector diff = static_cast<Vector>(Q) - static_cast<Vector>(p0);
    std::vector<float> diff_coordinates = diff.get_coordinates();
    std::vector<float> direct_coordinates = d.get_coordinates();

    // D(std::cout << "Direction vector: " << std::endl);
    // D(d.dump());
    // D(std::cout << "Point on a line: " << std::endl);
    // D(p0.dump());
    // D(std::cout << "Point Q: " << std::endl);
    // D(Q.dump());
    // D(std::cout << "diff vector: " << std::endl);
    // diff.dump();


    /* check if point is on a line */
    float tx = 1.0 * diff_coordinates[0] / direct_coordinates[0];
    float ty = 1.0 *  diff_coordinates[1] / direct_coordinates[1];
    float tz = 1.0 * diff_coordinates[2] / direct_coordinates[2];

    // D(std::cout << "tx = " << tx << std::endl);
    // D(std::cout << "ty = " << ty << std::endl);
    // D(std::cout << "tz = " << tz << std::endl);

    /* change later to exception */
    assert(std::abs(tx - ty) < TOLERANCE && std::abs(ty - tz) < TOLERANCE && std::abs(tx - tz) < TOLERANCE);

    return tx;
}

/*---------------------------------------------------------------*/
float compute_distance(const Point& Q, const Plane& pl) {
    Point P  = Point(pl.get_point());
    Vector diff = Vector(Q - P);
    Vector n = pl.get_normal();

    float n_len = n.len();
    assert(std::abs(n_len) > TOLERANCE);

    float dot = dot_product(diff, n);

    return dot / n_len;
}

/*---------------------------------------------------------------*/
bool intersect_2d(const Triangle& T0, const Triangle& T1) {
    
}

/* returns 4 parameters corresponding to the points on intersection line */
std::vector<float> compute_intervals(const Line& l, const Triangle& T0, const Triangle& T1) {

    Plane pl1(T1);
    Plane pl0(T0);

    /* intersect t0 with plane t1 */
    D(std::cout << "\t Computing triangle-plane intersection lines...");
    D(std::cout << "\n\n\n");
    std::pair<Line, Line> lines = get_lines(T0, pl1);
    
    /* lines which intersect plane */
    Line l1 = lines.first;
    Line l2 = lines.second;

     /* compute points */

    D(std::cout << "\t Computing intersection points...");
    D(std::cout << "\n\n\n");

    Point intersection_point_1(pl1, l1);
    Point intersection_point_2(pl1, l2);
    D(intersection_point_1.dump());
    D(intersection_point_2.dump());

     /* compute parameter values */
    D(std::cout << "\t Computing t00, t01...");
    D(std::cout << "\n\n\n");
    float t00 = compute_parameter(intersection_point_1, l);
    float t01 = compute_parameter(intersection_point_2, l);

    /* Now for the second triangle */

    D(std::cout << "\t Computing triangle-plane intersection lines...");
    D(std::cout << "\n\n\n");
    // D(T1.dump());
    // D(pl0.dump());
    lines = get_lines(T1, pl0);
    l1 = lines.first;
    l2 = lines.second;
    // D(l1.dump());
    // D(l2.dump());

    intersection_point_1 = Point(pl0, l1);
    intersection_point_2 = Point(pl0, l2);
    D(intersection_point_1.dump());
    D(intersection_point_2.dump());

    D(std::cout << "\t Computing t10, t11...");
    D(std::cout << "\n\n\n");
    float t10 = compute_parameter(intersection_point_1, l);
    float t11 = compute_parameter(intersection_point_2, l);

    /* now compare the t parameters */

    return std::vector<float> {t00, t01, t10, t11};

}

/*---------------------------------------------------------------*/
bool intersect(const Triangle& T0, const Triangle& T1) {
    /* 1) determine if lhs or rhs (or both) are degenerate and exit algorithm */
    D(std::cout << "Checking if degenerate: " << std::endl);
    if (T0.degenerate() || T1.degenerate()) {
        D(std::cout << "Degenerate.\n\n\n");
        return false;
    }
    D(std::cout << "Not degenerate.\n\n\n");

    /* 2) compute plane equation of lhs */

    D(std::cout << "Computing plane equation of T0..." << std::endl;);
    D(std::cout << "\n\n\n");

    Plane PL0(T0);
    /* 3) compute signed distances from triangle T1 to plane PL0 */
    std::vector<Point> points = T1.get_points();

    D(std::cout << "Computing distances from T1 vertices to plane PL0..." << std::endl;);
    D(std::cout << "\n\n\n");

    float d1 = compute_distance(points[0], PL0);
    float d2 = compute_distance(points[1], PL0);
    float d3 = compute_distance(points[2], PL0);
    /* 4) if they are all of the same sign, exit */
    if ((d1 > 0 && d2 > 0 && d3 > 0) || 
        (d1 < 0 && d2 < 0 && d3 < 0)) {
            D(std::cout << "All of the same size." << std::endl;);
            D(std::cout << "\n\n\n");
            return false;
        }

    D(std::cout << "Computing plane equation of T1..." << std::endl;);
    D(std::cout << "\n\n\n");
    /* 5) compute plane equation of T1 */
    Plane PL1(T1);
    /* 6) if parallel, exit. If coincident, project triangles and perform a 2d triangles intersection
        test */

    D(std::cout << "Checking if planes are parallel..." << std::endl;);
    D(std::cout << "\n\n\n");
    
    if (PL1.is_parallel(PL0)) {
        return false;
    }
    if (PL1.is_equal(PL0)) {
        bool intersect = intersect_2d(T0, T1);
    }

    /* 7) compare distances from triangle T0 to plane PL1. If they are all 
                            of the same sign, exit */
    points = T0.get_points();

    D(std::cout << "Computing distances from T0 vertices to plane PL1...." << std::endl;);
    D(std::cout << "\n\n\n");

    float a1 = compute_distance(points[0], PL1);
    float a2 = compute_distance(points[1], PL1);
    float a3 = compute_distance(points[2], PL1);
    /* 8) if they are all of the same sign, exit */
    if ((d1 > 0 && d2 > 0 && d3 > 0) || 
        (d1 < 0 && d2 < 0 && d3 < 0)) {
            D(std::cout << "All of the same sign." << std::endl;);
            D(std::cout << "\n\n\n");
            return false;
        }

    /* Handle case where vertex belongs to a plane */
    //if (std::abs(d1) < TOLERANCE || std::abs(d1) < TOLERANCE || std::abs(d1) < TOLERANCE)
    /* Compute intersection line, use line-plane intersection */
    D(std::cout << "Computing plane intersection line..." << std::endl;);
    D(std::cout << "\n\n\n");
    Line intersection_line(PL0, PL1);

    /* Compute intervals and check intersection */
    D(std::cout << "Computing intervals..." << std::endl;);
    //D(intersection_line.dump());
    D(std::cout << "\n\n\n");
    std::vector<float> params = compute_intervals(intersection_line, T0, T1);
    float t00 = params[0];
    float t01 = params[1];
    float t10 = params[2];
    float t11 = params[3];

    D(std::cout << "Calculated t values: " << std::endl);
    D(std::cout << t00 << ", " << t01 << ", " << t10 << ", " << t11 << std::endl);
    D(std::cout << "\n\n\n");
    if (std::min(t10, t11) > std::max(t00, t01) || std::min(t00, t01) > std::max(t10, t11)) {
        return false;
    } else {
        return true;
    }
}





