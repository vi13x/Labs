#include "Car.h"
#include <limits>

Car::Car() : TransportVehicle() {}

Car::Car(const std::string& Name,
         double Distance,
         double PassengerRate,
         double CargoRate,
         double Speed)
        : TransportVehicle(Name, Distance, PassengerRate, CargoRate, Speed) {}

Car::Car(const Car& other) : TransportVehicle(other) {}

Car::~Car() = default;

std::string Car::vehicle_type() const
{
    return "Автомобиль";
}

void Car::print_header() const
{
    std::cout << std::left
              << std::setw(13) << "Автомобиль"    << "| "
              << std::setw(28) << "Название"       << "| "
              << std::setw(17) << "Дистанция"        << "| "
              << std::setw(12) << "Скорость"          << "| "
              << std::setw(18) << "Цена/км пасс"        << "| "
              << std::setw(18) << "Цена/км кг"          << "| "
              << std::setw(12) << "Время"           << "     | " << std::endl;
}

void Car::menu() const
{
    std::cout << "\n=== МЕНЮ АВТОМОБИЛЯ ===\n";
    TransportVehicle::menu();
}

std::istream& operator>>(std::istream& is, Car& ob)
{
    is >> static_cast<TransportVehicle&>(ob);
    return is;
}

std::ostream& operator<<(std::ostream& os, Car& ob)
{
    os << std::left
       << std::setw(20) << ob.vehicle_type()   << "| "
       << std::setw(20) << ob.name             << "| "
       << std::setw(12) << ob.distance         << "| "
       << std::setw(12) << ob.speed            << "| "
       << std::setw(18) << ob.passengerRatePerKm << "| "
       << std::setw(18) << ob.cargoRatePerKmPerKg << "| "
       << std::setw(12) << ob.time_in_path()   << "| ";
    return os;
}

Car& Car::operator=(const Car& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
    }
    return *this;
}