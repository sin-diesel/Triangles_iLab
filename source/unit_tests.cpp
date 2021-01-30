#include <gtest/gtest.h>
#include "triangles.h"

/*---------------------------------------------------------------*/
TEST(Triangles, Point_equal) {
    Point p1(1.0, 2.1, 3.0);
    Point p2(1.0, 2.100000000001, 3.0);
    Point p3(1.0, 2.101, 3.0);

    ASSERT_EQ(p1, p2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, Vector_equal) {
    Point p1(1.0, 2.0, 3.0);
    Point p2(2.0, 1.0, 3.0);

    Vector v1(p1, p2);
    Vector v2(1.0, -1.0, 0.0);

    ASSERT_EQ(v1, v2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, Vector_mult_by_num) {
    Vector v1(1.0, -1.0, 0.0);

    Vector v2 = v1 * 3;

    Vector v4 = 3 * v1;

    Vector v3(3.0, -3.0, 0.0);

    ASSERT_EQ(v3, v2);
    ASSERT_EQ(v4, v3);
}

/*---------------------------------------------------------------*/
TEST(Triangles, Triangle_constructor_vectors) {
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


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}