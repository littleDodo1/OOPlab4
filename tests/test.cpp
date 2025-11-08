#include "../include/array.hpp"
#include "../include/Rectangle.hpp"
#include "../include/Square.hpp"
#include "../include/Triangle.hpp"
#include "../include/Figure.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <memory>

static constexpr double EPS = 1e-6;

bool eq(double a, double b, double eps = EPS) {
    return std::abs(a - b) < eps;
}

TEST(SquareTest, CenterCalculation) {
    Square<double> s(0.0, 0.0, 4.0);
    Point<double> c = s.center();
    EXPECT_NEAR(c.x, 2.0, EPS);
    EXPECT_NEAR(c.y, 2.0, EPS);
}

TEST(SquareTest, InputOutput) {
    std::istringstream in("1.5 -2.0 5.0");
    Square<double> s;
    EXPECT_NO_THROW(in >> s);

    std::ostringstream out;
    out << s;
    EXPECT_FALSE(out.str().empty());
}

TEST(SquareTest, Clone) {
    Square<double> original(10.0, 20.0, 7.5);
    auto copy = original.copy();
    ASSERT_NE(copy, nullptr);

    auto* s_copy = dynamic_cast<Square<double>*>(copy.get());
    ASSERT_NE(s_copy, nullptr);
    EXPECT_TRUE(eq(s_copy->area(), original.area()));
    EXPECT_TRUE(eq(s_copy->center().x, original.center().x));
    EXPECT_TRUE(eq(s_copy->center().y, original.center().y));
}

TEST(SquareTest, EqualityByArea) {
    Square<double> s1(1.0, 1.0, 4.0);  
    Square<double> s2(5.0, 5.0, 4.0);  
    EXPECT_TRUE(s1 == s2);  
}

TEST(SquareTest, InvalidInputThrows) {
    Square<double> s;
    std::istringstream in("0 0 -2.5");
    EXPECT_THROW(in >> s, std::invalid_argument);
}

TEST(RectangleTest, AreaAndCenter) {
    Rectangle<double> r(1.0, 1.0, 3.0, 2.0);
    EXPECT_NEAR(r.area(), 6.0, EPS);
    Point<double> c = r.center();
    EXPECT_NEAR(c.x, 2.5, EPS);
    EXPECT_NEAR(c.y, 2.0, EPS);
}

TEST(RectangleTest, InvalidDimensionsThrow) {
    Rectangle<double> r;
    std::istringstream in("0 0 -1 2");
    EXPECT_THROW(in >> r, std::invalid_argument);
}

TEST(TriangleTest, AreaAndCenter) {
    Triangle<double> t(0.0, 0.0, 4.0, 4.0);  
    EXPECT_NEAR(t.area(), 8.0, EPS);
    Point<double> c = t.center();
    EXPECT_NEAR(c.x, (0.0 + 2.0 + 4.0) / 3.0, EPS);
    EXPECT_NEAR(c.y, (0.0 + 4.0 + 0.0) / 3.0, EPS);
}

TEST(TriangleTest, InputOutputAndClone) {
    std::istringstream in("1.0 1.0 3.0 2.0");
    Triangle<double> t;
    EXPECT_NO_THROW(in >> t);

    auto copy = t.copy();
    auto* t_copy = dynamic_cast<Triangle<double>*>(copy.get());
    ASSERT_NE(t_copy, nullptr);
    EXPECT_TRUE(eq(t_copy->area(), t.area()));
    EXPECT_TRUE(eq(t_copy->center().x, t.center().x));
    EXPECT_TRUE(eq(t_copy->center().y, t.center().y));
}

TEST(TriangleTest, InvalidInputThrows) {
    Triangle<double> t;
    std::istringstream in("0 0 -1 2");
    EXPECT_THROW(in >> t, std::invalid_argument);
}

TEST(PolymorphicTest, CloneThroughBasePointer) {
    Square<double> s(5.0, 5.0, 3.0);
    Figure<double>* base = &s;
    auto copy = base->copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_TRUE(eq(copy->area(), s.area()));
}

TEST(PolymorphicTest, SumAreaViaBasePointer) {
    std::vector<std::unique_ptr<Figure<double>>> figs;
    figs.push_back(std::make_unique<Square<double>>(0, 0, 2.0));      
    figs.push_back(std::make_unique<Rectangle<double>>(0, 0, 2.0, 3.0)); 
    figs.push_back(std::make_unique<Triangle<double>>(0, 0, 4.0, 4.0));      

    double total = 0.0;
    for (const auto& fig : figs) {
        total += static_cast<double>(*fig);
    }
    EXPECT_NEAR(total, 18.0, EPS);
}

TEST(EqualityTest, DifferentTypesWithSameArea) {
    Square<double> s(0, 0, 2.0);
    Rectangle<double> r(0, 0, 1.0, 4.0);
    Triangle<double> t(0, 0, 4.0, 2.0);

    EXPECT_TRUE(s == r);
    EXPECT_TRUE(r == t);
    EXPECT_TRUE(s == t);
}

