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

void TransportVehicle::menu()
{
    std::cout << "=============МЕНЮ============" << std::endl;
    std::cout << "0. Выйти" << std::endl;
    std::cout << "1. Вывести объект" << std::endl;
    std::cout << "2. Изменить название" << std::endl;
    std::cout << "3. Изменить расстояние" << std::endl;
    std::cout << "4. Изменить тариф для пассажиров" << std::endl;
    std::cout << "5. Изменить тариф для груза" << std::endl;
    std::cout << "6. Изменить скорость" << std::endl;
    std::cout << "7. Получить название" << std::endl;
    std::cout << "8. Получить расстояние" << std::endl;
    std::cout << "9. Получить скорость" << std::endl;
}

void TransportVehicle::print_header() const
{
    std::cout << std::left
              << std::setw(15) << "Название" << "| "
              << std::setw(15) << "Расстояние" << "| "
              << std::setw(15) << "Скорость" << "| "
              << std::setw(15) << "Тариф пасс" << "| "
              << std::setw(15) << "Тариф груз" << "| ";
}

void TransportVehicle::print_table() const
{
    std::cout << std::left
              << std::setw(15) << name << "| "
              << std::setw(15) << distance << "| "
              << std::setw(15) << speed << "| "
              << std::setw(15) << passengerRate << "| "
              << std::setw(15) << cargoRate << "| ";
}

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
    vehicle.print_table();
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

