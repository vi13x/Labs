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
    ~Bicycle();

    std::string vehicle_type() const override;
    virtual void print_header() const override;
    virtual void print_separator() const override;
    virtual void menu() const override;

    // Уникальные методы для велосипеда
    int get_gears() const;                              // Получить количество передач
    void set_gears(int Gears);                          // Установить количество передач
    std::string get_bicycle_type() const;                // Получить тип велосипеда
    void set_bicycle_type(const std::string& Type);     // Установить тип велосипеда
    bool can_climb_hill(double gradient) const;         // Может ли подняться в гору (градиент в %)
    double calculate_effort_coefficient() const;        // Коэффициент усилия (зависит от передач)

    friend std::istream& operator>>(std::istream& is, Bicycle& ob);
    friend std::ostream& operator<<(std::ostream& os, Bicycle& ob);
    Bicycle& operator=(const Bicycle& other);
};