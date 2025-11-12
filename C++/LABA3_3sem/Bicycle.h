#pragma once

#include "TransportVehicle.h"

class Bicycle : public TransportVehicle {
public:
    Bicycle();
    Bicycle(const std::string &name,
            double distanceKm,
            double speedKmh,
            double passengerRatePerKm,
            double cargoRatePerKmPerKg);

    Bicycle& operator=(const Bicycle& other);

    friend std::ostream& operator<<(std::ostream& os, const Bicycle& bicycle);
    friend std::istream& operator>>(std::istream& is, Bicycle& bicycle);

    TransportVehicle* clone() const override;
    std::string type_name() const override;
    
    void input_info() override;
    void printHeader() override;
    void printTable() override;
    void display(int index = 0) override;
};