TEST(ArrayTest, AddAndRemove) {
    Array<std::shared_ptr<Figure<double>>> arr;
    arr.add(std::make_shared<Square<double>>(0, 0, 2.0));
    EXPECT_EQ(arr.getSize(), 1);

    arr.remove(0);
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(ArrayTest, TotalArea) {
    Array<std::shared_ptr<Figure<double>>> arr;
    arr.add(std::make_shared<Square<double>>(0, 0, 2.0));
    arr.add(std::make_shared<Rectangle<double>>(0, 0, 3, 2));
    arr.add(std::make_shared<Triangle<double>>(0, 0, 2, 2));

    double total = arr.allArea();
    EXPECT_NEAR(total, 12.0, EPS);
}

TEST(ArrayTest, PrintCenters) {
    Array<std::shared_ptr<Figure<double>>> arr;
    arr.add(std::make_shared<Square<double>>(0, 0, 2.0));
    
    std::ostringstream out;
    std::streambuf* orig = std::cout.rdbuf(out.rdbuf());
    arr.print_centers();
    std::cout.rdbuf(orig);
    
    std::string output = out.str();
    EXPECT_NE(output.find("Геометрические центры фигур"), std::string::npos);
}

TEST(ArrayTest, PrintAreas) {
    Array<std::shared_ptr<Figure<double>>> arr;
    arr.add(std::make_shared<Square<double>>(0, 0, 2.0));
    
    std::ostringstream out;
    std::streambuf* orig = std::cout.rdbuf(out.rdbuf());
    arr.print_areas();
    std::cout.rdbuf(orig);
    
    std::string output = out.str();
    EXPECT_NE(output.find("Площади фигур"), std::string::npos);
}

TEST(ArrayTest, CopyConstructor) {
    Array<std::shared_ptr<Figure<double>>> arr1;
    arr1.add(std::make_shared<Square<double>>(0, 0, 2.0));
    
    Array<std::shared_ptr<Figure<double>>> arr2(arr1);
    EXPECT_EQ(arr1.getSize(), arr2.getSize());
    EXPECT_NEAR(arr1.allArea(), arr2.allArea(), EPS);
}

TEST(ArrayTest, MoveConstructor) {
    Array<std::shared_ptr<Figure<double>>> arr1;
    arr1.add(std::make_shared<Square<double>>(0, 0, 2.0));
    
    double area_before = arr1.allArea();
    Array<std::shared_ptr<Figure<double>>> arr2(std::move(arr1));
    
    EXPECT_EQ(arr1.getSize(), 0);
    EXPECT_EQ(arr2.getSize(), 1);
    EXPECT_NEAR(arr2.allArea(), area_before, EPS);
}

TEST(ArrayTest, AssignmentOperator) {
    Array<std::shared_ptr<Figure<double>>> arr1;
    arr1.add(std::make_shared<Square<double>>(0, 0, 2.0));
    
    Array<std::shared_ptr<Figure<double>>> arr2;
    arr2 = arr1;
    
    EXPECT_EQ(arr1.getSize(), arr2.getSize());
    EXPECT_NEAR(arr1.allArea(), arr2.allArea(), EPS);
}

TEST(ArrayTest, MoveAssignmentOperator) {
    Array<std::shared_ptr<Figure<double>>> arr1;
    arr1.add(std::make_shared<Square<double>>(0, 0, 2.0));
    
    double area_before = arr1.allArea();
    Array<std::shared_ptr<Figure<double>>> arr2;
    arr2 = std::move(arr1);
    
    EXPECT_EQ(arr1.getSize(), 0);
    EXPECT_EQ(arr2.getSize(), 1);
    EXPECT_NEAR(arr2.allArea(), area_before, EPS);
}

TEST(ArrayTest, OutOfBoundsAccess) {
    Array<std::shared_ptr<Figure<double>>> arr;
    EXPECT_THROW(arr[0], std::out_of_range);
    
    arr.add(std::make_shared<Square<double>>(0, 0, 2.0));
    EXPECT_NO_THROW(arr[0]);
    EXPECT_THROW(arr[1], std::out_of_range);
}

TEST(ArrayTest, OutOfBoundsRemove) {
    Array<std::shared_ptr<Figure<double>>> arr;
    EXPECT_THROW(arr.remove(0), std::out_of_range);
    
    arr.add(std::make_shared<Square<double>>(0, 0, 2.0));
    EXPECT_NO_THROW(arr.remove(0));
    EXPECT_THROW(arr.remove(0), std::out_of_range);
}

TEST(ArrayTemplateTest, DifferentArrayTypes) {
    Array<std::shared_ptr<Figure<double>>> figure_array;
    figure_array.add(std::make_shared<Square<double>>(0, 0, 2.0));
    figure_array.add(std::make_shared<Triangle<double>>(0, 0, 3.0, 4.0));
    EXPECT_EQ(figure_array.getSize(), 2);
    
    Array<std::shared_ptr<Square<double>>> square_array;
    square_array.add(std::make_shared<Square<double>>(0, 0, 2.0));
    square_array.add(std::make_shared<Square<double>>(1, 1, 3.0));
    EXPECT_EQ(square_array.getSize(), 2);
    
    Array<std::shared_ptr<Triangle<double>>> triangle_array;
    triangle_array.add(std::make_shared<Triangle<double>>(0, 0, 2.0, 3.0));
    EXPECT_EQ(triangle_array.getSize(), 1);
}

TEST(ScalarTypesTest, DifferentScalarTypes) {
    Square<double> s_double(1.0, 2.0, 3.0);
    EXPECT_NEAR(s_double.area(), 9.0, EPS);
    
    Square<int> s_int(1, 2, 3);
    EXPECT_NEAR(s_int.area(), 9.0, EPS);
    
    Square<float> s_float(1.0f, 2.0f, 3.0f);
    EXPECT_NEAR(s_float.area(), 9.0, EPS);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}