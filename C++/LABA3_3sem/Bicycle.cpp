#include "Bicycle.h"
#include <limits>

Bicycle::Bicycle() : TransportVehicle() {}

Bicycle::Bicycle(const std::string& Name,
                 double Distance,
                 double PassengerRate,
                 double CargoRate,
                 double Speed)
        : TransportVehicle(Name, Distance, PassengerRate, CargoRate, Speed) {}

Bicycle::Bicycle(const Bicycle& other) : TransportVehicle(other) {}

Bicycle::~Bicycle() = default;

std::string Bicycle::vehicle_type() const
{
    return "Велосипед";
}

void Bicycle::print_header() const
{
    std::cout << std::left
              << std::setw(13) << "Велосипед"     << "| "
              << std::setw(28) << "Название"       << "| "
              << std::setw(17) << "Дистанция"        << "| "
              << std::setw(12) << "Скорость"          << "| "
              << std::setw(18) << "Цена/км пасс"        << "| "
              << std::setw(18) << "Цена/км кг"          << "| "
              << std::setw(12) << "Время"           << "     | " << std::endl;
}

void Bicycle::menu() const
{
    std::cout << "\n=== МЕНЮ ВЕЛОСИПЕДА ===\n";
    TransportVehicle::menu();
}

std::istream& operator>>(std::istream& is, Bicycle& ob)
{
    is >> static_cast<TransportVehicle&>(ob);
    return is;
}

std::ostream& operator<<(std::ostream& os, Bicycle& ob)
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

Bicycle& Bicycle::operator=(const Bicycle& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
    }
    return *this;
}