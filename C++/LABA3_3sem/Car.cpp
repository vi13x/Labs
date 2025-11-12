#include "Car.h"
#include <iostream>
#include <iomanip>

Car::Car() = default;

Car::Car(const std::string &name,
         double distanceKm,
         double speedKmh,
         double passengerRatePerKm,
         double cargoRatePerKmPerKg)
        : TransportVehicle(name, distanceKm, speedKmh, passengerRatePerKm, cargoRatePerKmPerKg) {}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        TransportVehicle::operator=(other);
    }
    return *this;
}

TransportVehicle* Car::clone() const {
    return new Car(*this);
}

std::ostream& operator<<(std::ostream& os, const Car& car) {
    os << car.type_name() << " - " << car.get_name();
    return os;
}

std::istream& operator>>(std::istream& is, Car& car) {
    car.input_info();
    return is;
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

void Car::display(int index) {
    TransportVehicle::display(index);
}