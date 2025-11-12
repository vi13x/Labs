#pragma once

#include "TransportVehicle.h"

class Bicycle : public TransportVehicle {
public:
    Bicycle(const std::string &name = "",
            double distanceKm = 0,
            double speedKmh = 0,
            double passengerRatePerKm = 0,
            double cargoRatePerKmPerKg = 0);

    TransportVehicle* clone() const override;
    std::string type_name() const override;

    void input_info() override;
    void printHeader() override;
    void printTable() override;
    void display(int index = 0) override;

    // УНИКАЛЬНЫЙ оператор присваивания для Bicycle
    Bicycle& operator=(const Bicycle& other);

    // УНИКАЛЬНЫЕ перегрузки ввода/вывода для Bicycle
    friend std::ostream& operator<<(std::ostream& os, const Bicycle& bicycle);
    friend std::istream& operator>>(std::istream& is, Bicycle& bicycle);
};
