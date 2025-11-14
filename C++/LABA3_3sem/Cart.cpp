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

void Cart::menu()
{
    TransportVehicle::menu();
    std::cout << "14. Изменить количество лошадей" << std::endl;
    std::cout << "15. Получить количество лошадей" << std::endl;
    std::cout << "16. Изменить время отдыха" << std::endl;
    std::cout << "17. Получить время отдыха" << std::endl;
    std::cout << "18. Изменить грузоподъёмность" << std::endl;
    std::cout << "19. Получить грузоподъёмность" << std::endl;
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

std::ostream& operator<<(std::ostream& os, Cart& cart)
{
    os << static_cast<TransportVehicle&>(cart);
    os << std::setw(15) << cart.horseCount << "| "
       << std::setw(15) << cart.restTime << "| "
       << std::setw(15) << cart.maxPayload << "| ";
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

void Cart::print_header() const
{
    TransportVehicle::print_header();
    std::cout << std::left
              << std::setw(15) << "Лошадей" << "| "
              << std::setw(15) << "Отдых (ч)" << "| "
              << std::setw(15) << "Макс. груз" << "| " << std::endl;
}

void Cart::print_table() const
{
    TransportVehicle::print_table();
    std::cout << std::left
              << std::setw(15) << horseCount << "| "
              << std::setw(15) << restTime << "| "
              << std::setw(15) << maxPayload << "| " << std::endl;
}
