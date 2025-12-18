#include "Cart.h"
#include <limits>

Cart::Cart() : TransportVehicle()
{
    horseCount = 1;
    cartType = "Телега";
    hoursSinceLastFeed = 0.0;
}

Cart::Cart(const std::string& Name,
           double Distance,
           double PassengerRate,
           double CargoRate,
           double Speed)
        : TransportVehicle(Name, Distance, PassengerRate, CargoRate, Speed)
{
    horseCount = 1;
    cartType = "Телега";
    hoursSinceLastFeed = 0.0;
}

Cart::Cart(const Cart& other) : TransportVehicle(other)
{
    horseCount = other.horseCount;
    cartType = other.cartType;
    hoursSinceLastFeed = other.hoursSinceLastFeed;
}

Cart::~Cart() = default;

std::string Cart::vehicle_type() const
{
    return "Повозка";
}


void Cart::print_table() const
{
    std::cout << std::left
              << std::setw(17) << "Повозка"        << "| "
              << std::setw(20) << name             << "| "
              << std::setw(12) << distance         << "| "
              << std::setw(12) << speed            << "| "
              << std::setw(18) << passengerRatePerKm << "| "
              << std::setw(18) << cargoRatePerKmPerKg << "| "
              << std::setw(12) << time_in_path()   << "| " << std::endl;
}

void Cart::print_separator() const
{
    std::cout << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+" 
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::string(15, '-') << "+"
              << std::string(15, '-') << "+" << std::endl;
}

void Cart::menu() const
{
    std::cout << "\n=== МЕНЮ ПОВОЗКИ ===\n";
    TransportVehicle::menu();
    std::cout << "14. Получить количество лошадей\n";
    std::cout << "15. Установить количество лошадей\n";
    std::cout << "16. Получить тип повозки\n";
    std::cout << "17. Установить тип повозки\n";
    std::cout << "18. Получить часов с последнего кормления\n";
    std::cout << "19. Установить часов с последнего кормления\n";
    std::cout << "20. Проверить необходимость кормления лошадей\n";
    std::cout << "21. Рассчитать стоимость корма\n";
    std::cout << "22. Покормить лошадей\n";
}

int Cart::get_horse_count() const
{
    return horseCount;
}

void Cart::set_horse_count(int Count)
{
    if (Count >= 1 && Count <= 8)
        horseCount = Count;
    else
        std::cout << "Ошибка: количество лошадей должно быть от 1 до 8!\n";
}

std::string Cart::get_cart_type() const
{
    return cartType;
}

void Cart::set_cart_type(const std::string& Type)
{
    cartType = Type;
}

double Cart::get_hours_since_last_feed() const
{
    return hoursSinceLastFeed;
}

void Cart::set_hours_since_last_feed(double Hours)
{
    if (Hours >= 0)
        hoursSinceLastFeed = Hours;
    else
        std::cout << "Ошибка: время не может быть отрицательным!\n";
}

bool Cart::needs_horse_feed() const
{
    return hoursSinceLastFeed >= 6.0;
}

double Cart::calculate_feed_cost(double feedPricePerHorse) const
{
    return horseCount * feedPricePerHorse;
}

void Cart::feed_horses()
{
    hoursSinceLastFeed = 0.0;
    std::cout << "Лошади покормлены!\n";
}

std::istream& operator>>(std::istream& is, Cart& ob)
{
    is >> static_cast<TransportVehicle&>(ob);
    std::cout << "Введите количество лошадей: ";
    is >> ob.horseCount;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите тип повозки: ";
    std::getline(is >> std::ws, ob.cartType);
    std::cout << "Введите часов с последнего кормления: ";
    is >> ob.hoursSinceLastFeed;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, const Cart& ob)
{
    os << std::setw(15) << std::left << ob.vehicle_type() << "|"
       << std::setw(10) << std::left << ob.GetName() << "|"
       << std::setw(10) << std::right << std::fixed << std::setprecision(2) << ob.GetDistance() << "|"
       << std::setw(15) << std::right << std::fixed << std::setprecision(2) << ob.GetSpeed() << "|"
       << std::setw(10) << std::right << std::fixed << std::setprecision(2) << ob.GetPassengerRate() << "|"
       << std::setw(10) << std::right << std::fixed << std::setprecision(2) << ob.GetCargoRate() << "|"
       << std::setw(16) << std::right << std::fixed << std::setprecision(2) << ob.time_in_path() << "|"
       << std::setw(13) << std::right << ob.get_horse_count() << "|"
       << std::setw(13) << std::left << ob.get_cart_type() << "|"
       << std::setw(16) << std::right << std::fixed << std::setprecision(2) << ob.get_hours_since_last_feed() << "|";
    return os;
}

Cart& Cart::operator=(const Cart& other)
{
    if (this != &other)
    {
        TransportVehicle::operator=(other);
        horseCount = other.horseCount;
        cartType = other.cartType;
        hoursSinceLastFeed = other.hoursSinceLastFeed;
    }
    return *this;
}
