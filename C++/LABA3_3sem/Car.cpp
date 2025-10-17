#include "Car.h"
#include <iostream>
#include <iomanip>

Car::Car(const std::string &name,
         double distanceKm,
         double speedKmh,
         double passengerRatePerKm,
         double cargoRatePerKmPerKg)
        : TransportVehicle(name, distanceKm, speedKmh, passengerRatePerKm, cargoRatePerKmPerKg) {}

TransportVehicle* Car::clone() const {
    return new Car(*this);
}

std::string Car::type_name() const {
    return "Car";
}

void Car::input_info() {
    TransportVehicle::input_info();
}

void Car::printHeader() {
    TransportVehicle::printHeader();
}

void Car::printTable() {
    TransportVehicle::printTable();
}
