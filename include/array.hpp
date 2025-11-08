#pragma once
#include <iostream>
#include <memory>
#include <vector>

template <class T>
class Array {
private:
    std::vector<T> data;

public:
    size_t getSize() const {
        return data.size();
    }

    Array() = default;
    ~Array() = default;

    Array(const Array& other) = default;
    Array& operator=(const Array& other) = default;

    Array(Array&& other) = default;
    Array& operator=(Array&& other) = default;

    void add(T&& element) {
        data.push_back(std::move(element));
    }

    void remove(size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Индекс за пределами массива");
        }

        data.erase(data.begin() + index);
    }

    T& operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Индекс за пределами массива");
        }

        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Индекс за пределами массива");
        }

        return data[index];
    }

    double allArea() const {
        double otv = 0.0;

        for (size_t i = 0; i < data.size(); ++i) {
            otv += static_cast<double>(*data[i]);
        }

        return otv;
    }

    void print_centers() const {
        std::cout << "Геометрические центры фигур:" << std::endl;

        for (size_t i = 0; i < data.size(); i++) {
            auto center = data[i]->center();
            std::cout << i << ": (" << center.x << ", " << center.y << ")" << std::endl;
        }
    }

    void print_areas() const {
        std::cout << "Площади фигур:" << std::endl;
        
        for (size_t i = 0; i < data.size(); i++) {
            std::cout << i << ": " << static_cast<double>(*data[i]) << std::endl;
        }
    }

    void print_total_area() const {
        std::cout << "Общая площадь:" << std::endl;
        std::cout << allArea() << std::endl;
    }

    template <typename FigureType>
    void readFigure() {
        std::shared_ptr<FigureType> newFig = std::make_shared<FigureType>();
        std::cin >> *newFig;
        add(std::move(newFig));
    }

    friend std::ostream& operator<<(std::ostream& os, const Array& list) {
        os << "Массив (Размер массива: " << list.data.size() << ")" << std::endl;
        for (size_t i = 0; i < list.data.size(); ++i) {
            os << "[Фигура №" << i << "]: " << *list.data[i] << std::endl;
        }
        return os;
    }
};