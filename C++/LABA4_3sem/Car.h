#pragma once
#include "TransportVehicle.h"

class Car : public TransportVehicle
{
private:
    double fuelConsumption;         // Расход топлива (л/100км)
    std::string fuelType;            // Тип топлива (бензин, дизель, электричество)
    double mileageSinceMaintenance;  // Пробег с последнего ТО (км)

public:
    Car();
    Car(const std::string& Name,
        double Distance,
        double PassengerRate,
        double CargoRate,
        double Speed);
    Car(const Car& other);
    ~Car() override;

    std::string vehicle_type() const override;
    virtual void print_table() const override;
    virtual void print_separator() const override;
    virtual void menu() const override;

    double get_fuel_consumption() const;
    void set_fuel_consumption(double Consumption);
    std::string get_fuel_type() const;
    void set_fuel_type(const std::string& Type);
    double get_mileage_since_maintenance() const;
    void set_mileage_since_maintenance(double Mileage);
    bool needs_maintenance() const;
    double calculate_fuel_cost(double fuelPrice) const;
    void update_mileage(double additionalMileage);

    friend std::istream& operator>>(std::istream& is, Car& ob);
    friend std::ostream& operator<<(std::ostream& os, const Car& ob);
    Car& operator=(const Car& other);
};
