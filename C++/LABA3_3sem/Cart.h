#pragma once

#include "TransportVehicle.h"

class Cart : public TransportVehicle {
public:
    Cart();
    Cart(const std::string &name,
         double distanceKm,
         double speedKmh,
         double passengerRatePerKm,
         double cargoRatePerKmPerKg);

    Cart& operator=(const Cart& other);

    // I/O operators
    friend std::ostream& operator<<(std::ostream& os, const Cart& cart);
    friend std::istream& operator>>(std::istream& is, Cart& cart);

    TransportVehicle* clone() const override;
    std::string type_name() const override;
    
    void input_info() override;
    void printHeader() override;
    void printTable() override;
    void display(int index = 0) override;
};


