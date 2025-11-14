#include "Cart.h"
#include <limits>

Cart::Cart() = default;

Cart::Cart(int HorseCount,
           double RestTime,
           double MaxPayload,
           const std::string& Name,
           double Distance,
           double PassengerRate,
           double CargoRate,
           double Speed)
    : TransportVehicle(Name, Distance, PassengerRate, CargoRate, Speed)
{
    horseCount = HorseCount;
    restTime = RestTime;
    maxPayload = MaxPayload;
}

Cart::Cart(const Cart& other) = default;

Cart::~Cart() = default;

double Cart::time_in_path() const
{
    double base = TransportVehicle::time_in_path();
    return base + restTime;
}

double Cart::cost_cargo(double cargoWeight) const
{
    if (cargoWeight > maxPayload)
    {
        std::cout << "Превышена грузоподъёмность!" << std::endl;
        return 0.0;
    }
    return TransportVehicle::cost_cargo(cargoWeight);
}

int Cart::GetHorseCount() const
{
    return horseCount;
}

double Cart::GetRestTime() const
{
    return restTime;
}

double Cart::GetMaxPayload() const
{
    return maxPayload;
}

void Cart::SetHorseCount(int HorseCount)
{
    if (HorseCount > 0)
    {
        horseCount = HorseCount;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

void Cart::SetRestTime(double RestTime)
{
    if (RestTime >= 0)
    {
        restTime = RestTime;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

void Cart::SetMaxPayload(double MaxPayload)
{
    if (MaxPayload >= 0)
    {
        maxPayload = MaxPayload;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

std::istream& operator>>(std::istream& is, Cart& cart)
{
    std::cout << "--- Ввод данных о повозке ---" << std::endl;
    is >> static_cast<TransportVehicle&>(cart);
    std::cout << "Введите количество лошадей: ";
    is >> cart.horseCount;
    std::cout << "Введите дополнительное время отдыха (ч): ";
    is >> cart.restTime;
    std::cout << "Введите грузоподъёмность (кг): ";
    is >> cart.maxPayload;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, const Cart& cart)
{
    os << static_cast<const TransportVehicle&>(cart)
       << ", лошадей: " << cart.horseCount
       << ", отдых: " << cart.restTime << " ч"
       << ", грузоподъёмность: " << cart.maxPayload << " кг";
    return os;
}

Cart& Cart::operator=(const Cart& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
        horseCount = other.horseCount;
        restTime = other.restTime;
        maxPayload = other.maxPayload;
    }
    return *this;
}

