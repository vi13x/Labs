#pragma once

#include "Passenger_carrier.h"

class Airplane : public Passenger_carrier {
private:
    int collections;             // Дополнительные сборы в аэропорту
    int passenger_capacity;      // Вместимость пассажиров
    double cargo_capacity;       // Грузоподъёмность

public:
    Airplane();
    Airplane(int Collections,
             int PassengerCapacity,
             double CargoCapacity,
             const std::string& Name,
             double Distance,
             double Money_km,
             double Speed);
    Airplane(const Airplane& other);
    ~Airplane();

    double time_in_path() override;
    double cost_path() override;
    void menu() override;

    int GetCollections();
    int GetPassengerCapacity();
    double GetCargoCapacity();

    void SetCollections(int Collections);
    void SetPassengerCapacity(int PassengerCapacity);
    void SetCargoCapacity(double CargoCapacity);

    friend std::istream& operator>>(std::istream& is, Airplane& ob);
    friend std::ostream& operator<<(std::ostream& out, Airplane& obj);
    Airplane& operator=(const Airplane& other);

    void print_header() const override;
    void print_table() const override;
};
