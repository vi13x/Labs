#include "Car.h"
#include <limits>

Car::Car() : TransportVehicle()
{
    fuelConsumption = 8.0;
    fuelType = "Бензин";
    mileageSinceMaintenance = 0.0;
}

Car::Car(const std::string& Name,
         double Distance,
         double PassengerRate,
         double CargoRate,
         double Speed)
        : TransportVehicle(Name, Distance, PassengerRate, CargoRate, Speed)
{
    fuelConsumption = 8.0;
    fuelType = "Бензин";
    mileageSinceMaintenance = 0.0;
}

Car::Car(const Car& other) : TransportVehicle(other)
{
    fuelConsumption = other.fuelConsumption;
    fuelType = other.fuelType;
    mileageSinceMaintenance = other.mileageSinceMaintenance;
}

Car::~Car() = default;

std::string Car::vehicle_type() const
{
    return "Автомобиль";
}

void Car::print_header() const
{
    std::cout << "+----+----------+----------+----------+----------+----------+----------+" << std::endl;
    std::cout << "| №  | Название | Дистанция| Скорость | Цена/км  | Цена/км  | Время    |" << std::endl;
    std::cout << "|    |          |          |          | пасс     | кг       |          |" << std::endl;
    std::cout << "+----+----------+----------+----------+----------+----------+----------+" << std::endl;
}

void Car::print_separator() const
{
    std::cout << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+" 
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+" << std::endl;
}

void Car::menu() const
{
    std::cout << "\n=== МЕНЮ АВТОМОБИЛЯ ===\n";
    TransportVehicle::menu();
    std::cout << "14. Получить расход топлива\n";
    std::cout << "15. Установить расход топлива\n";
    std::cout << "16. Получить тип топлива\n";
    std::cout << "17. Установить тип топлива\n";
    std::cout << "18. Получить пробег с последнего ТО\n";
    std::cout << "19. Установить пробег с последнего ТО\n";
    std::cout << "20. Проверить необходимость ТО\n";
    std::cout << "21. Рассчитать стоимость топлива для поездки\n";
    std::cout << "22. Обновить пробег после поездки\n";
}

// Уникальные методы для автомобиля
double Car::get_fuel_consumption() const
{
    return fuelConsumption;
}

void Car::set_fuel_consumption(double Consumption)
{
    if (Consumption > 0 && Consumption <= 50)
        fuelConsumption = Consumption;
    else
        std::cout << "Ошибка: расход топлива должен быть от 0 до 50 л/100км!\n";
}

std::string Car::get_fuel_type() const
{
    return fuelType;
}

void Car::set_fuel_type(const std::string& Type)
{
    fuelType = Type;
}

double Car::get_mileage_since_maintenance() const
{
    return mileageSinceMaintenance;
}

void Car::set_mileage_since_maintenance(double Mileage)
{
    if (Mileage >= 0)
        mileageSinceMaintenance = Mileage;
    else
        std::cout << "Ошибка: пробег не может быть отрицательным!\n";
}

bool Car::needs_maintenance() const
{
    return mileageSinceMaintenance >= 10000.0;
}

double Car::calculate_fuel_cost(double fuelPrice) const
{
    // Рассчитываем количество топлива для поездки: (расход / 100) * расстояние
    double fuelNeeded = (fuelConsumption / 100.0) * distance;
    return fuelNeeded * fuelPrice;
}

void Car::update_mileage(double additionalMileage)
{
    if (additionalMileage >= 0)
        mileageSinceMaintenance += additionalMileage;
    else
        std::cout << "Ошибка: пробег не может быть отрицательным!\n";
}

std::istream& operator>>(std::istream& is, Car& ob)
{
    is >> static_cast<TransportVehicle&>(ob);
    std::cout << "Введите расход топлива (л/100км): ";
    is >> ob.fuelConsumption;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите тип топлива: ";
    std::getline(is >> std::ws, ob.fuelType);
    std::cout << "Введите пробег с последнего ТО (км): ";
    is >> ob.mileageSinceMaintenance;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, Car& ob)
{
    // Вызываем базовый оператор для вывода базовых полей
    os << static_cast<TransportVehicle&>(ob);
    return os;
}

Car& Car::operator=(const Car& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
        fuelConsumption = other.fuelConsumption;
        fuelType = other.fuelType;
        mileageSinceMaintenance = other.mileageSinceMaintenance;
    }
    return *this;
}