#include <iomanip>
#include <iostream>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif

#include "Bicycle.h"
#include "Car.h"
#include "Cart.h"

void base_menu_actions(TransportVehicle& vehicle, int choice)
{
    switch (choice)
    {
    case 1:
        vehicle.print_header();
        vehicle.print_table();
        break;
    case 2:
    {
        std::string name;
        std::cout << "Введите новое название: ";
        std::getline(std::cin >> std::ws, name);
        vehicle.SetName(name);
        break;
    }
    case 3:
    {
        double distance;
        std::cout << "Введите новое расстояние: ";
        std::cin >> distance;
        vehicle.SetDistance(distance);
        break;
    }
    case 4:
    {
        double rate;
        std::cout << "Введите новую стоимость за км для пассажиров: ";
        std::cin >> rate;
        vehicle.SetPassengerRate(rate);
        break;
    }
    case 5:
    {
        double rate;
        std::cout << "Введите новую стоимость за км для груза: ";
        std::cin >> rate;
        vehicle.SetCargoRate(rate);
        break;
    }
    case 6:
    {
        double speed;
        std::cout << "Введите новую скорость: ";
        std::cin >> speed;
        vehicle.SetSpeed(speed);
        break;
    }
    case 7:
        std::cout << "Название: " << vehicle.GetName() << std::endl;
        break;
    case 8:
        std::cout << "Расстояние: " << vehicle.GetDistance() << std::endl;
        break;
    case 9:
        std::cout << "Стоимость за км (пассажиры): " << vehicle.GetPassengerRate() << std::endl;
        break;
    case 10:
        std::cout << "Стоимость за км (груз): " << vehicle.GetCargoRate() << std::endl;
        break;
    case 11:
        std::cout << "Скорость: " << vehicle.GetSpeed() << std::endl;
        break;
    case 12:
    {
        int passengers;
        std::cout << "Введите количество пассажиров: ";
        std::cin >> passengers;
        std::cout << "Стоимость перевозки пассажиров: "
                  << vehicle.cost_passengers(passengers) << std::endl;
        std::cout << "Время в пути: " << vehicle.time_in_path() << " ч" << std::endl;
        break;
    }
    case 13:
    {
        double cargo;
        std::cout << "Введите массу груза (кг): ";
        std::cin >> cargo;
        std::cout << "Стоимость перевозки груза: " << vehicle.cost_cargo(cargo) << std::endl;
        std::cout << "Время в пути: " << vehicle.time_in_path() << " ч" << std::endl;
        break;
    }
    default:
        std::cout << "Неверный пункт!" << std::endl;
        break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void menu_car(Car& car)
{
    while (true)
    {
        car.menu();
        std::cout << "Выберите пункт: ";
        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 0)
        {
            return;
        }
        if (choice >= 1 && choice <= 13)
        {
            base_menu_actions(car, choice);
            continue;
        }
        switch (choice)
        {
        case 14:
        {
            double price;
            std::cout << "Введите стоимость топлива: ";
            std::cin >> price;
            car.SetFuelPrice(price);
            break;
        }
        case 15:
            std::cout << "Стоимость топлива: " << car.GetFuelPrice() << std::endl;
            break;
        case 16:
        {
            int capacity;
            std::cout << "Введите вместимость пассажиров: ";
            std::cin >> capacity;
            car.SetPassengerCapacity(capacity);
            break;
        }
        case 17:
            std::cout << "Вместимость пассажиров: " << car.GetPassengerCapacity() << std::endl;
            break;
        case 18:
        {
            double volume;
            std::cout << "Введите объём багажника: ";
            std::cin >> volume;
            car.SetTrunkVolume(volume);
            break;
        }
        case 19:
            std::cout << "Объём багажника: " << car.GetTrunkVolume() << std::endl;
            break;
        default:
            std::cout << "Неверный пункт!" << std::endl;
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void menu_bicycle(Bicycle& bicycle)
{
    while (true)
    {
        bicycle.menu();
        std::cout << "Выберите пункт: ";
        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 0)
        {
            return;
        }
        if (choice >= 1 && choice <= 13)
        {
            base_menu_actions(bicycle, choice);
            continue;
        }
        switch (choice)
        {
        case 14:
        {
            int gears;
            std::cout << "Введите количество передач: ";
            std::cin >> gears;
            bicycle.SetGearCount(gears);
            break;
        }
        case 15:
            std::cout << "Передач: " << bicycle.GetGearCount() << std::endl;
            break;
        case 16:
        {
            int value;
            std::cout << "Есть багажник? (1 - да, 0 - нет): ";
            std::cin >> value;
            bicycle.SetHasCargoRack(value != 0);
            break;
        }
        case 17:
            std::cout << "Наличие багажника: " << (bicycle.GetHasCargoRack() ? "Да" : "Нет") << std::endl;
            break;
        case 18:
        {
            double maxCargo;
            std::cout << "Введите максимальный груз: ";
            std::cin >> maxCargo;
            bicycle.SetMaxCargo(maxCargo);
            break;
        }
        case 19:
            std::cout << "Максимальный груз: " << bicycle.GetMaxCargo() << std::endl;
            break;
        default:
            std::cout << "Неверный пункт!" << std::endl;
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void menu_cart(Cart& cart)
{
    while (true)
    {
        cart.menu();
        std::cout << "Выберите пункт: ";
        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 0)
        {
            return;
        }
        if (choice >= 1 && choice <= 13)
        {
            base_menu_actions(cart, choice);
            continue;
        }
        switch (choice)
        {
        case 14:
        {
            int horses;
            std::cout << "Введите количество лошадей: ";
            std::cin >> horses;
            cart.SetHorseCount(horses);
            break;
        }
        case 15:
            std::cout << "Количество лошадей: " << cart.GetHorseCount() << std::endl;
            break;
        case 16:
        {
            double rest;
            std::cout << "Введите время отдыха: ";
            std::cin >> rest;
            cart.SetRestTime(rest);
            break;
        }
        case 17:
            std::cout << "Время отдыха: " << cart.GetRestTime() << std::endl;
            break;
        case 18:
        {
            double payload;
            std::cout << "Введите грузоподъёмность: ";
            std::cin >> payload;
            cart.SetMaxPayload(payload);
            break;
        }
        case 19:
            std::cout << "Грузоподъёмность: " << cart.GetMaxPayload() << std::endl;
            break;
        default:
            std::cout << "Неверный пункт!" << std::endl;
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "ru_RU.UTF-8");

    Car car;
    Bicycle bicycle;
    Cart cart;

    std::cout << "Введите данные для автомобиля" << std::endl;
    std::cin >> car;
    std::cout << "\nВведите данные для велосипеда" << std::endl;
    std::cin >> bicycle;
    std::cout << "\nВведите данные для повозки" << std::endl;
    std::cin >> cart;

    std::cout << "\n=== Автомобиль ===" << std::endl;
    car.print_header();
    car.print_table();
    std::cout << "\n=== Велосипед ===" << std::endl;
    bicycle.print_header();
    bicycle.print_table();
    std::cout << "\n=== Повозка ===" << std::endl;
    cart.print_header();
    cart.print_table();

    int passengers;
    double cargoWeight;
    std::cout << "\nВведите количество пассажиров для расчёта: ";
    std::cin >> passengers;
    std::cout << "Введите массу груза (кг) для расчёта: ";
    std::cin >> cargoWeight;

    auto show_results = [&](const std::string& title, TransportVehicle& vehicle)
    {
        std::cout << title << " - время: " << vehicle.time_in_path()
                  << " ч, стоимость пассажиров: " << vehicle.cost_passengers(passengers)
                  << " руб, стоимость груза: " << vehicle.cost_cargo(cargoWeight) << " руб" << std::endl;
    };

    std::cout << "\n=== Расчёт перевозок ===" << std::endl;
    show_results("Автомобиль", car);
    show_results("Велосипед", bicycle);
    show_results("Повозка", cart);

    std::cout << "\n=== Меню автомобиля ===" << std::endl;
    menu_car(car);
    std::cout << "\n=== Меню велосипеда ===" << std::endl;
    menu_bicycle(bicycle);
    std::cout << "\n=== Меню повозки ===" << std::endl;
    menu_cart(cart);

    return 0;
}
