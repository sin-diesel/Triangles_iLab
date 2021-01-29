#include <gtest/gtest.h>
#include "triangles.h"

/*---------------------------------------------------------------*/
TEST(Triangles, Point_equal) {
    Point p1(1.0, 2.1, 3.0);
    Point p2(1.0, 2.100000000001, 3.0);
    Point p3(1.0, 2.101, 3.0);

    ASSERT_EQ(p1, p2);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}