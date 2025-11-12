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
    std::cout << "[Bicycle] Input data:\n";
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

// Уникальный оператор присваивания
Bicycle& Bicycle::operator=(const Bicycle& other) {
    if (this != &other) {
        this->name                = other.name;
        this->distanceKm          = other.distanceKm;
        this->speedKmh            = other.speedKmh;
        this->passengerRatePerKm  = other.passengerRatePerKm;
        this->cargoRatePerKmPerKg = other.cargoRatePerKmPerKg;
    }
    return *this;
}

// Уникальный вывод
std::ostream& operator<<(std::ostream& os, const Bicycle& bicycle) {
    os << "[Bicycle object] ";
    os << static_cast<const TransportVehicle&>(bicycle);
    return os;
}

// Уникальный ввод
std::istream& operator>>(std::istream& is, Bicycle& bicycle) {
    std::cout << ">>> Enter data for Bicycle <<<\n";
    bicycle.input_info();
    return is;
}
