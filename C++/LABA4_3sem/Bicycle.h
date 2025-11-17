#pragma once
#include "TransportVehicle.h"

class Bicycle : public TransportVehicle
{
public:
    Bicycle();
    Bicycle(const std::string& Name,
            double Distance,
            double PassengerRate,
            double CargoRate,
            double Speed);
    Bicycle(const Bicycle& other);
    ~Bicycle() override;

    virtual void print_header() const override;
    virtual void print_table() const override;
    virtual void menu() const override;

    friend std::istream& operator>>(std::istream& is, Bicycle& ob);
    friend std::ostream& operator<<(std::ostream& os, Bicycle& ob);
    Bicycle& operator=(const Bicycle& other);
};
