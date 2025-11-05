#pragma once

#include <string>
#include <iostream>
#include <iomanip>

class TransportVehicle {
protected:
    std::string name;
    double distanceKm{};
    double speedKmh{};
    double passengerRatePerKm{};
    double cargoRatePerKmPerKg{};

public:
    TransportVehicle();

    TransportVehicle(std::string name,
                     double distanceKm,
                     double speedKmh,
                     double passengerRatePerKm,
                     double cargoRatePerKmPerKg);

    virtual ~TransportVehicle();
    virtual TransportVehicle* clone() const;
    virtual std::string type_name() const;

    virtual double time_in_path_hours() const;
    virtual double cost_passengers(int numPassengers) const;
    virtual double cost_cargo(double weightKg) const;

    void input_info_passengers(int numPassengers) const;
    void input_info_cargo(double weightKg) const;

    // getters
    const std::string& get_name() const { return name; }
    double get_distance_km() const { return distanceKm; }
    double get_speed_kmh() const { return speedKmh; }
    double get_passenger_rate_per_km() const { return passengerRatePerKm; }
    double get_cargo_rate_per_km_per_kg() const { return cargoRatePerKmPerKg; }

    // setters
    void set_name(const std::string& n) { name = n; }
    void set_distance_km(double d) { distanceKm = d; }
    void set_speed_kmh(double s) { speedKmh = s; }
    void set_passenger_rate_per_km(double r) { passengerRatePerKm = r; }
    void set_cargo_rate_per_km_per_kg(double r) { cargoRatePerKmPerKg = r; }

    // Методы для ввода и вывода
    virtual void input_info();
    virtual void printHeader();
    virtual void printTable();
    virtual void display(int index = 0); // Вывод шапки и данных объекта

    // Операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const TransportVehicle& vehicle);
    friend std::istream& operator>>(std::istream& is, TransportVehicle& vehicle);
};


