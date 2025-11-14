#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <locale>
#include <string>

class Passenger_carrier {
private:
    std::string name;     // Название транспорта
    double distance;      // Расстояние перевозки, км
    double money_km;      // Стоимость за километр, руб
    double speed;         // Скорость транспорта, км/ч

public:
    Passenger_carrier();
    Passenger_carrier(const std::string& Name,
                      double Distance,
                      double Money_km,
                      double Speed);
    Passenger_carrier(const Passenger_carrier& other);
    virtual ~Passenger_carrier();

    virtual void menu();
    virtual double time_in_path();
    virtual double cost_path();

    std::string GetName();
    double GetDistance();
    double GetMoney_km();
    double GetSpeed();

    void SetName(const std::string& Name);
    void SetDistance(double Distance);
    void SetMoney_km(double Money_km);
    void SetSpeed(double Speed);

    friend std::istream& operator>>(std::istream& is, Passenger_carrier& ob);
    friend std::ostream& operator<<(std::ostream& out, Passenger_carrier& obj);
    Passenger_carrier& operator=(const Passenger_carrier& other);

    virtual void print_header() const;
    virtual void print_table() const;
};
