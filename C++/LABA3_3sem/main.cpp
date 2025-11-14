#include <array>
#include <clocale>
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

enum class VehicleType
{
    None,
    Car,
    Cart,
    Bicycle
};

struct Selection
{
    VehicleType type{ VehicleType::None };
    std::size_t index{ 0 };
};

void print_menu()
{
    std::cout << "\n===== Меню управления =====" << std::endl;
    std::cout << "0  - выход" << std::endl;
    std::cout << "1  - выбрать объект" << std::endl;
    std::cout << "2  - показать текущий объект" << std::endl;
    std::cout << "3  - изменить название" << std::endl;
    std::cout << "4  - изменить расстояние" << std::endl;
    std::cout << "5  - изменить тариф для пассажиров" << std::endl;
    std::cout << "6  - изменить тариф для груза" << std::endl;
    std::cout << "7  - изменить скорость" << std::endl;
    std::cout << "8  - расчёт перевозки пассажиров" << std::endl;
    std::cout << "9  - расчёт перевозки груза" << std::endl;
    std::cout << "10 - изменить стоимость топлива (авто)" << std::endl;
    std::cout << "11 - показать стоимость топлива (авто)" << std::endl;
    std::cout << "12 - изменить пассажирскую вместимость (авто)" << std::endl;
    std::cout << "13 - показать пассажирскую вместимость (авто)" << std::endl;
    std::cout << "14 - изменить объём багажника (авто)" << std::endl;
    std::cout << "15 - показать объём багажника (авто)" << std::endl;
    std::cout << "16 - изменить число лошадей (повозка)" << std::endl;
    std::cout << "17 - показать число лошадей (повозка)" << std::endl;
    std::cout << "18 - изменить время отдыха (повозка)" << std::endl;
    std::cout << "19 - показать время отдыха (повозка)" << std::endl;
    std::cout << "20 - изменить грузоподъёмность (повозка)" << std::endl;
    std::cout << "21 - показать грузоподъёмность (повозка)" << std::endl;
    std::cout << "22 - изменить количество передач (велосипед)" << std::endl;
    std::cout << "23 - показать количество передач (велосипед)" << std::endl;
    std::cout << "24 - изменить наличие багажника (велосипед)" << std::endl;
    std::cout << "25 - показать наличие багажника (велосипед)" << std::endl;
    std::cout << "26 - изменить максимальный груз (велосипед)" << std::endl;
    std::cout << "27 - показать максимальный груз (велосипед)" << std::endl;
}

TransportVehicle* get_selected_vehicle(const Selection& selection,
                                       std::array<Car, kCarCount>& cars,
                                       std::array<Cart, kCartCount>& carts,
                                       std::array<Bicycle, kBicycleCount>& bicycles)
{
    switch (selection.type)
    {
    case VehicleType::Car:
        if (selection.index < cars.size())
        {
            return &cars[selection.index];
        }
        break;
    case VehicleType::Cart:
        if (selection.index < carts.size())
        {
            return &carts[selection.index];
        }
        break;
    case VehicleType::Bicycle:
        if (selection.index < bicycles.size())
        {
            return &bicycles[selection.index];
        }
        break;
    case VehicleType::None:
    default:
        break;
    }
    return nullptr;
}

TransportVehicle* require_selection(const Selection& selection,
                                    std::array<Car, kCarCount>& cars,
                                    std::array<Cart, kCartCount>& carts,
                                    std::array<Bicycle, kBicycleCount>& bicycles)
{
    TransportVehicle* vehicle = get_selected_vehicle(selection, cars, carts, bicycles);
    if (!vehicle)
    {
        std::cout << "Сначала выберите объект (пункт 1)." << std::endl;
    }
    return vehicle;
}

