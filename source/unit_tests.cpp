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

    D(pl1.dump());
    D(pl2.dump());

    ASSERT_EQ(pl1, pl2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, CrossProduct) {

    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    D(v1.dump());
    D(v2.dump());

    Vector norm = cross_product(v1, v2);
    D(norm.dump());
    Vector res(7, -8, -10);
    ASSERT_EQ(norm, res);
}

/*---------------------------------------------------------------*/
TEST(Triangles, DotProduct) {

    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    float dot = dot_product(v1, v2);
    ASSERT_EQ(dot, 5);
}

/*---------------------------------------------------------------*/
TEST(Triangles, VectorConversion) {

    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    float dot = dot_product(v1, static_cast<Vector>(p1));
    ASSERT_EQ(dot, -4);
}

/*---------------------------------------------------------------*/
TEST(Triangles, PlanePlaneIntersection) {
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Point p4(2, 3, 1);
    Point p5(1, 1, 1);
    Point p6(-1, -1, -3);

    Plane pl1(p1, p2, p3);
    Plane pl2(p4, p5, p6);

    Line l1(pl1, pl2);; 

    l1.dump();

    //ASSERT_EQ(l1, l2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, PlanePlaneIntersection2) {
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Point p4(2, 3, 5);
    Point p5(3, 8, 7);
    Point p6(-1, -1, -3);

    Plane pl1(p1, p2, p3);
    Plane pl2(p4, p5, p6);


    Line l1(pl1, pl2); 

    l1.dump();

    //ASSERT_EQ(l1, l2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, PlanePlaneIntersection3) {
    Point p1(1, 1, 1);
    Point p2(15, -1, -32);
    Point p3(21, -8, -40);

    Point p4(2, 3, 5);
    Point p5(3, 8, 7);
    Point p6(-1, -1, -3);

    Plane pl1(p1, p2, p3);
    Plane pl2(p4, p5, p6);


    Line l1(pl1, pl2); 

    l1.dump();

    //ASSERT_EQ(l1, l2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, PlanePlaneParallel) {
    Point p1(1, 1, 1);
    Point p2(2, 2, 2);
    Point p3(4, 1, 1);

    Point p4(2, 2, 2);
    Point p5(4, 4, 4);
    Point p6(8, 2, 2);

    Plane pl1(p1, p2, p3);
    Plane pl2(p4, p5, p6);

    //Point p(1.46, 1.46, -2.75);
    //Vector a(-20, -20, 2);

    Line l1(pl1, pl2);
    //Line l2(p, a); 

    l1.dump();
    //l2.dump();

    //ASSERT_EQ(l1, l2);
}

/*---------------------------------------------------------------*/
TEST(Triangles, TriangleNotDegenerate) {
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(-1, -2, 0);

    Triangle t(p1, p2, p3);

    ASSERT_FALSE(t.degenerate());
}

/*---------------------------------------------------------------*/
TEST(Triangles, TriangleDegenerate) {
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(2, 0, 1);

    Triangle t(p1, p2, p3);

    ASSERT_TRUE(t.degenerate());
}

/*---------------------------------------------------------------*/
TEST(Triangles, PlaneTriangleConstructor) {
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(-1, -2, 0);

    Triangle t(p1, p2, p3);
    Plane pl(t);

    D(pl.dump());

}

/*---------------------------------------------------------------*/
TEST(Triangles, PointOperators) {
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);

    Point p3(-1, 1, 0);
    Point p4(3, 1, 2);

    Point p5 = p1 - p2;
    Point p6 = p1 + p2;

    ASSERT_EQ(p5, p3);
    ASSERT_EQ(p6, p4);
}

/*---------------------------------------------------------------*/
TEST(Triangles, PointPlaneDistance) {
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(-1, -2, 0);

    Plane pl(p1, p2, p3);
    
    Point p(6, 10, -23);

    float dist = 25.7883;
    float computed_dist = compute_distance(p, pl);

    float precision = 1e-4;
    ASSERT_TRUE(std::abs(dist - computed_dist) < precision);
}

