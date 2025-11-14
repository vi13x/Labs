#include "Car.h"
#include <limits>

Car::Car() = default;

Car::Car(double FuelPrice,
         int PassengerCapacity,
         double TrunkVolume,
         const std::string& Name,
         double Distance,
         double PassengerRate,
         double CargoRate,
         double Speed)
    : TransportVehicle(Name, Distance, PassengerRate, CargoRate, Speed)
{
    fuelPrice = FuelPrice;
    passengerCapacity = PassengerCapacity;
    trunkVolume = TrunkVolume;
}

Car::Car(const Car& other) = default;

Car::~Car() = default;

double Car::time_in_path() const
{
    // Автомобиль делает остановки каждые 200 км на 0.25 часа
    double stops = distance > 0 ? (distance / 200.0) * 0.25 : 0.0;
    return TransportVehicle::time_in_path() + stops;
}

double Car::cost_passengers(int passengers) const
{
    double base = TransportVehicle::cost_passengers(passengers);
    return base + fuelPrice;
}

double Car::GetFuelPrice() const
{
    return fuelPrice;
}

int Car::GetPassengerCapacity() const
{
    return passengerCapacity;
}

double Car::GetTrunkVolume() const
{
    return trunkVolume;
}

void Car::SetFuelPrice(double FuelPrice)
{
    if (FuelPrice >= 0)
    {
        fuelPrice = FuelPrice;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

void Car::SetPassengerCapacity(int PassengerCapacity)
{
    if (PassengerCapacity >= 0)
    {
        passengerCapacity = PassengerCapacity;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

void Car::SetTrunkVolume(double TrunkVolume)
{
    if (TrunkVolume >= 0)
    {
        trunkVolume = TrunkVolume;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

std::istream& operator>>(std::istream& is, Car& car)
{
    std::cout << "--- Ввод данных об автомобиле ---" << std::endl;
    is >> static_cast<TransportVehicle&>(car);
    std::cout << "Введите стоимость топлива за поездку: ";
    is >> car.fuelPrice;
    std::cout << "Введите максимальное количество пассажиров: ";
    is >> car.passengerCapacity;
    std::cout << "Введите объём багажника (л): ";
    is >> car.trunkVolume;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, const Car& car)
{
    os << static_cast<const TransportVehicle&>(car)
       << ", топливо: " << car.fuelPrice
       << ", мест: " << car.passengerCapacity
       << ", багажник: " << car.trunkVolume << " л";
    return os;
}

Car& Car::operator=(const Car& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
        fuelPrice = other.fuelPrice;
        passengerCapacity = other.passengerCapacity;
        trunkVolume = other.trunkVolume;
    }
    return *this;
}

