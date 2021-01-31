#include <gtest/gtest.h>
#include "triangles.h"

/* TDD:
1) write a new test
2) run the code to see the test fail
3) write code to pass the test
4) refactor the code
5) make sure the test still gets passed
6) repeat

Also: a good practice is to write a test that should be passed
         and also a test that should fail
*/

/*---------------------------------------------------------------*/
TEST(Triangles, PointEqual) {
    Point p1(1.0, 2.1, 3.0);
    Point p2(1.0, 2.100000000001, 3.0);
    Point p3(1.0, 2.101, 3.0);

    ASSERT_EQ(p1, p2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, VectorEqual) {
    Point p1(1.0, 2.0, 3.0);
    Point p2(2.0, 1.0, 3.0);

    Vector v1(p1, p2);
    Vector v2(1.0, -1.0, 0.0);

    ASSERT_EQ(v1, v2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, VectorMulByNum) {
    Vector v1(1.0, -1.0, 0.0);

    Vector v2 = v1 * 3;

    Vector v4 = 3 * v1;

    Vector v3(3.0, -3.0, 0.0);

    ASSERT_EQ(v3, v2);
    ASSERT_EQ(v4, v3);
}

/*---------------------------------------------------------------*/
TEST(Triangles, TriangleConstructorVectors) {
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(3, 2, 1);

    Triangle t1(p1, p2, p3);

    D(t1.dump());

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    Triangle t2(p1, v1, v2);

    D(t2.dump());

    ASSERT_EQ(t1, t2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, Print) {
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(3, 2, 1);

    Vector v1(2, 4, 1);

    Line l1(p2, v1);

    Triangle t1(p1, p2, p3);

    D(l1.dump());
    D(p1.dump());
    D(v1.dump());
    D(t1.dump());
}

/*---------------------------------------------------------------*/
TEST(Triangles, LineConstructor) {
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);

    Vector v1(2, -2, 3);

    Line l1(p1, v1);
    Line l2(p1, p2);

    D(l1.dump());
    D(l2.dump());

    ASSERT_EQ(l1, l2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, PlaneConstructor) {
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    Plane pl1(p1, p2, p3);
    Plane pl2(p1, v1, v2);

    ASSERT_EQ(pl1, pl2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, PlanePlaneIntersection) {
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Point p4(0, 0, 0);
    Point p5(1, 1, 1);
    Point p6(-1, -1, -1);

    Plane pl1(p1, p2, p3);
    Plane pl2(p4, p5, p6);

    Line l1(pl1, pl2);
    Line l2(); // add impl

    ASSERT_EQ(l1, l2);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}