#pragma once
#include "TransportVehicle.h"

class Car : public TransportVehicle
{
public:
    Car();
    Car(const std::string& Name,
        double Distance,
        double PassengerRate,
        double CargoRate,
        double Speed);
    Car(const Car& other);
    ~Car() override;

    virtual void print_header() const override;
    virtual void print_table() const override;
    virtual void menu() const override;

    friend std::istream& operator>>(std::istream& is, Car& ob);
    friend std::ostream& operator<<(std::ostream& os, Car& ob);
    Car& operator=(const Car& other);
};
