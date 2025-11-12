#pragma once

#include "TransportVehicle.h"

class Car : public TransportVehicle {
public:
    Car();
    Car(const std::string &name,
        double distanceKm,
        double speedKmh,
        double passengerRatePerKm,
        double cargoRatePerKmPerKg);

    Car& operator=(const Car& other);

    // I/O operators
    friend std::ostream& operator<<(std::ostream& os, const Car& car);
    friend std::istream& operator>>(std::istream& is, Car& car);

    TransportVehicle* clone() const override;
    std::string type_name() const override;
    
    void input_info() override;
    void printHeader() override;
    void printTable() override;
    void display(int index = 0) override;
};


