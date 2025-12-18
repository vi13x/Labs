#pragma once
#include "TransportVehicle.h"

class Bicycle : public TransportVehicle
{
private:
    int gears;                      // Количество передач
    std::string bicycleType;        // Тип велосипеда (горный, городской, спортивный)

public:
    Bicycle();
    Bicycle(const std::string& Name,
            double Distance,
            double PassengerRate,
            double CargoRate,
            double Speed);
    Bicycle(const Bicycle& other);
    ~Bicycle() override;

    std::string vehicle_type() const override;
    virtual void print_table() const override;
    virtual void print_separator() const override;
    virtual void menu() const override;

    int get_gears() const;
    void set_gears(int Gears);
    std::string get_bicycle_type() const;
    void set_bicycle_type(const std::string& Type);
    bool can_climb_hill(double gradient) const;
    double calculate_effort_coefficient() const;

    friend std::istream& operator>>(std::istream& is, Bicycle& ob);
    friend std::ostream& operator<<(std::ostream& os, const Bicycle& ob);
    Bicycle& operator=(const Bicycle& other);
};
