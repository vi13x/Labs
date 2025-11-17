#include "Car.h"

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
              << std::setw(20) << "Автомобиль"     << "| "
              << std::setw(20) << name             << "| "
              << std::setw(12) << distance         << "| "
              << std::setw(12) << speed            << "| "
              << std::setw(18) << passengerRatePerKm << "| "
              << std::setw(18) << cargoRatePerKmPerKg << "| "
              << std::setw(12) << time_in_path()   << "| " << std::endl;
}


void Car::menu() const
{
    std::cout << "\n=== МЕНЮ АВТО ===\n";
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
