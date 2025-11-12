#include "Cart.h"
#include <iostream>
#include <iomanip>

Cart::Cart(const std::string &name,
           double distanceKm,
           double speedKmh,
           double passengerRatePerKm,
           double cargoRatePerKmPerKg)
        : TransportVehicle(name, distanceKm, speedKmh, passengerRatePerKm, cargoRatePerKmPerKg) {}

TransportVehicle* Cart::clone() const {
    return new Cart(*this);
}

std::string Cart::type_name() const {
    return "Cart";
}

void Cart::input_info() {
    std::cout << "[Cart] Input data:\n";
    TransportVehicle::input_info();
}

void Cart::printHeader() {
    TransportVehicle::printHeader();
}

void Cart::printTable() {
    TransportVehicle::printTable();
}

void Cart::display(int index) {
    TransportVehicle::display(index);
}

// ===== Уникальный оператор присваивания =====
Cart& Cart::operator=(const Cart& other) {
    if (this != &other) {
        this->name                = other.name;
        this->distanceKm          = other.distanceKm;
        this->speedKmh            = other.speedKmh;
        this->passengerRatePerKm  = other.passengerRatePerKm;
        this->cargoRatePerKmPerKg = other.cargoRatePerKmPerKg;
    }
    return *this;
}

// ===== Уникальная перегрузка вывода =====
std::ostream& operator<<(std::ostream& os, const Cart& cart) {
    os << "[Cart object] ";
    os << static_cast<const TransportVehicle&>(cart);
    return os;
}

// ===== Уникальная перегрузка ввода =====
std::istream& operator>>(std::istream& is, Cart& cart) {
    std::cout << ">>> Enter data for Cart <<<\n";
    cart.input_info();
    return is;
}
