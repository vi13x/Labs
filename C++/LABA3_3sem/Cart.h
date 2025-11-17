#pragma once
#include "TransportVehicle.h"

class Cart : public TransportVehicle
{
public:
    Cart();
    Cart(const std::string& Name,
         double Distance,
         double PassengerRate,
         double CargoRate,
         double Speed);
    Cart(const Cart& other);
    ~Cart();

    virtual void print_header() const override;
    virtual void print_table() const override;
    virtual void menu() const override;

    friend std::istream& operator>>(std::istream& is, Cart& ob);
    friend std::ostream& operator<<(std::ostream& os, Cart& ob);
    Cart& operator=(const Cart& other);
};