/*---------------------------------------------------------------*/
TEST(Triangles, PointPlaneDistanceNegative) {
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(-1, -2, 0);

    Plane pl(p1, p2, p3);
    
    Point p(-6, -10, 23);

    float dist = -24.6336;
    float computed_dist = compute_distance(p, pl);
    D(std::cout << "Computed distance: " << computed_dist << std::endl);

    float precision = 1e-4;
    ASSERT_TRUE(std::abs(dist - computed_dist) < precision);
}

/*---------------------------------------------------------------*/
TEST(Triangles, PlanePlaneParallel2) {
    Point p1(1, 1, 1);
    Point p2(3, 3, 3);
    Point p3(4, 1, 1);

    Point p4(2, 2, 2);
    Point p5(4, 4, 4);
    Point p6(8, 2, 2);

    Plane pl1(p1, p2, p3);
    Plane pl2(p4, p5, p6);
    
    ASSERT_FALSE(pl1.is_parallel(pl2));
    ASSERT_TRUE(pl1.is_equal(pl2));

    p4 = Point(-1, -1, 1);
    p5 = Point(-3, -3, 3);
    p6 = Point(-4, -1, 1);
    pl2 = Plane(p4, p5, p6);

    ASSERT_FALSE(pl1.is_parallel(pl2));
}

/*---------------------------------------------------------------*/
TEST(Triangles, LinePlaneIntersection) {
    Point A(1, 1, 1);
    Point B(2, 0, 1);
    Point C(-1, -2, 0);

    Point d(-1, 2, 5);
    Point E(2, 4, 2);
    Point F(1, -2, 0);

    Plane P0(A, B, C);
    Plane P1(d, E, F);
    Triangle t(d, E, F);

    float d1 = compute_distance(d, P0);
    float d2 = compute_distance(E, P0);
    float d3 = compute_distance(F, P0);

    ASSERT_FALSE((d1 > 0 && d2 > 0 && d3 > 0) || 
        (d1 < 0 && d2 < 0 && d3 < 0));

    D(std::cout << "d1 = " << d1 << " d2 = " << d2 << " d3 = " << d3 << std::endl;)

    if (d1 < 0 && d2 < 0 && d3 > 0) {
        Line l1(d, F);
        Line l2(E, F);
    
        Point ans1(0.8261, -1.6522, 0.4348);
        Point ans2(1.6667, 2, 1.3333);  

        Point intersection_point_1(P0, l1);

        //D(l1.dump());
        D(intersection_point_1.dump());
        D(std::cout << "Expected point 1: " << std::endl);
        D(ans1.dump());

        Point intersection_point_2(P0, l2);
        D(l2.dump());
        D(intersection_point_2.dump());
        D(std::cout << "Expected point 2: " << std::endl);
        D(ans2.dump());


        ASSERT_EQ(intersection_point_1, ans1);
        ASSERT_EQ(intersection_point_2, ans2);
    }

}

/*---------------------------------------------------------------*/
// TEST(Triangles, TrianglePlaneInterval) {
//     Point p1(1, 1, 1);
//     Point p2(2, 0, 1);
//     Point p3(-1, -2, 0);

//     Point p4(-1, 2, 5);
//     Point p5(2, 4, 2);
//     Point p6(1, -2, 0);


//     Triangle t0(p1, p2, p3);
//     Triangle t1(p4, p5, p6);

//     Plane pl0(t1);

// }

/*---------------------------------------------------------------*/
// TEST(Triangles, TrianglePlaneInterval) {
//     Point p1(1, 1, 1);
//     Point p2(2, 0, 1);
//     Point p3(-1, -2, 0);

//     Point p4(-1, 2, 5);
//     Point p5(2, 4, 2);
//     Point p6(1, -2, 0);


//     Triangle t0(p1, p2, p3);
//     Triangle t1(p4, p5, p6);

//     Plane pl0(t1);

// }


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}