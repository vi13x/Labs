#pragma once

#include "TransportVehicle.h"

class Bicycle : public TransportVehicle
{
private:
    int gearCount{};        // Количество передач
    bool hasCargoRack{};    // Наличие багажника
    double maxCargo{};      // Максимальный перевозимый груз (кг)

public:
    Bicycle();
    Bicycle(int GearCount,
            bool HasCargoRack,
            double MaxCargo,
            const std::string& Name,
            double Distance,
            double PassengerRate,
            double CargoRate,
            double Speed);
    Bicycle(const Bicycle& other);
    ~Bicycle() override;

    double time_in_path() const override;
    double cost_cargo(double cargoWeight) const override;
    int GetGearCount() const;
    bool GetHasCargoRack() const;
    double GetMaxCargo() const;

    void SetGearCount(int GearCount);
    void SetHasCargoRack(bool HasCargoRack);
    void SetMaxCargo(double MaxCargo);

    friend std::istream& operator>>(std::istream& is, Bicycle& bicycle);
    friend std::ostream& operator<<(std::ostream& os, const Bicycle& bicycle);
    Bicycle& operator=(const Bicycle& other);

};
