#pragma once

#include "TransportVehicle.h"

class Car : public TransportVehicle
{
private:
    double fuelPrice{};       // Стоимость топлива за поездку
    int passengerCapacity{};  // Максимальное количество пассажиров
    double trunkVolume{};     // Объём багажника (л)

public:
    Car();
    Car(double FuelPrice,
        int PassengerCapacity,
        double TrunkVolume,
        const std::string& Name,
        double Distance,
        double PassengerRate,
        double CargoRate,
        double Speed);
    Car(const Car& other);
    ~Car() override;

    double time_in_path() const override;
    double cost_passengers(int passengers) const override;
    void menu() override;

    double GetFuelPrice() const;
    int GetPassengerCapacity() const;
    double GetTrunkVolume() const;

    void SetFuelPrice(double FuelPrice);
    void SetPassengerCapacity(int PassengerCapacity);
    void SetTrunkVolume(double TrunkVolume);

    friend std::istream& operator>>(std::istream& is, Car& car);
    friend std::ostream& operator<<(std::ostream& os, Car& car);
    Car& operator=(const Car& other);

    void print_header() const override;
    void print_table() const override;
};
