#pragma once

#include "TransportVehicle.h"

class Cart : public TransportVehicle
{
private:
    int horseCount{};        // Количество лошадей
    double restTime{};       // Время отдыха (часы)
    double maxPayload{};     // Максимальная грузоподъёмность (кг)

public:
    Cart();
    Cart(int HorseCount,
         double RestTime,
         double MaxPayload,
         const std::string& Name,
         double Distance,
         double PassengerRate,
         double CargoRate,
         double Speed);
    Cart(const Cart& other);
    ~Cart() override;

    double time_in_path() const override;
    double cost_cargo(double cargoWeight) const override;
    void menu() override;

    int GetHorseCount() const;
    double GetRestTime() const;
    double GetMaxPayload() const;

    void SetHorseCount(int HorseCount);
    void SetRestTime(double RestTime);
    void SetMaxPayload(double MaxPayload);

    friend std::istream& operator>>(std::istream& is, Cart& cart);
    friend std::ostream& operator<<(std::ostream& os, Cart& cart);
    Cart& operator=(const Cart& other);

    void print_header() const override;
    void print_table() const override;
};
