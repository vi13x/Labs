#include "TransportVehicle.h"
#include <limits>

TransportVehicle::TransportVehicle()
{
    name = "Не задано";
    distance = 0.0;
    passengerRatePerKm = 0.0;
    cargoRatePerKmPerKg = 0.0;
    speed = 0.0;
}

TransportVehicle::TransportVehicle(const std::string& Name,
                                   double Distance,
                                   double PassengerRate,
                                   double CargoRate,
                                   double Speed)
{
    name = Name;
    distance = Distance;
    passengerRatePerKm = PassengerRate;
    cargoRatePerKmPerKg = CargoRate;
    speed = Speed;
}

TransportVehicle::TransportVehicle(const TransportVehicle& o)
{
    name = o.name;
    distance = o.distance;
    passengerRatePerKm = o.passengerRatePerKm;
    cargoRatePerKmPerKg = o.cargoRatePerKmPerKg;
    speed = o.speed;
}

TransportVehicle::~TransportVehicle() {}

double TransportVehicle::time_in_path() const
{
    return speed <= 0 ? 0 : distance / speed;
}

double TransportVehicle::cost_passengers(int p) const
{
    return p <= 0 ? 0 : p * passengerRatePerKm * distance;
}

double TransportVehicle::cost_cargo(double w) const
{
    return w <= 0 ? 0 : w * cargoRatePerKmPerKg * distance;
}

std::string TransportVehicle::vehicle_type() const
{
    return "Транспорт";
}

void TransportVehicle::print_separator() const
{
    std::cout << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+" 
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const TransportVehicle::HeaderTag&)
{
    os << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+" 
       << std::string(15, '-') << "+" << std::string(15, '-') << "+"
       << std::string(15, '-') << "+" << std::string(15, '-') << "+"
       << std::string(15, '-') << "+" << std::endl;
    os << "|" << std::left << std::setw(15) << "Тип"            << "|"
       << std::setw(15) << "Название"       << "|"
       << std::setw(15) << "Дистанция"      << "|"
       << std::setw(15) << "Скорость"       << "|"
       << std::setw(15) << "Цена/км пасс"   << "|"
       << std::setw(15) << "Цена/км кг"     << "|"
       << std::setw(15) << "Время"          << "|" << std::endl;
    os << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+" 
       << std::string(15, '-') << "+" << std::string(15, '-') << "+"
       << std::string(15, '-') << "+" << std::string(15, '-') << "+"
       << std::string(15, '-') << "+" << std::endl;
    return os;
}

void TransportVehicle::print_table() const
{
    std::cout << std::left
              << std::setw(20) << "Транспорт"      << "| "
              << std::setw(20) << name             << "| "
              << std::setw(10) << distance         << "| "
              << std::setw(12) << speed            << "| "
              << std::setw(18) << passengerRatePerKm << "| "
              << std::setw(18) << cargoRatePerKmPerKg << "| "
              << std::setw(12) << time_in_path()   << "| " << std::endl;
}


void TransportVehicle::menu() const
{
    std::cout <<
              "\n0. Выход\n"
              "1. Показать объект\n"
              "2. Изменить название\n"
              "3. Изменить расстояние\n"
              "4. Изменить цену за км (пассажиры)\n"
              "5. Изменить цену за км (груз)\n"
              "6. Изменить скорость\n"
              "7. Получить название\n"
              "8. Получить расстояние\n"
              "9. Получить цену за км (пассажиры)\n"
              "10. Получить цену за км (груз)\n"
              "11. Получить скорость\n"
              "12. Посчитать стоимость перевозки пассажиров\n"
              "13. Посчитать стоимость перевозки груза\n";
}

std::string TransportVehicle::GetName() const { return name; }
double TransportVehicle::GetDistance() const { return distance; }
double TransportVehicle::GetPassengerRate() const { return passengerRatePerKm; }
double TransportVehicle::GetCargoRate() const { return cargoRatePerKmPerKg; }
double TransportVehicle::GetSpeed() const { return speed; }

void TransportVehicle::SetName(const std::string& Name) { name = Name; }

void TransportVehicle::SetDistance(double Distance)
{
    if (Distance >= 0)
        distance = Distance;
    else
        std::cout << "Ошибка: расстояние не может быть отрицательным!\n";
}

void TransportVehicle::SetPassengerRate(double Rate)
{
    if (Rate >= 0)
        passengerRatePerKm = Rate;
    else
        std::cout << "Ошибка: цена не может быть отрицательной!\n";
}

void TransportVehicle::SetCargoRate(double Rate)
{
    if (Rate >= 0)
        cargoRatePerKmPerKg = Rate;
    else
        std::cout << "Ошибка: цена не может быть отрицательной!\n";
}

void TransportVehicle::SetSpeed(double Speed)
{
    if (Speed > 0)
        speed = Speed;
    else
        std::cout << "Ошибка: скорость должна быть > 0!\n";
}

bool TransportVehicle::operator==(const TransportVehicle& o) const
{
    return name == o.name;
}

std::istream& operator>>(std::istream& is, TransportVehicle& ob)
{
    std::cout << "Введите название: ";
    std::getline(is >> std::ws, ob.name);

    std::cout << "Введите расстояние (км): ";
    is >> ob.distance;

    std::cout << "Введите цену за км (пассажиры): ";
    is >> ob.passengerRatePerKm;

    std::cout << "Введите цену за км (1 кг груза): ";
    is >> ob.cargoRatePerKmPerKg;

    std::cout << "Введите скорость (км/ч): ";
    is >> ob.speed;

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, const TransportVehicle& ob)
{
    os << std::setw(10) << std::left << ob.name << "|"
       << std::setw(10) << std::right << std::fixed << std::setprecision(2) << ob.distance << "|"
       << std::setw(10) << std::right << std::fixed << std::setprecision(2) << ob.speed << "|"
       << std::setw(10) << std::right << std::fixed << std::setprecision(2) << ob.passengerRatePerKm << "|"
       << std::setw(10) << std::right << std::fixed << std::setprecision(2) << ob.cargoRatePerKmPerKg << "|"
       << std::setw(10) << std::right << std::fixed << std::setprecision(2) << ob.time_in_path() << "|";
    return os;
}

TransportVehicle& TransportVehicle::operator=(const TransportVehicle& o)
{
    if (this != &o)
    {
        name = o.name;
        distance = o.distance;
        passengerRatePerKm = o.passengerRatePerKm;
        cargoRatePerKmPerKg = o.cargoRatePerKmPerKg;
        speed = o.speed;
    }
    return *this;
}
