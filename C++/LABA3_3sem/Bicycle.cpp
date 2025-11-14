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

void Bicycle::menu()
{
    TransportVehicle::menu();
    std::cout << "14. Изменить количество передач" << std::endl;
    std::cout << "15. Получить количество передач" << std::endl;
    std::cout << "16. Изменить наличие багажника" << std::endl;
    std::cout << "17. Узнать наличие багажника" << std::endl;
    std::cout << "18. Изменить максимальный груз" << std::endl;
    std::cout << "19. Получить максимальный груз" << std::endl;
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

std::ostream& operator<<(std::ostream& os, Bicycle& bicycle)
{
    os << static_cast<TransportVehicle&>(bicycle);
    os << std::setw(15) << bicycle.gearCount << "| "
       << std::setw(15) << (bicycle.hasCargoRack ? "Да" : "Нет") << "| "
       << std::setw(15) << bicycle.maxCargo << "| ";
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

void Bicycle::print_header() const
{
    TransportVehicle::print_header();
    std::cout << std::left
              << std::setw(15) << "Передачи" << "| "
              << std::setw(15) << "Багажник" << "| "
              << std::setw(15) << "Макс. груз" << "| " << std::endl;
}

void Bicycle::print_table() const
{
    TransportVehicle::print_table();
    std::cout << std::left
              << std::setw(15) << gearCount << "| "
              << std::setw(15) << (hasCargoRack ? "Да" : "Нет") << "| "
              << std::setw(15) << maxCargo << "| " << std::endl;
}
