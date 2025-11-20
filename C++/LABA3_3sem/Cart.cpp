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

std::string Cart::vehicle_type() const
{
    return "Повозка";
}

void Cart::print_header() const
{
    std::cout << std::left
              << std::setw(13) << "Повозка"        << "| "
              << std::setw(28) << "Название"       << "| "
              << std::setw(17) << "Дистанция"        << "| "
              << std::setw(12) << "Скорость"          << "| "
              << std::setw(18) << "Цена/км пасс"        << "| "
              << std::setw(18) << "Цена/км кг"          << "| "
              << std::setw(12) << "Время"           << "     | " << std::endl;
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

Cart& Cart::operator=(const Cart& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
    }
    return *this;
}