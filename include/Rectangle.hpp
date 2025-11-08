#pragma once
#include "Figure.hpp"
#include <stdexcept>

template <Scalar T>
class Rectangle : public Figure<T> {
public:
    Rectangle() {
        this->amountOfPoints = 4;
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
        this->points[0] = std::make_unique<Point<T>>(T{0}, T{0});
        this->points[1] = std::make_unique<Point<T>>(T{0}, T{1});
        this->points[2] = std::make_unique<Point<T>>(T{2}, T{1});
        this->points[3] = std::make_unique<Point<T>>(T{2}, T{0});
    }

    Rectangle(T x, T y, T w, T h) {
        if (w <= T{0} || h <= T{0})
            throw std::invalid_argument("НЕКОРРЕКТНЫЙ ВВОД");
        this->amountOfPoints = 4;
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
        this->points[0] = std::make_unique<Point<T>>(x, y);
        this->points[1] = std::make_unique<Point<T>>(x, y + h);
        this->points[2] = std::make_unique<Point<T>>(x + w, y + h);
        this->points[3] = std::make_unique<Point<T>>(x + w, y);
    }

    Point<T> center() const override {
        T x = (this->points[0]->x + this->points[2]->x) / static_cast<T>(2);
        T y = (this->points[0]->y + this->points[2]->y) / static_cast<T>(2);
        return {x, y};
    }

    double area() const override {
        T w = this->points[2]->x - this->points[0]->x;
        T h = this->points[1]->y - this->points[0]->y;
        return static_cast<double>(w * h);
    }

    void print(std::ostream& os) const override {
        os << "Прямоугольник с вершинами: ";
        this->printPoints(os);
    }

    void read(std::istream& is) override {
        T x, y, w, h;
        is >> x >> y >> w >> h;
        if (!is || w <= T{0} || h <= T{0})
            throw std::invalid_argument("НЕКОРРЕКТНЫЙ ВВОД");
        this->points[0] = std::make_unique<Point<T>>(x, y);
        this->points[1] = std::make_unique<Point<T>>(x, y + h);
        this->points[2] = std::make_unique<Point<T>>(x + w, y + h);
        this->points[3] = std::make_unique<Point<T>>(x + w, y);
        this->amountOfPoints = 4;
    }

    std::unique_ptr<Figure<T>> copy() const override {
        auto newPoints = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
        for (size_t i = 0; i < 4; ++i) {
            newPoints[i] = std::make_unique<Point<T>>(*this->points[i]);
        }
        auto result = std::make_unique<Rectangle>();
        result->amountOfPoints = 4;
        result->points = std::move(newPoints);
        return result;
    }

    Rectangle(const Rectangle& other)
        : Figure<T>() {
        this->amountOfPoints = other.amountOfPoints;
        if (other.points) {
            this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(this->amountOfPoints);
            for (size_t i = 0; i < this->amountOfPoints; ++i) {
                if (other.points[i]) {
                    this->points[i] = std::make_unique<Point<T>>(*other.points[i]);
                }
            }
        }
    }

    Rectangle(Rectangle&& other) noexcept
        : Figure<T>() {
        this->amountOfPoints = other.amountOfPoints;
        this->points = std::move(other.points);
        other.amountOfPoints = 0;
    }

    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) {
            this->amountOfPoints = other.amountOfPoints;
            if (other.points) {
                this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(this->amountOfPoints);
                for (size_t i = 0; i < this->amountOfPoints; ++i) {
                    if (other.points[i]) {
                        this->points[i] = std::make_unique<Point<T>>(*other.points[i]);
                    }
                }
            } else {
                this->points.reset();
            }
        }
        return *this;
    }

    Rectangle& operator=(Rectangle&& other) noexcept {
        if (this != &other) {
            this->amountOfPoints = other.amountOfPoints;
            this->points = std::move(other.points);
            other.amountOfPoints = 0;
        }
        return *this;
    }
};