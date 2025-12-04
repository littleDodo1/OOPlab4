#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "Figure.hpp"

template <Scalar T>
class Array {
private:
    std::vector<std::shared_ptr<Figure<T>>> data;

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

    void add(std::shared_ptr<Figure<T>> fig) {
        if (!fig) {
            throw std::invalid_argument("Попытка добавить пустой указатель");
        }
        data.push_back(std::move(fig));
    }

    void remove(size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        data.erase(data.begin() + index);
    }

    std::shared_ptr<Figure<T>>& operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        return data[index];
    }

    const std::shared_ptr<Figure<T>>& operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        return data[index];
    }

    double all_area() const {
        double total = 0.0;
        for (const auto& fig : data) {
            total += static_cast<double>(*fig); 
        }
        return total;
    }

    void print_centers() const {
        for (size_t i = 0; i < data.size(); ++i) {
            Point<T> c = data[i]->center();
            std::cout << i << ": (" << c.x << ", " << c.y << ")" << std::endl;
        }
    }

    void print_areas() const {
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << i << ": " << static_cast<double>(*data[i]) << std::endl;
        }
    }

    void print_total_area() const {
        std::cout << "Общая площадь: " << all_area() << std::endl;
    }

    template <typename FigureType>
        void readFigure() {
            auto fig = std::make_shared<FigureType>();
            std::cin >> *fig;  
            add(fig);
        }

    
    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        os << "Массив фигур (размер: " << arr.data.size() << ")\n";
        for (size_t i = 0; i < arr.data.size(); ++i) {
            os << "[Фигура " << i << "] " << *arr.data[i] << "\n";
        }
        return os;
    }
};