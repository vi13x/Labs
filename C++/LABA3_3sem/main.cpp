#include <array>
#include <clocale>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

#include "Bicycle.h"
#include "Car.h"
#include "Cart.h"

namespace
{
constexpr std::size_t kCarCount = 2;
constexpr std::size_t kCartCount = 2;
constexpr std::size_t kBicycleCount = 2;

void clear_stream()
{
    if (!std::cin)
    {
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void menu_transport(TransportVehicle& vehicle)
{
    while (true)
    {
        vehicle.menu();
        int choice = 0;
        if (!(std::cin >> choice))
        {
            std::cout << "Ошибка ввода!" << std::endl;
            clear_stream();
            continue;
        }
        clear_stream();

        switch (choice)
        {
        case 0:
            return;
        case 1:
            std::cout << std::endl << "Объект" << std::endl;
            vehicle.print_header();
            std::cout << vehicle << std::endl << std::endl;
            break;
        case 2:
        {
            std::string buffer;
            std::cout << "Введите новое название: ";
            std::getline(std::cin, buffer);
            if (!buffer.empty())
            {
                vehicle.SetName(buffer);
            }
            else
            {
                std::cout << "Название не может быть пустым!" << std::endl;
            }
            std::cout << std::endl;
            break;
        }
        case 3:
        {
            double value = 0.0;
            std::cout << "Введите новое расстояние: ";
            if (std::cin >> value)
            {
                vehicle.SetDistance(value);
            }
            else
            {
                std::cout << "Ошибка ввода!" << std::endl;
            }
            clear_stream();
            std::cout << std::endl;
            break;
        }
        case 4:
        {
            double value = 0.0;
            std::cout << "Введите тариф для пассажиров: ";
            if (std::cin >> value)
            {
                vehicle.SetPassengerRate(value);
            }
            else
            {
                std::cout << "Ошибка ввода!" << std::endl;
            }
            clear_stream();
            std::cout << std::endl;
            break;
        }
        case 5:
        {
            double value = 0.0;
            std::cout << "Введите тариф для груза: ";
            if (std::cin >> value)
            {
                vehicle.SetCargoRate(value);
            }
            else
            {
                std::cout << "Ошибка ввода!" << std::endl;
            }
            clear_stream();
            std::cout << std::endl;
            break;
        }
        case 6:
        {
            double value = 0.0;
            std::cout << "Введите скорость: ";
            if (std::cin >> value)
            {
                vehicle.SetSpeed(value);
            }
            else
            {
                std::cout << "Ошибка ввода!" << std::endl;
            }
            clear_stream();
            std::cout << std::endl;
            break;
        }
        case 7:
            std::cout << "Название: " << vehicle.GetName() << std::endl << std::endl;
            break;
        case 8:
            std::cout << "Расстояние: " << vehicle.GetDistance() << std::endl << std::endl;
            break;
        case 9:
            std::cout << "Скорость: " << vehicle.GetSpeed() << std::endl << std::endl;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        {
            Car* car = dynamic_cast<Car*>(&vehicle);
            if (!car)
            {
                std::cout << "Пункт доступен только для автомобиля." << std::endl << std::endl;
                break;
            }
            if (choice == 10)
            {
                double value = 0.0;
                std::cout << "Введите стоимость топлива: ";
                if (std::cin >> value)
                {
                    car->SetFuelPrice(value);
                }
                else
                {
                    std::cout << "Ошибка ввода!" << std::endl;
                }
                clear_stream();
            }
            else if (choice == 11)
            {
                std::cout << "Стоимость топлива: " << car->GetFuelPrice() << std::endl;
            }
            else if (choice == 12)
            {
                int value = 0;
                std::cout << "Введите пассажирскую вместимость: ";
                if (std::cin >> value)
                {
                    car->SetPassengerCapacity(value);
                }
                else
                {
                    std::cout << "Ошибка ввода!" << std::endl;
                }
                clear_stream();
            }
            else if (choice == 13)
            {
                std::cout << "Пассажирская вместимость: " << car->GetPassengerCapacity() << std::endl;
            }
            else if (choice == 14)
            {
                double value = 0.0;
                std::cout << "Введите объём багажника: ";
                if (std::cin >> value)
                {
                    car->SetTrunkVolume(value);
                }
                else
                {
                    std::cout << "Ошибка ввода!" << std::endl;
                }
                clear_stream();
            }
            else if (choice == 15)
            {
                std::cout << "Объём багажника: " << car->GetTrunkVolume() << std::endl;
            }
            std::cout << std::endl;
            break;
        }
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        {
            Cart* cart = dynamic_cast<Cart*>(&vehicle);
            if (!cart)
            {
                std::cout << "Пункт доступен только для повозки." << std::endl << std::endl;
                break;
            }
            if (choice == 16)
            {
                int value = 0;
                std::cout << "Введите количество лошадей: ";
                if (std::cin >> value)
                {
                    cart->SetHorseCount(value);
                }
                else
                {
                    std::cout << "Ошибка ввода!" << std::endl;
                }
                clear_stream();
            }
            else if (choice == 17)
            {
                std::cout << "Количество лошадей: " << cart->GetHorseCount() << std::endl;
            }
            else if (choice == 18)
            {
                double value = 0.0;
                std::cout << "Введите время отдыха: ";
                if (std::cin >> value)
                {
                    cart->SetRestTime(value);
                }
                else
                {
                    std::cout << "Ошибка ввода!" << std::endl;
                }
                clear_stream();
            }
            else if (choice == 19)
            {
                std::cout << "Время отдыха: " << cart->GetRestTime() << std::endl;
            }
            else if (choice == 20)
            {
                double value = 0.0;
                std::cout << "Введите грузоподъёмность: ";
                if (std::cin >> value)
                {
                    cart->SetMaxPayload(value);
                }
                else
                {
                    std::cout << "Ошибка ввода!" << std::endl;
                }
                clear_stream();
            }
            else if (choice == 21)
            {
                std::cout << "Грузоподъёмность: " << cart->GetMaxPayload() << std::endl;
            }
            std::cout << std::endl;
            break;
        }
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        {
            Bicycle* bicycle = dynamic_cast<Bicycle*>(&vehicle);
            if (!bicycle)
            {
                std::cout << "Пункт доступен только для велосипеда." << std::endl << std::endl;
                break;
            }
            if (choice == 22)
            {
                int value = 0;
                std::cout << "Введите количество передач: ";
                if (std::cin >> value)
                {
                    bicycle->SetGearCount(value);
                }
                else
                {
                    std::cout << "Ошибка ввода!" << std::endl;
                }
                clear_stream();
            }
            else if (choice == 23)
            {
                std::cout << "Количество передач: " << bicycle->GetGearCount() << std::endl;
            }
            else if (choice == 24)
            {
                int flag = 0;
                std::cout << "Есть багажник? (1 - да, 0 - нет): ";
                if (std::cin >> flag)
                {
                    bicycle->SetHasCargoRack(flag != 0);
                }
                else
                {
                    std::cout << "Ошибка ввода!" << std::endl;
                }
                clear_stream();
            }
            else if (choice == 25)
            {
                std::cout << "Багажник: " << (bicycle->GetHasCargoRack() ? "есть" : "нет") << std::endl;
            }
            else if (choice == 26)
            {
                double value = 0.0;
                std::cout << "Введите максимальный груз: ";
                if (std::cin >> value)
                {
                    bicycle->SetMaxCargo(value);
                }
                else
                {
                    std::cout << "Ошибка ввода!" << std::endl;
                }
                clear_stream();
            }
            else if (choice == 27)
            {
                std::cout << "Максимальный груз: " << bicycle->GetMaxCargo() << std::endl;
            }
            std::cout << std::endl;
            break;
        }
        default:
            std::cout << "Нет такого пункта." << std::endl << std::endl;
            break;
        }
    }
}
} // namespace

int main()
{
    std::setlocale(LC_ALL, "rus");
#ifdef _WIN32
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
#endif

    std::array<Car, kCarCount> cars;
    std::array<Cart, kCartCount> carts;
    std::array<Bicycle, kBicycleCount> bicycles;

    for (std::size_t i = 0; i < cars.size(); ++i)
    {
        std::cout << "Введите данные автомобиля " << (i + 1) << ":" << std::endl;
        std::cin >> cars[i];
        std::cout << std::endl;
    }

    for (std::size_t i = 0; i < carts.size(); ++i)
    {
        std::cout << "Введите данные повозки " << (i + 1) << ":" << std::endl;
        std::cin >> carts[i];
        std::cout << std::endl;
    }

    for (std::size_t i = 0; i < bicycles.size(); ++i)
    {
        std::cout << "Введите данные велосипеда " << (i + 1) << ":" << std::endl;
        std::cin >> bicycles[i];
        std::cout << std::endl;
    }

    std::cout << std::setw(70) << "=== Автомобили ===" << std::endl;
    cars.front().print_header();
    for (const auto& car : cars)
    {
        std::cout << car << std::endl;
    }
    std::cout << std::endl;

    std::cout << std::setw(70) << "=== Повозки ===" << std::endl;
    carts.front().print_header();
    for (const auto& cart : carts)
    {
        std::cout << cart << std::endl;
    }
    std::cout << std::endl;

    std::cout << std::setw(70) << "=== Велосипеды ===" << std::endl;
    bicycles.front().print_header();
    for (const auto& bicycle : bicycles)
    {
        std::cout << bicycle << std::endl;
    }
    std::cout << std::endl;

    std::cout << "=== Расчёт перевозок ===" << std::endl;
    for (std::size_t i = 0; i < cars.size(); ++i)
    {
        std::cout << "Авто " << (i + 1) << " - время: " << cars[i].time_in_path()
                  << " ч, стоимость (1 пассажир): " << cars[i].cost_passengers(1) << " руб" << std::endl;
    }
    for (std::size_t i = 0; i < carts.size(); ++i)
    {
        std::cout << "Повозка " << (i + 1) << " - время: " << carts[i].time_in_path()
                  << " ч, перевозка 50 кг: " << carts[i].cost_cargo(50) << " руб" << std::endl;
    }
    for (std::size_t i = 0; i < bicycles.size(); ++i)
    {
        std::cout << "Велосипед " << (i + 1) << " - время: " << bicycles[i].time_in_path()
                  << " ч, перевозка 5 кг: " << bicycles[i].cost_cargo(5) << " руб" << std::endl;
    }

    std::cout << std::endl << "=== Меню работы с объектом ===" << std::endl;
    std::cout << "Выберите тип (1 - авто, 2 - повозка, 3 - велосипед): ";
    int typeChoice = 0;
    if (!(std::cin >> typeChoice))
    {
        std::cout << "Некорректный ввод." << std::endl;
        return 0;
    }
    std::cout << "Введите номер объекта (с 1): ";
    std::size_t index = 0;
    if (!(std::cin >> index) || index == 0)
    {
        std::cout << "Некорректный индекс." << std::endl;
        return 0;
    }
    clear_stream();

    TransportVehicle* selected = nullptr;
    switch (typeChoice)
    {
    case 1:
        if (index <= cars.size())
        {
            selected = &cars[index - 1];
        }
        break;
    case 2:
        if (index <= carts.size())
        {
            selected = &carts[index - 1];
        }
        break;
    case 3:
        if (index <= bicycles.size())
        {
            selected = &bicycles[index - 1];
        }
        break;
    default:
        break;
    }

    if (!selected)
    {
        std::cout << "Объект не найден." << std::endl;
        return 0;
    }

    menu_transport(*selected);
    return 0;
}
