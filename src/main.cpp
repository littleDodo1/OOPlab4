#include <iostream>
#include <string>
#include <memory>
#include "../include/array.hpp"
#include "../include/Rectangle.hpp"
#include "../include/Square.hpp"
#include "../include/Triangle.hpp"

int main() {
    Array<double> figs;

    figs.add(std::make_shared<Triangle<double>>(0.0, 0.0, 4.0, 3.0));
    figs.add(std::make_shared<Square<double>>(1.0, 1.0, 2.0));
    figs.add(std::make_shared<Rectangle<double>>(2.0, 2.0, 3.0, 4.0));

    std::cout << figs;
    figs.print_centers();
    figs.print_areas();
    figs.print_total_area();

    Array<double> arr;

    std::cout << "\n=== ИНТЕРАКТИВНЫЙ РЕЖИМ ===" << std::endl;
    std::cout << "Введите номер действия:\n"
              << "  1: добавить треугольник\n"
              << "  2: добавить квадрат\n"
              << "  3: добавить прямоугольник\n"
              << "  4: суммарная площадь\n"
              << "  5: вывести центры всех фигур\n"
              << "  6: вывести площади всех фигур\n"
              << "  7: вывести все фигуры\n"
              << "  8: удалить фигуру\n"
              << "  0: выход" << std::endl;

    std::string cmd;
    while (std::cin >> cmd) {
        try {
            if (cmd == "1") {
                double x, y, base, height;
                std::cout << "x y основание высота: ";
                std::cin >> x >> y >> base >> height;
                arr.add(std::make_shared<Triangle<double>>(x, y, base, height));
                std::cout << "Треугольник добавлен." << std::endl;

            } else if (cmd == "2") {
                double x, y, s;
                std::cout << "x y сторона: ";
                std::cin >> x >> y >> s;
                arr.add(std::make_shared<Square<double>>(x, y, s));
                std::cout << "Квадрат добавлен." << std::endl;

            } else if (cmd == "3") {
                double x, y, w, h;
                std::cout << "x y ширина высота: ";
                std::cin >> x >> y >> w >> h;
                arr.add(std::make_shared<Rectangle<double>>(x, y, w, h));
                std::cout << "Прямоугольник добавлен." << std::endl;

            } else if (cmd == "4") {
                arr.print_total_area();

            } else if (cmd == "5") {
                if (arr.getSize() == 0) std::cout << "Нет фигур." << std::endl;
                else arr.print_centers();

            } else if (cmd == "6") {
                if (arr.getSize() == 0) std::cout << "Нет фигур." << std::endl;
                else arr.print_areas();

            } else if (cmd == "7") {
                if (arr.getSize() == 0) std::cout << "Нет фигур." << std::endl;
                else std::cout << arr;

            } else if (cmd == "8") {
                if (arr.getSize() == 0) {
                    std::cout << "Нет фигур для удаления." << std::endl;
                } else {
                    size_t idx;
                    std::cout << "Индекс (от 0 до " << arr.getSize() - 1 << "): ";
                    std::cin >> idx;
                    arr.remove(idx);
                    std::cout << "Фигура удалена." << std::endl;
                }

            } else if (cmd == "0") {
                break;

            } else {
                std::cout << "Неизвестная команда." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        if (cmd != "0") {
            std::cout << "Ввод: ";
        }
    }

    return 0;
}