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
    std::cout << "[Car] Input data:\n";
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

// ===== Уникальный оператор присваивания =====
Car& Car::operator=(const Car& other) {
    if (this != &other) {
        // копируем базовую часть
        this->name                = other.name;
        this->distanceKm          = other.distanceKm;
        this->speedKmh            = other.speedKmh;
        this->passengerRatePerKm  = other.passengerRatePerKm;
        this->cargoRatePerKmPerKg = other.cargoRatePerKmPerKg;
        // если будут свои поля у Car — копировать их здесь
    }
    return *this;
}

// ===== Уникальная перегрузка вывода для Car =====
std::ostream& operator<<(std::ostream& os, const Car& car) {
    os << "[Car object] ";
    // используем базовый оператор вывода для общей части
    os << static_cast<const TransportVehicle&>(car);
    return os;
}

// ===== Уникальная перегрузка ввода для Car =====
std::istream& operator>>(std::istream& is, Car& car) {
    std::cout << ">>> Enter data for Car <<<\n";
    car.input_info(); // использует переопределённый input_info()
    return is;
}
