#include "TransportVehicle.h"
#include <limits>

TransportVehicle::TransportVehicle()
{
    name = "Не задано";
    distance = 0.0;
    passengerRatePerKm = 0.0;
    cargoRatePerKmPerKg = 0.0;
    speed = 0.0;
}

TransportVehicle::TransportVehicle(const std::string& Name,
                                   double Distance,
                                   double PassengerRate,
                                   double CargoRate,
                                   double Speed)
{
    name = Name;
    distance = Distance;
    passengerRatePerKm = PassengerRate;
    cargoRatePerKmPerKg = CargoRate;
    speed = Speed;
}

TransportVehicle::TransportVehicle(const TransportVehicle& other)
{
    name = other.name;
    distance = other.distance;
    passengerRatePerKm = other.passengerRatePerKm;
    cargoRatePerKmPerKg = other.cargoRatePerKmPerKg;
    speed = other.speed;
}

TransportVehicle::~TransportVehicle() = default;

double TransportVehicle::time_in_path() const
{
    if (speed <= 0.0) return 0.0;
    return distance / speed;
}

double TransportVehicle::cost_passengers(int passengers) const
{
    if (passengers <= 0) return 0.0;
    return distance * passengerRatePerKm * passengers;
}

double TransportVehicle::cost_cargo(double weightKg) const
{
    if (weightKg <= 0.0) return 0.0;
    return distance * cargoRatePerKmPerKg * weightKg;
}

void TransportVehicle::print_header() const
{
    std::cout << std::left
              << std::setw(15) << "Тип"         << "| "
              << std::setw(15) << "Название"    << "| "
              << std::setw(10) << "Дистанция"   << "| "
              << std::setw(10) << "Скорость"    << "| "
              << std::setw(15) << "Цена/км пасс" << "| "
              << std::setw(15) << "Цена/км кг"  << "| "
              << std::setw(10) << "Время"       << "| " << std::endl;
}

void TransportVehicle::print_table() const
{
    std::cout << std::left
              << std::setw(15) << "Транспорт"   << "| "
              << std::setw(15) << name          << "| "
              << std::setw(10) << distance      << "| "
              << std::setw(10) << speed         << "| "
              << std::setw(15) << passengerRatePerKm << "| "
              << std::setw(15) << cargoRatePerKmPerKg << "| "
              << std::setw(10) << time_in_path() << "| " << std::endl;
}

void TransportVehicle::menu() const
{
    std::cout << "\n0. Выход\n";
    std::cout << "1. Показать объект\n";
    std::cout << "2. Изменить название\n";
    std::cout << "3. Изменить расстояние\n";
    std::cout << "4. Изменить цену за км (пассажиры)\n";
    std::cout << "5. Изменить цену за км (груз)\n";
    std::cout << "6. Изменить скорость\n";
    std::cout << "7. Получить название\n";
    std::cout << "8. Получить расстояние\n";
    std::cout << "9. Получить цену за км (пассажиры)\n";
    std::cout << "10. Получить цену за км (груз)\n";
    std::cout << "11. Получить скорость\n";
    std::cout << "12. Посчитать стоимость перевозки пассажиров\n";
    std::cout << "13. Посчитать стоимость перевозки груза\n";
    std::cout << "Выбор: ";
}

// ===== Геттеры =====
std::string TransportVehicle::GetName() const            { return name; }
double TransportVehicle::GetDistance() const             { return distance; }
double TransportVehicle::GetPassengerRate() const        { return passengerRatePerKm; }
double TransportVehicle::GetCargoRate() const            { return cargoRatePerKmPerKg; }
double TransportVehicle::GetSpeed() const                { return speed; }

// ===== Сеттеры =====
void TransportVehicle::SetName(const std::string& Name)  { name = Name; }

void TransportVehicle::SetDistance(double Distance)
{
    if (Distance >= 0)
        distance = Distance;
    else
        std::cout << "Ошибка: расстояние не может быть отрицательным!\n";
}

void TransportVehicle::SetPassengerRate(double Rate)
{
    if (Rate >= 0)
        passengerRatePerKm = Rate;
    else
        std::cout << "Ошибка: цена не может быть отрицательной!\n";
}

void TransportVehicle::SetCargoRate(double Rate)
{
    if (Rate >= 0)
        cargoRatePerKmPerKg = Rate;
    else
        std::cout << "Ошибка: цена не может быть отрицательной!\n";
}

void TransportVehicle::SetSpeed(double Speed)
{
    if (Speed > 0)
        speed = Speed;
    else
        std::cout << "Ошибка: скорость должна быть > 0!\n";
}

// ===== Операторы =====
std::istream& operator>>(std::istream& is, TransportVehicle& ob)
{
    std::cout << "Введите название: ";
    std::getline(is >> std::ws, ob.name);

    std::cout << "Введите расстояние (км): ";
    is >> ob.distance;

    std::cout << "Введите цену за км (пассажиры): ";
    is >> ob.passengerRatePerKm;

    std::cout << "Введите цену за км (1 кг груза): ";
    is >> ob.cargoRatePerKmPerKg;

    std::cout << "Введите скорость (км/ч): ";
    is >> ob.speed;

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, TransportVehicle& ob)
{
    os << std::left
       << std::setw(15) << "Транспорт"    << "| "
       << std::setw(15) << ob.name        << "| "
       << std::setw(10) << ob.distance    << "| "
       << std::setw(10) << ob.speed       << "| "
       << std::setw(15) << ob.passengerRatePerKm << "| "
       << std::setw(15) << ob.cargoRatePerKmPerKg << "| "
       << std::setw(10) << ob.time_in_path() << "| ";
    return os;
}

TransportVehicle& TransportVehicle::operator=(const TransportVehicle& other)
{
    if (this != &other)
    {
        name = other.name;
        distance = other.distance;
        passengerRatePerKm = other.passengerRatePerKm;
        cargoRatePerKmPerKg = other.cargoRatePerKmPerKg;
        speed = other.speed;
    }
    return *this;
}
