#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

class TransportVehicle {
protected:
    std::string name;           // Название транспортного средства
    double distance{};          // Расстояние перевозки (км)
    double passengerRate{};     // Стоимость за км для пассажиров
    double cargoRate{};         // Стоимость за км для килограмма груза
    double speed{};             // Скорость (км/ч)

public:
    TransportVehicle();
    TransportVehicle(const std::string& Name,
                     double Distance,
                     double PassengerRate,
                     double CargoRate,
                     double Speed);
    TransportVehicle(const TransportVehicle& other);
    virtual ~TransportVehicle();

    virtual void menu();
    virtual double time_in_path() const;              // Расчёт времени в пути
    virtual double cost_passengers(int passengers) const; // Стоимость перевозки пассажиров
    virtual double cost_cargo(double cargoWeight) const;  // Стоимость перевозки груза

    std::string GetName() const;
    double GetDistance() const;
    double GetPassengerRate() const;
    double GetCargoRate() const;
    double GetSpeed() const;

    void SetName(const std::string& Name);
    void SetDistance(double Distance);
    void SetPassengerRate(double Rate);
    void SetCargoRate(double Rate);
    void SetSpeed(double Speed);

    friend std::istream& operator>>(std::istream& is, TransportVehicle& vehicle);
    friend std::ostream& operator<<(std::ostream& os, const TransportVehicle& vehicle);
    TransportVehicle& operator=(const TransportVehicle& other);

    virtual void print_header() const;
    virtual void print_table() const;
};
