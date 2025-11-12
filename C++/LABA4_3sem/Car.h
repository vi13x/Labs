#pragma once

#include "TransportVehicle.h"

class Car : public TransportVehicle {
public:
    Car(const std::string &name = "",
        double distanceKm = 0,
        double speedKmh = 0,
        double passengerRatePerKm = 0,
        double cargoRatePerKmPerKg = 0);

    // Полиморфный интерфейс
    TransportVehicle* clone() const override;
    std::string type_name() const override;

    void input_info() override;
    void printHeader() override;
    void printTable() override;
    void display(int index = 0) override;

    // Уникальный оператор присваивания для Car
    Car& operator=(const Car& other);

    // Уникальные перегрузки ввода/вывода для Car
    friend std::ostream& operator<<(std::ostream& os, const Car& car);
    friend std::istream& operator>>(std::istream& is, Car& car);
};
