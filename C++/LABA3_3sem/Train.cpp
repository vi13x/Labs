#include "Train.h"

Train::Train() : time_stops(0.0), wagon_count(0), train_type("Не указан") {}

Train::Train(double Time_stops,
             int Wagon_count,
             const std::string& Train_type,
             const std::string& Name,
             double Distance,
             double Money_km,
             double Speed)
    : Passenger_carrier(Name, Distance, Money_km, Speed),
      time_stops(Time_stops),
      wagon_count(Wagon_count),
      train_type(Train_type) {}

Train::Train(const Train& other) = default;

Train::~Train() = default;

double Train::time_in_path() {
    return Passenger_carrier::time_in_path() + time_stops;
}

double Train::cost_path() {
    return Passenger_carrier::cost_path();
}

void Train::menu() {
    Passenger_carrier::menu();
    std::cout << "10. Изменить время на остановки" << std::endl;
    std::cout << "11. Получить время на остановки" << std::endl;
    std::cout << "12. Изменить количество вагонов" << std::endl;
    std::cout << "13. Получить количество вагонов" << std::endl;
    std::cout << "14. Изменить тип поезда" << std::endl;
    std::cout << "15. Получить тип поезда" << std::endl;
}

double Train::GetTime_stops() {
    return time_stops;
}

int Train::GetWagon_count() {
    return wagon_count;
}

std::string Train::GetTrain_type() {
    return train_type;
}

void Train::SetTime_stops(double Time_stops) {
    if (Time_stops >= 0) {
        time_stops = Time_stops;
    } else {
        std::cout << "Ошибка!" << std::endl;
    }
}

void Train::SetWagon_count(int Wagon_count) {
    if (Wagon_count >= 0) {
        wagon_count = Wagon_count;
    } else {
        std::cout << "Ошибка!" << std::endl;
    }
}

void Train::SetTrain_type(const std::string& Train_type) {
    if (!Train_type.empty()) {
        train_type = Train_type;
    } else {
        std::cout << "Ошибка!" << std::endl;
    }
}

std::istream& operator>>(std::istream& is, Train& ob) {
    is >> static_cast<Passenger_carrier&>(ob);
    std::cout << "Введите время на остановки: ";
    is >> ob.time_stops;
    std::cout << "Введите количество вагонов: ";
    is >> ob.wagon_count;
    std::cout << "Введите тип поезда: ";
    is >> ob.train_type;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, Train& ob) {
    os << static_cast<Passenger_carrier&>(ob);
    os << std::left
       << std::setw(15) << ob.time_stops << "| "
       << std::setw(15) << ob.wagon_count << "| "
       << std::setw(16) << ob.train_type << "| ";
    return os;
}

Train& Train::operator=(const Train& other) {
    if (this != &other) {
        Passenger_carrier::operator=(other);
        time_stops = other.time_stops;
        wagon_count = other.wagon_count;
        train_type = other.train_type;
    }
    return *this;
}

void Train::print_header() const {
    Passenger_carrier::print_header();
    std::cout << std::left
              << std::setw(15) << "Остановки" << "| "
              << std::setw(15) << "Вагонов" << "| "
              << std::setw(16) << "Тип поезда" << "| " << std::endl;
}

void Train::print_table() const {
    Passenger_carrier::print_table();
    std::cout << std::left
              << std::setw(15) << time_stops << "| "
              << std::setw(15) << wagon_count << "| "
              << std::setw(16) << train_type << "| ";
}
