#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class TransportVehicle
{
protected:
    std::string name;
    double distance;
    double passengerRatePerKm;
    double cargoRatePerKmPerKg;
    double speed;

public:
    TransportVehicle();
    TransportVehicle(const std::string&, double, double, double, double);
    TransportVehicle(const TransportVehicle&);
    virtual ~TransportVehicle();

    virtual double time_in_path() const;
    virtual double cost_passengers(int) const;
    virtual double cost_cargo(double) const;
    virtual std::string vehicle_type() const;
    virtual void print_table() const;
    virtual void print_separator() const;
    virtual void menu() const;

    std::string GetName() const;
    double GetDistance() const;
    double GetPassengerRate() const;
    double GetCargoRate() const;
    double GetSpeed() const;

    void SetName(const std::string&);
    void SetDistance(double);
    void SetPassengerRate(double);
    void SetCargoRate(double);
    void SetSpeed(double);

    bool operator==(const TransportVehicle&) const;

    friend std::istream& operator>>(std::istream&, TransportVehicle&);
    friend std::ostream& operator<<(std::ostream&, const TransportVehicle&);
    TransportVehicle& operator=(const TransportVehicle&);

    // Структура для вывода заголовка через operator<<
    struct HeaderTag {};
    static HeaderTag header() { return HeaderTag{}; }
    friend std::ostream& operator<<(std::ostream&, const HeaderTag&);
};
