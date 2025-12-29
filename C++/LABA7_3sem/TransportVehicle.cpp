#include "TransportVehicle.h"
#include "ExceptionHandler.h"
#include <limits>
#include <cmath>

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
    if (speed <= 0)
        throw DomainErrorException("Невозможно вычислить время: скорость должна быть больше 0");
    
    if (distance < 0)
        throw DomainErrorException("Невозможно вычислить время: расстояние не может быть отрицательным");
    
    double result = distance / speed;
    
    if (std::isinf(result))
        throw OverflowErrorException("вычисление времени в пути", "Результат бесконечен");
    
    if (std::isnan(result))
        throw DomainErrorException("Результат вычисления времени в пути: NaN");
    
    return result;
}

double TransportVehicle::cost_passengers(int p) const
{
    if (p < 0)
        throw InvalidArgumentException("passengers", "Количество пассажиров не может быть отрицательным");
    
    if (p == 0)
        return 0;
    
    if (p > 1000)
        throw OverflowErrorException("вычисление стоимости пассажиров", "Слишком большое количество пассажиров");
    
    double result = static_cast<double>(p) * passengerRatePerKm * distance;
    
    if (std::isinf(result) || std::isnan(result))
        throw OverflowErrorException("вычисление стоимости пассажиров", "Результат переполнения");
    
    return result;
}

double TransportVehicle::cost_cargo(double w) const
{
    if (w < 0)
        throw InvalidArgumentException("weight", "Вес груза не может быть отрицательным");
    
    if (w == 0)
        return 0;
    
    if (w > 1000000.0)
        throw OverflowErrorException("вычисление стоимости груза", "Слишком большой вес груза");
    
    double result = w * cargoRatePerKmPerKg * distance;
    
    if (std::isinf(result) || std::isnan(result))
        throw OverflowErrorException("вычисление стоимости груза", "Результат переполнения");
    
    return result;
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
    if (Distance < 0)
        throw InvalidArgumentException("distance", "Расстояние не может быть отрицательным");
    
    if (std::isinf(Distance) || std::isnan(Distance))
        throw DomainErrorException("Расстояние не может быть бесконечным или NaN");
    
    if (Distance > 1000000.0)
        throw OverflowErrorException("установка расстояния", "Расстояние слишком большое");
    
    distance = Distance;
}

void TransportVehicle::SetPassengerRate(double Rate)
{
    if (Rate < 0)
        throw InvalidArgumentException("passengerRate", "Цена за км (пассажиры) не может быть отрицательной");
    
    if (std::isinf(Rate) || std::isnan(Rate))
        throw DomainErrorException("Цена за км (пассажиры) не может быть бесконечной или NaN");
    
    if (Rate > 1000000.0)
        throw OverflowErrorException("установка цены за км (пассажиры)", "Цена слишком большая");
    
    passengerRatePerKm = Rate;
}

void TransportVehicle::SetCargoRate(double Rate)
{
    if (Rate < 0)
        throw InvalidArgumentException("cargoRate", "Цена за км (груз) не может быть отрицательной");
    
    if (std::isinf(Rate) || std::isnan(Rate))
        throw DomainErrorException("Цена за км (груз) не может быть бесконечной или NaN");
    
    if (Rate > 1000000.0)
        throw OverflowErrorException("установка цены за км (груз)", "Цена слишком большая");
    
    cargoRatePerKmPerKg = Rate;
}

void TransportVehicle::SetSpeed(double Speed)
{
    if (Speed <= 0)
        throw InvalidArgumentException("speed", "Скорость должна быть больше 0");
    
    if (std::isinf(Speed) || std::isnan(Speed))
        throw DomainErrorException("Скорость не может быть бесконечной или NaN");
    
    if (Speed > 10000.0)
        throw OverflowErrorException("установка скорости", "Скорость слишком большая (превышает 10000 км/ч)");
    
    speed = Speed;
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


