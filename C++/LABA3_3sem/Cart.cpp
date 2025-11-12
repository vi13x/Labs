#include "Cart.h"
#include <iostream>
#include <iomanip>

Cart::Cart() = default;

Cart::Cart(const std::string &name,
           double distanceKm,
           double speedKmh,
           double passengerRatePerKm,
           double cargoRatePerKmPerKg)
        : TransportVehicle(name, distanceKm, speedKmh, passengerRatePerKm, cargoRatePerKmPerKg) {}

Cart& Cart::operator=(const Cart& other) {
    if (this != &other) {
        TransportVehicle::operator=(other);
    }
    return *this;
}

TransportVehicle* Cart::clone() const {
    return new Cart(*this);
}

std::ostream& operator<<(std::ostream& os, const Cart& cart) {
    os << cart.type_name() << " - " << cart.get_name();
    return os;
}

std::istream& operator>>(std::istream& is, Cart& cart) {
    cart.input_info();
    return is;
}

std::string Cart::type_name() const {
    return "Cart";
}

void Cart::input_info() {
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