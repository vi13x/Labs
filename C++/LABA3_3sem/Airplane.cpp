#include "Airplane.h"

Airplane::Airplane() : Passenger_carrier(), collections(0), passenger_capacity(0), cargo_capacity(0.0) {}

Airplane::Airplane(int Collections,
                   int PassengerCapacity,
                   double CargoCapacity,
                   const std::string& Name,
                   double Distance,
                   double Money_km,
                   double Speed)
    : Passenger_carrier(Name, Distance, Money_km, Speed),
      collections(Collections),
      passenger_capacity(PassengerCapacity),
      cargo_capacity(CargoCapacity) {}

Airplane::Airplane(const Airplane& other) = default;

Airplane::~Airplane() = default;

double Airplane::time_in_path() {
    return Passenger_carrier::time_in_path() + 1.5;
}

double Airplane::cost_path() {
    return Passenger_carrier::cost_path() + collections;
}

void Airplane::menu() {
    Passenger_carrier::menu();
    std::cout << "10. Изменить количество пассажиров" << std::endl;
    std::cout << "11. Изменить грузоподъёмность" << std::endl;
    std::cout << "12. Изменить сборы" << std::endl;
    std::cout << "13. Получить количество пассажиров" << std::endl;
    std::cout << "14. Получить грузоподъёмность" << std::endl;
    std::cout << "15. Получить сборы" << std::endl;
}

int Airplane::GetCollections() {
    return collections;
}

int Airplane::GetPassengerCapacity() {
    return passenger_capacity;
}

double Airplane::GetCargoCapacity() {
    return cargo_capacity;
}

void Airplane::SetCollections(int Collections) {
    if (Collections >= 0) {
        collections = Collections;
    } else {
        std::cout << "Ошибка! Сборы должны быть положительным числом." << std::endl;
    }
}

void Airplane::SetPassengerCapacity(int PassengerCapacity) {
    if (PassengerCapacity >= 0) {
        passenger_capacity = PassengerCapacity;
    } else {
        std::cout << "Ошибка! Вместимость пассажиров не может быть отрицательной." << std::endl;
    }
}

void Airplane::SetCargoCapacity(double CargoCapacity) {
    if (CargoCapacity >= 0) {
        cargo_capacity = CargoCapacity;
    } else {
        std::cout << "Ошибка! Грузоподъёмность не может быть отрицательной." << std::endl;
    }
}

std::istream& operator>>(std::istream& is, Airplane& ob) {
    is >> static_cast<Passenger_carrier&>(ob);
    std::cout << "Введите сборы в аэропорту: ";
    is >> ob.collections;
    std::cout << "Введите вместимость пассажиров: ";
    is >> ob.passenger_capacity;
    std::cout << "Введите грузоподъёмность (кг): ";
    is >> ob.cargo_capacity;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& out, Airplane& obj) {
    out << static_cast<Passenger_carrier&>(obj);
    out << std::left
        << std::setw(15) << obj.collections << "| "
        << std::setw(15) << obj.passenger_capacity << "| "
        << std::setw(16) << obj.cargo_capacity << "| ";
    return out;
}

Airplane& Airplane::operator=(const Airplane& other) {
    if (this != &other) {
        Passenger_carrier::operator=(other);
        collections = other.collections;
        passenger_capacity = other.passenger_capacity;
        cargo_capacity = other.cargo_capacity;
    }
    return *this;
}

void Airplane::print_header() const {
    Passenger_carrier::print_header();
    std::cout << std::left
              << std::setw(15) << "Сборы" << "| "
              << std::setw(15) << "Вместимость" << "| "
              << std::setw(16) << "Грузоподъёмность" << "| " << std::endl;
}

void Airplane::print_table() const {
    Passenger_carrier::print_table();
    std::cout << std::left
              << std::setw(15) << collections << "| "
              << std::setw(15) << passenger_capacity << "| "
              << std::setw(16) << cargo_capacity << "| ";
}
