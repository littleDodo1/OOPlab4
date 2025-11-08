#pragma once
#include "Figure.hpp"
#include <stdexcept>

template <Scalar T>
class Square : public Figure<T> {
public:
    Square() {
        this->amountOfPoints = 4;
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
        this->points[0] = std::make_unique<Point<T>>(T{0}, T{0});
        this->points[1] = std::make_unique<Point<T>>(T{0}, T{1});
        this->points[2] = std::make_unique<Point<T>>(T{1}, T{1});
        this->points[3] = std::make_unique<Point<T>>(T{1}, T{0});
    }

    Square(T x, T y, T side) {
        if (side <= T{0})
            throw std::invalid_argument("НЕКОРРЕКТНЫЙ ВВОД");
            
        this->amountOfPoints = 4;
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
        this->points[0] = std::make_unique<Point<T>>(x, y);
        this->points[1] = std::make_unique<Point<T>>(x, y + side);
        this->points[2] = std::make_unique<Point<T>>(x + side, y + side);
        this->points[3] = std::make_unique<Point<T>>(x + side, y);
    }

    Point<T> center() const override {
        T x = (this->points[0]->x + this->points[2]->x) / static_cast<T>(2);
        T y = (this->points[0]->y + this->points[2]->y) / static_cast<T>(2);
        return {x, y};
    }

    double area() const override {
        T side = this->points[1]->y - this->points[0]->y;
        return static_cast<double>(side * side);
    }

    void print(std::ostream& os) const override {
        os << "Квадрат с вершинами: ";
        this->printPoints(os);
    }

    void read(std::istream& is) override {
        T x, y, s;
        is >> x >> y >> s;
        if (!is || s <= T{0})
            throw std::invalid_argument("НЕКОРРЕКТНЫЙ ВВОД");

        this->points[0] = std::make_unique<Point<T>>(x, y);
        this->points[1] = std::make_unique<Point<T>>(x, y + s);
        this->points[2] = std::make_unique<Point<T>>(x + s, y + s);
        this->points[3] = std::make_unique<Point<T>>(x + s, y);
        this->amountOfPoints = 4;
    }

    std::unique_ptr<Figure<T>> copy() const override {
        auto newPoints = std::make_unique<std::unique_ptr<Point<T>>[]>(4);

        for (size_t i = 0; i < 4; ++i) {
            newPoints[i] = std::make_unique<Point<T>>(*this->points[i]);
        }

        auto result = std::make_unique<Square>();
        result->amountOfPoints = 4;
        result->points = std::move(newPoints);
        return result;
    }

    Square(const Square& other)
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

    Square(Square&& other) noexcept
        : Figure<T>() {
        this->amountOfPoints = other.amountOfPoints;
        this->points = std::move(other.points);
        other.amountOfPoints = 0;
    }

    Square& operator=(const Square& other) {
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

    Square& operator=(Square&& other) noexcept {
        if (this != &other) {
            this->amountOfPoints = other.amountOfPoints;
            this->points = std::move(other.points);
            other.amountOfPoints = 0;
        }
        return *this;
    }
};