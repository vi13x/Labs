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
              << std::setw(17) << "Повозка"        << "| "
              << std::setw(20) << name             << "| "
              << std::setw(12) << distance         << "| "
              << std::setw(12) << speed            << "| "
              << std::setw(18) << passengerRatePerKm << "| "
              << std::setw(18) << cargoRatePerKmPerKg << "| "
              << std::setw(12) << time_in_path()   << "| " << std::endl;
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