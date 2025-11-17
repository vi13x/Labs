#include "Cart.h"
#include <limits>

Cart::Cart() : TransportVehicle() {}

Cart::Cart(const std::string& Name,
           double Distance,
           double PassengerRate,
           double CargoRate,
           double Speed)
        : TransportVehicle(Name, Distance, PassengerRate, CargoRate, Speed) {}

Cart::Cart(const Cart& other) : TransportVehicle(other) {}

Cart::~Cart() = default;

void Cart::print_header() const
{
    TransportVehicle::print_header();
}

void Cart::print_table() const
{
    std::cout << std::left
              << std::setw(15) << "Повозка"     << "| "
              << std::setw(15) << name          << "| "
              << std::setw(10) << distance      << "| "
              << std::setw(10) << speed         << "| "
              << std::setw(15) << passengerRatePerKm << "| "
              << std::setw(15) << cargoRatePerKmPerKg << "| "
              << std::setw(10) << time_in_path() << "| " << std::endl;
}

void Cart::menu() const
{
    std::cout << "\n=== МЕНЮ ПОВОЗКИ ===\n";
    TransportVehicle::menu();
}

std::istream& operator>>(std::istream& is, Cart& ob)
{
    is >> static_cast<TransportVehicle&>(ob);
    return is;
}

std::ostream& operator<<(std::ostream& os, Cart& ob)
{
    os << static_cast<TransportVehicle&>(ob);
    return os;
}

Cart& Cart::operator=(const Cart& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
    }
    return *this;
}
