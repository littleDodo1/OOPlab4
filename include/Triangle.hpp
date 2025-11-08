#pragma once
#include "Figure.hpp"
#include <stdexcept>
#include <cmath>

template <Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() {
        this->amountOfPoints = 3;
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(3);
        this->points[0] = std::make_unique<Point<T>>(T{0}, T{0});
        this->points[1] = std::make_unique<Point<T>>(T{1}, T{2});
        this->points[2] = std::make_unique<Point<T>>(T{2}, T{0});
    }

    Triangle(T x, T y, T base, T height) {
        if (base <= T{0} || height <= T{0})
            throw std::invalid_argument("НЕКОРРЕКТНЫЙ ВВОД");

        this->amountOfPoints = 3;
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(3);
        this->points[0] = std::make_unique<Point<T>>(x, y);
        this->points[1] = std::make_unique<Point<T>>(x + base / 2, y + height);
        this->points[2] = std::make_unique<Point<T>>(x + base, y);
    }

    Point<T> center() const override {
        T x = (this->points[0]->x + this->points[1]->x + this->points[2]->x) / static_cast<T>(3);
        T y = (this->points[0]->y + this->points[1]->y + this->points[2]->y) / static_cast<T>(3);
        return {x, y};
    }

    double area() const override {
        T x1 = this->points[0]->x;
        T y1 = this->points[0]->y;
        T y2 = this->points[1]->y;
        T x3 = this->points[2]->x;
        
        return static_cast<double>(std::abs((x1 - x3) * (y2 - y1) / 2));
    }

    void print(std::ostream& os) const override {
        os << "Треугольник с вершинами: ";
        this->printPoints(os);
    }

    void read(std::istream& is) override {
        T x, y, base, height;
        is >> x >> y >> base >> height;

        if (!is || base <= T{0} || height <= T{0})
            throw std::invalid_argument("НЕКОрректный ВВОД");

        this->points[0] = std::make_unique<Point<T>>(x, y);
        this->points[1] = std::make_unique<Point<T>>(x + base/2, y + height);
        this->points[2] = std::make_unique<Point<T>>(x + base, y);
        this->amountOfPoints = 3;
    }

    std::unique_ptr<Figure<T>> copy() const override {
        auto newPoints = std::make_unique<std::unique_ptr<Point<T>>[]>(3);

        for (size_t i = 0; i < 3; i++) {
            newPoints[i] = std::make_unique<Point<T>>(*this->points[i]);
        }

        auto result = std::make_unique<Triangle>();
        result->amountOfPoints = 3;
        result->points = std::move(newPoints);
        return result;
    }
};