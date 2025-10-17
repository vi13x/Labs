#include "Bicycle.h"
#include <iostream>
#include <iomanip>

Bicycle::Bicycle(const std::string &name,
                 double distanceKm,
                 double speedKmh,
                 double passengerRatePerKm,
                 double cargoRatePerKmPerKg)
        : TransportVehicle(name, distanceKm, speedKmh, passengerRatePerKm, cargoRatePerKmPerKg) {}

TransportVehicle* Bicycle::clone() const {
    return new Bicycle(*this);
}

std::string Bicycle::type_name() const {
    return "Bicycle";
}

void Bicycle::input_info() {
    TransportVehicle::input_info();
}

void Bicycle::printHeader() {
    TransportVehicle::printHeader();
}

void Bicycle::printTable() {
    TransportVehicle::printTable();
}
