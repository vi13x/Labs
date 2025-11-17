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

void Bicycle::print_header() const
{
    TransportVehicle::print_header();
}

void Bicycle::print_table() const
{
    std::cout << std::left
              << std::setw(20) << "Велосипед"      << "| "
              << std::setw(20) << name             << "| "
              << std::setw(12) << distance         << "| "
              << std::setw(12) << speed            << "| "
              << std::setw(18) << passengerRatePerKm << "| "
              << std::setw(18) << cargoRatePerKmPerKg << "| "
              << std::setw(12) << time_in_path()   << "| " << std::endl;
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
    os << static_cast<TransportVehicle&>(ob);
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