std::string type_label(VehicleType type)
{
    switch (type)
    {
    case VehicleType::Car:
        return "автомобиль";
    case VehicleType::Cart:
        return "повозка";
    case VehicleType::Bicycle:
        return "велосипед";
    case VehicleType::None:
    default:
        return "не выбран";
    }
}

} // namespace

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
#endif
    std::setlocale(LC_ALL, "rus");

    std::array<Car, kCarCount> cars;
    std::array<Cart, kCartCount> carts;
    std::array<Bicycle, kBicycleCount> bicycles;

    for (std::size_t i = 0; i < cars.size(); ++i)
    {
        std::cout << "\nВведите данные для автомобиля #" << (i + 1) << std::endl;
        std::cin >> cars[i];
    }

    for (std::size_t i = 0; i < carts.size(); ++i)
    {
        std::cout << "\nВведите данные для повозки #" << (i + 1) << std::endl;
        std::cin >> carts[i];
    }

    for (std::size_t i = 0; i < bicycles.size(); ++i)
    {
        std::cout << "\nВведите данные для велосипеда #" << (i + 1) << std::endl;
        std::cin >> bicycles[i];
    }

    Selection selection;

    while (true)
    {
        print_menu();
        std::cout << "Выберите пункт: ";
        int choice = 0;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода!" << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0)
        {
            break;
        }

        switch (choice)
        {
        case 1:
        {
            std::cout << "Выберите тип (1 - авто, 2 - повозка, 3 - велосипед): ";
            int typeChoice = 0;
            if (!(std::cin >> typeChoice))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода!" << std::endl;
                break;
            }
            VehicleType newType = VehicleType::None;
            std::size_t available = 0;
            switch (typeChoice)
            {
            case 1:
                newType = VehicleType::Car;
                available = cars.size();
                break;
            case 2:
                newType = VehicleType::Cart;
                available = carts.size();
                break;
            case 3:
                newType = VehicleType::Bicycle;
                available = bicycles.size();
                break;
            default:
                std::cout << "Неизвестный тип!" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            if (newType == VehicleType::None)
            {
                break;
            }
            std::cout << "Введите номер объекта (1-" << available << "): ";
            std::size_t number = 0;
            if (!(std::cin >> number) || number == 0 || number > available)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный номер!" << std::endl;
                break;
            }
            selection.type = newType;
            selection.index = number - 1;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Выбран " << type_label(selection.type) << " #" << number << std::endl;
            break;
        }
        case 2:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            if (vehicle)
            {
                std::cout << *vehicle << std::endl;
            }
            break;
        }
        case 3:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            if (!vehicle)
            {
                break;
            }
            std::string newName;
            std::cout << "Введите новое название: ";
            std::getline(std::cin, newName);
            vehicle->SetName(newName);
            break;
        }
        case 4:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            if (!vehicle)
            {
                break;
            }
            double value = 0.0;
            std::cout << "Введите расстояние (км): ";
            if (!(std::cin >> value))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода!" << std::endl;
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            vehicle->SetDistance(value);
            break;
        }
        case 5:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            if (!vehicle)
            {
                break;
            }
            double value = 0.0;
            std::cout << "Введите тариф за км для пассажиров: ";
            if (!(std::cin >> value))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода!" << std::endl;
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            vehicle->SetPassengerRate(value);
            break;
        }
        case 6:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            if (!vehicle)
            {
                break;
            }
            double value = 0.0;
            std::cout << "Введите тариф за км для груза: ";
            if (!(std::cin >> value))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода!" << std::endl;
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            vehicle->SetCargoRate(value);
            break;
        }
        case 7:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            if (!vehicle)
            {
                break;
            }
            double value = 0.0;
            std::cout << "Введите скорость (км/ч): ";
            if (!(std::cin >> value))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода!" << std::endl;
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            vehicle->SetSpeed(value);
            break;
        }
        case 8:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            if (!vehicle)
            {
                break;
            }
            int passengers = 0;
            std::cout << "Введите количество пассажиров: ";
            if (!(std::cin >> passengers))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода!" << std::endl;
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Стоимость: " << vehicle->cost_passengers(passengers)
                      << ", время в пути: " << vehicle->time_in_path() << " ч" << std::endl;
            break;
        }
        case 9:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            if (!vehicle)
            {
                break;
            }
            double cargo = 0.0;
            std::cout << "Введите массу груза (кг): ";
            if (!(std::cin >> cargo))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода!" << std::endl;
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Стоимость: " << vehicle->cost_cargo(cargo)
                      << ", время в пути: " << vehicle->time_in_path() << " ч" << std::endl;
            break;
        }
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            Car* car = dynamic_cast<Car*>(vehicle);
            if (!car)
            {
                break;
            }
            if (choice == 10)
            {
                double price = 0.0;
                std::cout << "Введите стоимость топлива: ";
                if (!(std::cin >> price))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                car->SetFuelPrice(price);
            }
            else if (choice == 11)
            {
                std::cout << "Стоимость топлива: " << car->GetFuelPrice() << std::endl;
            }
            else if (choice == 12)
            {
                int capacity = 0;
                std::cout << "Введите пассажирскую вместимость: ";
                if (!(std::cin >> capacity))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                car->SetPassengerCapacity(capacity);
            }
            else if (choice == 13)
            {
                std::cout << "Пассажирская вместимость: " << car->GetPassengerCapacity() << std::endl;
            }
            else if (choice == 14)
            {
                double volume = 0.0;
                std::cout << "Введите объём багажника (л): ";
                if (!(std::cin >> volume))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                car->SetTrunkVolume(volume);
            }
            else
            {
                std::cout << "Объём багажника: " << car->GetTrunkVolume() << std::endl;
            }
            break;
        }
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            Cart* cart = dynamic_cast<Cart*>(vehicle);
            if (!cart)
            {
                break;
            }
            if (choice == 16)
            {
                int horses = 0;
                std::cout << "Введите количество лошадей: ";
                if (!(std::cin >> horses))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cart->SetHorseCount(horses);
            }
            else if (choice == 17)
            {
                std::cout << "Лошадей: " << cart->GetHorseCount() << std::endl;
            }
            else if (choice == 18)
            {
                double rest = 0.0;
                std::cout << "Введите время отдыха (ч): ";
                if (!(std::cin >> rest))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cart->SetRestTime(rest);
            }
            else if (choice == 19)
            {
                std::cout << "Время отдыха: " << cart->GetRestTime() << " ч" << std::endl;
            }
            else if (choice == 20)
            {
                double payload = 0.0;
                std::cout << "Введите грузоподъёмность (кг): ";
                if (!(std::cin >> payload))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cart->SetMaxPayload(payload);
            }
            else
            {
                std::cout << "Грузоподъёмность: " << cart->GetMaxPayload() << " кг" << std::endl;
            }
            break;
        }
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        {
            TransportVehicle* vehicle = require_selection(selection, cars, carts, bicycles);
            Bicycle* bicycle = dynamic_cast<Bicycle*>(vehicle);
            if (!bicycle)
            {
                break;
            }
            if (choice == 22)
            {
                int gears = 0;
                std::cout << "Введите количество передач: ";
                if (!(std::cin >> gears))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                bicycle->SetGearCount(gears);
            }
            else if (choice == 23)
            {
                std::cout << "Количество передач: " << bicycle->GetGearCount() << std::endl;
            }
            else if (choice == 24)
            {
                int flag = 0;
                std::cout << "Есть багажник? (1 - да, 0 - нет): ";
                if (!(std::cin >> flag))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                bicycle->SetHasCargoRack(flag != 0);
            }
            else if (choice == 25)
            {
                std::cout << "Наличие багажника: " << (bicycle->GetHasCargoRack() ? "да" : "нет") << std::endl;
            }
            else if (choice == 26)
            {
                double payload = 0.0;
                std::cout << "Введите максимальный груз (кг): ";
                if (!(std::cin >> payload))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                bicycle->SetMaxCargo(payload);
            }
            else
            {
                std::cout << "Максимальный груз: " << bicycle->GetMaxCargo() << " кг" << std::endl;
            }
            break;
        }
        default:
            std::cout << "Неизвестный пункт меню!" << std::endl;
            break;
        }
    }

    std::cout << "Выход из программы." << std::endl;
    return 0;
}
