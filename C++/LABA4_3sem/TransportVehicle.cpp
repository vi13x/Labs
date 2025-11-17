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

void TransportVehicle::print_header() const
{
    std::cout << std::left
              << std::setw(13) << "Тип"            << "| "
              << std::setw(28) << "Название"       << "| "
              << std::setw(17) << "Дистанция   "      << "| "
              << std::setw(12) << "Скорость    "       << "| "
              << std::setw(18) << "Цена/км пасс      "   << "| "
              << std::setw(18) << "Цена/км кг        "     << "| "
              << std::setw(12) << "Время"          << "     | " << std::endl;
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

void TransportVehicle::SetName(const std::string& s) { name = s; }
void TransportVehicle::SetDistance(double v) { if (v >= 0) distance = v; }
void TransportVehicle::SetPassengerRate(double v) { if (v >= 0) passengerRatePerKm = v; }
void TransportVehicle::SetCargoRate(double v) { if (v >= 0) cargoRatePerKmPerKg = v; }
void TransportVehicle::SetSpeed(double v) { if (v > 0) speed = v; }

bool TransportVehicle::operator==(const TransportVehicle& o) const
{
    return name == o.name;
}

std::istream& operator>>(std::istream& is, TransportVehicle& ob)
{
    std::cout << "Название: ";
    getline(is >> std::ws, ob.name);

    std::cout << "Расстояние: ";
    is >> ob.distance;

    std::cout << "Цена/км (пассажиры): ";
    is >> ob.passengerRatePerKm;

    std::cout << "Цена/км (кг груза): ";
    is >> ob.cargoRatePerKmPerKg;

    std::cout << "Скорость: ";
    is >> ob.speed;

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, TransportVehicle& ob)
{
    os << std::left
            << std::setw(13) << "Транспорт" << "| "
            << std::setw(28) << ob.name << "| "
            << std::setw(12) << ob.distance << "| "
            << std::setw(12) << ob.speed << "| "
            << std::setw(18) << ob.passengerRatePerKm << "| "
            << std::setw(18) << ob.cargoRatePerKmPerKg << "| "
            << std::setw(12) << ob.time_in_path() << "| " << std::endl;
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
