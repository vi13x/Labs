#include "Bicycle.h"
#include <limits>

Bicycle::Bicycle() : TransportVehicle()
{
    gears = 1;
    bicycleType = "Городской";
}

Bicycle::Bicycle(const std::string& Name,
                 double Distance,
                 double PassengerRate,
                 double CargoRate,
                 double Speed)
        : TransportVehicle(Name, Distance, PassengerRate, CargoRate, Speed)
{
    gears = 1;
    bicycleType = "Городской";
}

Bicycle::Bicycle(const Bicycle& other) : TransportVehicle(other)
{
    gears = other.gears;
    bicycleType = other.bicycleType;
}

Bicycle::~Bicycle() = default;

std::string Bicycle::vehicle_type() const
{
    return "Велосипед";
}

void Bicycle::print_header() const
{
    std::cout << "+----+----------+----------+----------+----------+----------+----------+" << std::endl;
    std::cout << "| №  | Название | Дистанция| Скорость | Цена/км  | Цена/км  | Время    |" << std::endl;
    std::cout << "|    |          |          |          | пасс     | кг       |          |" << std::endl;
    std::cout << "+----+----------+----------+----------+----------+----------+----------+" << std::endl;
}

void Bicycle::print_separator() const
{
    std::cout << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+" 
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::endl;
}

void Bicycle::menu() const
{
    std::cout << "\n=== МЕНЮ ВЕЛОСИПЕДА ===\n";
    TransportVehicle::menu();
    std::cout << "14. Получить количество передач\n";
    std::cout << "15. Установить количество передач\n";
    std::cout << "16. Получить тип велосипеда\n";
    std::cout << "17. Установить тип велосипеда\n";
    std::cout << "18. Проверить возможность подъема в гору\n";
    std::cout << "19. Рассчитать коэффициент усилия\n";
}

// Уникальные методы для велосипеда
int Bicycle::get_gears() const
{
    return gears;
}

void Bicycle::set_gears(int Gears)
{
    if (Gears >= 1 && Gears <= 30)
        gears = Gears;
    else
        std::cout << "Ошибка: количество передач должно быть от 1 до 30!\n";
}

std::string Bicycle::get_bicycle_type() const
{
    return bicycleType;
}

void Bicycle::set_bicycle_type(const std::string& Type)
{
    bicycleType = Type;
}

bool Bicycle::can_climb_hill(double gradient) const
{
    // Чем больше передач и меньше градиент, тем легче подняться
    // Максимальный градиент зависит от передач: больше передач = можно подняться на более крутой склон
    double maxGradient = 5.0 + (gears * 0.5); // Базовая формула
    return gradient <= maxGradient;
}

double Bicycle::calculate_effort_coefficient() const
{
    // Коэффициент усилия: чем больше передач, тем меньше усилий требуется
    // Формула: базовое усилие / количество передач
    return 10.0 / gears;
}

std::istream& operator>>(std::istream& is, Bicycle& ob)
{
    is >> static_cast<TransportVehicle&>(ob);
    std::cout << "Введите количество передач: ";
    is >> ob.gears;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите тип велосипеда: ";
    std::getline(is >> std::ws, ob.bicycleType);
    return is;
}

std::ostream& operator<<(std::ostream& os, Bicycle& ob)
{
    // Вызываем базовый оператор для вывода базовых полей
    os << static_cast<TransportVehicle&>(ob);
    return os;
}

Bicycle& Bicycle::operator=(const Bicycle& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
        gears = other.gears;
        bicycleType = other.bicycleType;
    }
    return *this;
}