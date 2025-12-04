#pragma once
#include <iostream>
#include <memory>
#include <cmath>
#include <concepts>
#include "Figure.hpp"

template <class T>
concept Scalar = std::is_arithmetic_v<T>;

template <class T>
struct Point {
    T x = 0;
    T y = 0;

    Point() = default;
    Point(T x_, T y_) : x(x_), y(y_) {}
};

template <Scalar T>
class Figure {
protected:
    std::unique_ptr<std::unique_ptr<Point<T>>[]> points;
    size_t amountOfPoints;

public:
    Figure() : points(nullptr), amountOfPoints(0) {}

    Figure(size_t n, std::unique_ptr<std::unique_ptr<Point<T>>[]>&& inputPoints)
        : amountOfPoints(n), points(std::move(inputPoints)) {}

    virtual ~Figure() = default;

    virtual Point<T> center() const = 0;
    virtual double area() const = 0;

    explicit operator double() const {
        return area();
    }

    virtual void print_points(std::ostream& os) const {
        for (size_t i = 0; i < amountOfPoints; ++i) {
            if (points[i]) {
                os << "(" << points[i]->x << ", " << points[i]->y << ")";
                if (i + 1 < amountOfPoints) os << " ";
            }
        }
    }

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    virtual std::unique_ptr<Figure<T>> copy() const = 0;

    friend bool operator==(const Figure<T>& lfig, const Figure<T>& rfig) {
        constexpr double eps = 1e-6;
        return std::abs(lfig.area() - rfig.area()) < eps;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read(is);
        return is;
    }
};