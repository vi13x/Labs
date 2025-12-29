#include "Car.h"
#include "ExceptionHandler.h"
#include <limits>
#include <cmath>

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


void Car::print_table() const
{
    std::cout << std::left
              << std::setw(20) << "Автомобиль"     << "| "
              << std::setw(20) << name             << "| "
              << std::setw(12) << distance         << "| "
              << std::setw(12) << speed            << "| "
              << std::setw(18) << passengerRatePerKm << "| "
              << std::setw(18) << cargoRatePerKmPerKg << "| "
              << std::setw(12) << time_in_path()   << "| " << std::endl;
}

void Car::print_separator() const
{
    std::cout << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+" 
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::endl;
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

double Car::get_fuel_consumption() const
{
    return fuelConsumption;
}

void Car::set_fuel_consumption(double Consumption)
{
    if (Consumption <= 0)
        throw InvalidArgumentException("fuelConsumption", "Расход топлива должен быть больше 0");
    
    if (Consumption > 50)
        throw OverflowErrorException("установка расхода топлива", "Расход топлива превышает максимальное значение (50 л/100км)");
    
    if (std::isinf(Consumption) || std::isnan(Consumption))
        throw DomainErrorException("Расход топлива не может быть бесконечным или NaN");
    
    fuelConsumption = Consumption;
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
    if (Mileage < 0)
        throw InvalidArgumentException("mileageSinceMaintenance", "Пробег не может быть отрицательным");
    
    if (std::isinf(Mileage) || std::isnan(Mileage))
        throw DomainErrorException("Пробег не может быть бесконечным или NaN");
    
    if (Mileage > 10000000.0)
        throw OverflowErrorException("установка пробега", "Пробег слишком большой");
    
    mileageSinceMaintenance = Mileage;
}

bool Car::needs_maintenance() const
{
    return mileageSinceMaintenance >= 10000.0;
}

double Car::calculate_fuel_cost(double fuelPrice) const
{
    if (fuelPrice < 0)
        throw InvalidArgumentException("fuelPrice", "Цена топлива не может быть отрицательной");
    
    if (std::isinf(fuelPrice) || std::isnan(fuelPrice))
        throw DomainErrorException("Цена топлива не может быть бесконечной или NaN");
    
    double fuelNeeded = (fuelConsumption / 100.0) * distance;
    
    if (std::isinf(fuelNeeded) || std::isnan(fuelNeeded))
        throw OverflowErrorException("вычисление расхода топлива", "Результат переполнения");
    
    double result = fuelNeeded * fuelPrice;
    
    if (std::isinf(result) || std::isnan(result))
        throw OverflowErrorException("вычисление стоимости топлива", "Результат переполнения");
    
    return result;
}

void Car::update_mileage(double additionalMileage)
{
    if (additionalMileage < 0)
        throw InvalidArgumentException("additionalMileage", "Дополнительный пробег не может быть отрицательным");
    
    if (std::isinf(additionalMileage) || std::isnan(additionalMileage))
        throw DomainErrorException("Дополнительный пробег не может быть бесконечным или NaN");
    
    double newMileage = mileageSinceMaintenance + additionalMileage;
    
    if (std::isinf(newMileage) || std::isnan(newMileage))
        throw OverflowErrorException("обновление пробега", "Результат переполнения");
    
    if (newMileage > 10000000.0)
        throw OverflowErrorException("обновление пробега", "Пробег слишком большой");
    
    mileageSinceMaintenance = newMileage;
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

std::ostream& operator<<(std::ostream& os, const Car& ob)
{
    os << static_cast<const TransportVehicle&>(ob);
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


