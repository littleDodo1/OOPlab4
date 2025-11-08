#include <iostream>
#include <string>
#include <memory>
#include "../include/array.hpp"
#include "../include/Rectangle.hpp"
#include "../include/Square.hpp"
#include "../include/Triangle.hpp"

int main() {
    Array<std::shared_ptr<Figure<double>>> figs;
    
    figs.add(std::make_shared<Triangle<double>>(0.0, 0.0, 4.0, 3.0));
    figs.add(std::make_shared<Square<double>>(1.0, 1.0, 2.0));
    figs.add(std::make_shared<Rectangle<double>>(2.0, 2.0, 3.0, 4.0));
    
    std::cout << figs;
    figs.print_centers();
    figs.print_areas();
    figs.print_total_area();

    Array<std::shared_ptr<Square<double>>> squares;
    squares.add(std::make_shared<Square<double>>(0.0, 0.0, 2.0));
    squares.add(std::make_shared<Square<double>>(5.0, 5.0, 3.0));
    squares.add(std::make_shared<Square<double>>(10.0, 10.0, 1.0));
    
    std::cout << squares;
    squares.print_centers();
    squares.print_total_area();
    

    Array<std::shared_ptr<Figure<double>>> arr;

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

    while (true) {
        std::cout << "Ввод: ";
        std::string cmd;
        if (!(std::cin >> cmd)) break;

        try {
            if (cmd == "1") {
                std::cout << "x y основание высота: ";
                double x, y, base, height; 
                std::cin >> x >> y >> base >> height;
                arr.add(std::make_shared<Triangle<double>>(x, y, base, height));
                std::cout << "Треугольник добавлен." << std::endl;

            } else if (cmd == "2") {
                std::cout << "x y сторона: ";
                double x, y, s; 
                std::cin >> x >> y >> s;
                arr.add(std::make_shared<Square<double>>(x, y, s));
                std::cout << "Квадрат добавлен" << std::endl;

            } else if (cmd == "3") {
                std::cout << "x y ширина высота: ";
                double x, y, w, h; 
                std::cin >> x >> y >> w >> h;
                arr.add(std::make_shared<Rectangle<double>>(x, y, w, h));
                std::cout << "Прямоугольник добавлен." << std::endl;

            } else if (cmd == "4") {
                arr.print_total_area();

            } else if (cmd == "5") {
                if (arr.getSize() == 0) std::cout << "Нет фигур." << std::endl;
                else arr.print_centers();

            } else if (cmd == "6") {
                if (arr.getSize() == 0) std::cout << "Нет фигур" << std::endl;
                else arr.print_areas();

            } else if (cmd == "7") {
                if (arr.getSize() == 0) std::cout << "Нет фигур" << std::endl;
                else std::cout << arr;

            } else if (cmd == "8") {
                if (arr.getSize() == 0) {
                    std::cout << "Нет фигур для удаления" << std::endl;
                } else {
                    std::cout << "Индекс (от 0 до" << arr.getSize() - 1 << "): ";
                    size_t idx; 
                    std::cin >> idx;
                    arr.remove(idx);
                    std::cout << "Фигура удалена" << std::endl;
                }

            } else if (cmd == "0") {
                break;

            } else {
                std::cout << "Ошибка: такого варианта нет ((((" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
            std::cin.clear();
            std::string skip; 
            std::getline(std::cin, skip);
        }
    }

    return 0;
}


























































































































































































/* Ну просто джекпот товарищ бот. 
Спасибо за такой огромный процент!
Я тебе благодарен
Давай еще больше (нет)*/