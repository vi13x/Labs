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
    ~Car();

    std::string vehicle_type() const override;
    virtual void print_header() const override;
    virtual void print_separator() const override;
    virtual void menu() const override;

    double get_fuel_consumption() const;                    // Получить расход топлива
    void set_fuel_consumption(double Consumption);         // Установить расход топлива
    std::string get_fuel_type() const;                      // Получить тип топлива
    void set_fuel_type(const std::string& Type);           // Установить тип топлива
    double get_mileage_since_maintenance() const;          // Получить пробег с последнего ТО
    void set_mileage_since_maintenance(double Mileage);    // Установить пробег с последнего ТО
    bool needs_maintenance() const;                         // Нужно ли ТО (если пробег > 10000 км)
    double calculate_fuel_cost(double fuelPrice) const;     // Рассчитать стоимость топлива для поездки
    void update_mileage(double additionalMileage);         // Обновить пробег после поездки

    friend std::istream& operator>>(std::istream& is, Car& ob);
    friend std::ostream& operator<<(std::ostream& os, Car& ob);
    Car& operator=(const Car& other);
};