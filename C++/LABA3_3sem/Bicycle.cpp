#include "Bicycle.h"
#include <limits>

Bicycle::Bicycle() = default;

Bicycle::Bicycle(int GearCount,
                 bool HasCargoRack,
                 double MaxCargo,
                 const std::string& Name,
                 double Distance,
                 double PassengerRate,
                 double CargoRate,
                 double Speed)
    : TransportVehicle(Name, Distance, PassengerRate, CargoRate, Speed)
{
    gearCount = GearCount;
    hasCargoRack = HasCargoRack;
    maxCargo = MaxCargo;
}

Bicycle::Bicycle(const Bicycle& other) = default;

Bicycle::~Bicycle() = default;

double Bicycle::time_in_path() const
{
    // Велосипед делает паузу каждые 30 км по 0.1 часа
    double stops = distance > 0 ? (distance / 30.0) * 0.1 : 0.0;
    return TransportVehicle::time_in_path() + stops;
}

double Bicycle::cost_cargo(double cargoWeight) const
{
    if (cargoWeight > maxCargo)
    {
        std::cout << "Превышен максимальный груз!" << std::endl;
        return 0.0;
    }
    return TransportVehicle::cost_cargo(cargoWeight);
}

int Bicycle::GetGearCount() const
{
    return gearCount;
}

bool Bicycle::GetHasCargoRack() const
{
    return hasCargoRack;
}

double Bicycle::GetMaxCargo() const
{
    return maxCargo;
}

void Bicycle::SetGearCount(int GearCount)
{
    if (GearCount >= 0)
    {
        gearCount = GearCount;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

void Bicycle::SetHasCargoRack(bool HasCargoRack)
{
    hasCargoRack = HasCargoRack;
}

void Bicycle::SetMaxCargo(double MaxCargo)
{
    if (MaxCargo >= 0)
    {
        maxCargo = MaxCargo;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

std::istream& operator>>(std::istream& is, Bicycle& bicycle)
{
    std::cout << "--- Ввод данных о велосипеде ---" << std::endl;
    is >> static_cast<TransportVehicle&>(bicycle);
    std::cout << "Введите количество передач: ";
    is >> bicycle.gearCount;
    std::cout << "Есть багажник? (1 - да, 0 - нет): ";
    is >> bicycle.hasCargoRack;
    std::cout << "Введите максимальный груз (кг): ";
    is >> bicycle.maxCargo;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, const Bicycle& bicycle)
{
    os << static_cast<const TransportVehicle&>(bicycle)
       << ", передач: " << bicycle.gearCount
       << ", багажник: " << (bicycle.hasCargoRack ? "есть" : "нет")
       << ", макс. груз: " << bicycle.maxCargo << " кг";
    return os;
}

Bicycle& Bicycle::operator=(const Bicycle& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
        gearCount = other.gearCount;
        hasCargoRack = other.hasCargoRack;
        maxCargo = other.maxCargo;
    }
    return *this;
}

