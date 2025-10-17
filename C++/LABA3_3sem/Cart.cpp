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
    TransportVehicle::input_info();
}

void Cart::printHeader() {
    TransportVehicle::printHeader();
}

void Cart::printTable() {
    TransportVehicle::printTable();
}
