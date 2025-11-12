#include "Bicycle.h"
#include <iostream>
#include <iomanip>

Bicycle::Bicycle() = default;

Bicycle::Bicycle(const std::string &name,
                 double distanceKm,
                 double speedKmh,
                 double passengerRatePerKm,
                 double cargoRatePerKmPerKg)
        : TransportVehicle(name, distanceKm, speedKmh, passengerRatePerKm, cargoRatePerKmPerKg) {}

Bicycle& Bicycle::operator=(const Bicycle& other) {
    if (this != &other) {
        TransportVehicle::operator=(other);
    }
    return *this;
}

TransportVehicle* Bicycle::clone() const {
    return new Bicycle(*this);
}

std::ostream& operator<<(std::ostream& os, const Bicycle& bicycle) {
    os << bicycle.type_name() << " - " << bicycle.get_name();
    return os;
}

std::istream& operator>>(std::istream& is, Bicycle& bicycle) {
    bicycle.input_info();
    return is;
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

void Bicycle::display(int index) {
    TransportVehicle::display(index);
}