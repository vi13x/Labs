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

void Car::print_header() const
{
    TransportVehicle::print_header();
}

void Car::print_table() const
{
    std::cout << std::left
              << std::setw(15) << "Автомобиль"  << "| "
              << std::setw(15) << name          << "| "
              << std::setw(10) << distance      << "| "
              << std::setw(10) << speed         << "| "
              << std::setw(15) << passengerRatePerKm << "| "
              << std::setw(15) << cargoRatePerKmPerKg << "| "
              << std::setw(10) << time_in_path() << "| " << std::endl;
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
    os << static_cast<TransportVehicle&>(ob);
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
