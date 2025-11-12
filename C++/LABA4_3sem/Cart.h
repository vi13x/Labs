#pragma once

#include "TransportVehicle.h"

class Cart : public TransportVehicle {
public:
    Cart(const std::string &name = "",
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

    // Уникальный оператор присваивания
    Cart& operator=(const Cart& other);

    // Уникальные перегрузки ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Cart& cart);
    friend std::istream& operator>>(std::istream& is, Cart& cart);
};
