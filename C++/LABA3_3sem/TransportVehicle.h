#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class TransportVehicle
{
protected:
    std::string name;               // Название
    double distance;                // Расстояние, км
    double passengerRatePerKm;      // Цена за км на 1 пассажира
    double cargoRatePerKmPerKg;     // Цена за км на 1 кг груза
    double speed;                   // Скорость, км/ч

public:
    TransportVehicle();
    TransportVehicle(const std::string& Name,
                     double Distance,
                     double PassengerRate,
                     double CargoRate,
                     double Speed);
    TransportVehicle(const TransportVehicle& other);
    virtual ~TransportVehicle();

    // Виртуальный интерфейс
    virtual double time_in_path() const;                 // Время в пути (часы)
    virtual double cost_passengers(int passengers) const; // Стоимость перевозки пассажиров
    virtual double cost_cargo(double weightKg) const;     // Стоимость перевозки груза
    virtual std::string vehicle_type() const;             // Тип транспорта (для таблиц)
    virtual void print_header() const;                    // Шапка таблицы
    virtual void print_separator() const;                 // Разделительная линия таблицы
    virtual void menu() const;                            // Меню базовых операций

    // Геттеры
    std::string GetName() const;
    double GetDistance() const;
    double GetPassengerRate() const;
    double GetCargoRate() const;
    double GetSpeed() const;

    // Сеттеры
    void SetName(const std::string& Name);
    void SetDistance(double Distance);
    void SetPassengerRate(double Rate);
    void SetCargoRate(double Rate);
    void SetSpeed(double Speed);

    // Операторы
    friend std::istream& operator>>(std::istream& is, TransportVehicle& ob);
    friend std::ostream& operator<<(std::ostream& os, TransportVehicle& ob);
    TransportVehicle& operator=(const TransportVehicle& other);
};