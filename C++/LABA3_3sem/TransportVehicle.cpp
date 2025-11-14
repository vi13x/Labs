#include "TransportVehicle.h"

TransportVehicle::TransportVehicle() = default;

TransportVehicle::TransportVehicle(const std::string& Name,
                                   double Distance,
                                   double PassengerRate,
                                   double CargoRate,
                                   double Speed)
    : name(Name),
      distance(Distance),
      passengerRate(PassengerRate),
      cargoRate(CargoRate),
      speed(Speed) {}

TransportVehicle::TransportVehicle(const TransportVehicle& other) = default;

TransportVehicle::~TransportVehicle() = default;

double TransportVehicle::time_in_path() const
{
    if (speed <= 0)
    {
        return 0.0;
    }
    return distance / speed;
}

double TransportVehicle::cost_passengers(int passengers) const
{
    if (passengers <= 0)
    {
        return 0.0;
    }
    return distance * passengerRate * passengers;
}

double TransportVehicle::cost_cargo(double cargoWeight) const
{
    if (cargoWeight <= 0)
    {
        return 0.0;
    }
    return distance * cargoRate * cargoWeight;
}

std::string TransportVehicle::GetName() const
{
    return name;
}

double TransportVehicle::GetDistance() const
{
    return distance;
}

double TransportVehicle::GetPassengerRate() const
{
    return passengerRate;
}

double TransportVehicle::GetCargoRate() const
{
    return cargoRate;
}

double TransportVehicle::GetSpeed() const
{
    return speed;
}

void TransportVehicle::SetName(const std::string& Name)
{
    name = Name;
}

void TransportVehicle::SetDistance(double Distance)
{
    if (Distance > 0)
    {
        distance = Distance;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

void TransportVehicle::SetPassengerRate(double Rate)
{
    if (Rate > 0)
    {
        passengerRate = Rate;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

void TransportVehicle::SetCargoRate(double Rate)
{
    if (Rate > 0)
    {
        cargoRate = Rate;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

void TransportVehicle::SetSpeed(double Speed)
{
    if (Speed > 0)
    {
        speed = Speed;
    }
    else
    {
        std::cout << "Ошибка!" << std::endl;
    }
}

std::istream& operator>>(std::istream& is, TransportVehicle& vehicle)
{
    std::string inputName;
    std::cout << "Введите название: ";
    std::getline(is >> std::ws, inputName);
    vehicle.SetName(inputName);
    std::cout << "Введите расстояние (км): ";
    is >> vehicle.distance;
    std::cout << "Введите стоимость за км для пассажиров: ";
    is >> vehicle.passengerRate;
    std::cout << "Введите стоимость за км для груза (на 1 кг): ";
    is >> vehicle.cargoRate;
    std::cout << "Введите скорость (км/ч): ";
    is >> vehicle.speed;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, const TransportVehicle& vehicle)
{
    os << "Транспорт: " << vehicle.name
       << ", расстояние: " << vehicle.distance << " км"
       << ", скорость: " << vehicle.speed << " км/ч"
       << ", тариф пассажиры: " << vehicle.passengerRate
       << ", тариф груз: " << vehicle.cargoRate;
    return os;
}

TransportVehicle& TransportVehicle::operator=(const TransportVehicle& other)
{
    if (this != &other)
    {
        name = other.name;
        distance = other.distance;
        passengerRate = other.passengerRate;
        cargoRate = other.cargoRate;
        speed = other.speed;
    }
    return *this;
}

