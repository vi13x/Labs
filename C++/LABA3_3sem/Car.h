#pragma once

#include "TransportVehicle.h"

class Car : public TransportVehicle {
public:
    Car(const std::string &name,
        double distanceKm,
        double speedKmh,
        double passengerRatePerKm,
        double cargoRatePerKmPerKg);

    TransportVehicle* clone() const override;
    std::string type_name() const override;
    
    void input_info() override;
    void printHeader() override;
    void printTable() override;
};


