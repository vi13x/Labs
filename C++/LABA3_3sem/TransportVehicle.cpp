#include "TransportVehicle.h"
#include <iostream>
#include <iomanip>

TransportVehicle::TransportVehicle() = default;

TransportVehicle::TransportVehicle(std::string name,
                                   double distanceKm,
                                   double speedKmh,
                                   double passengerRatePerKm,
                                   double cargoRatePerKmPerKg)
        : name(std::move(name)),
          distanceKm(distanceKm),
          speedKmh(speedKmh),
          passengerRatePerKm(passengerRatePerKm),
          cargoRatePerKmPerKg(cargoRatePerKmPerKg) {}

TransportVehicle::~TransportVehicle() = default;

TransportVehicle* TransportVehicle::clone() const {
    return new TransportVehicle(*this);
}

std::string TransportVehicle::type_name() const {
    return "Vehicle";
}

double TransportVehicle::time_in_path_hours() const {
    if (speedKmh <= 0.0) return 0.0;
    return distanceKm / speedKmh;
}

double TransportVehicle::cost_passengers(int numPassengers) const {
    if (numPassengers <= 0) return 0.0;
    return distanceKm * passengerRatePerKm * static_cast<double>(numPassengers);
}

double TransportVehicle::cost_cargo(double weightKg) const {
    if (weightKg <= 0.0) return 0.0;
    return distanceKm * cargoRatePerKmPerKg * weightKg;
}

void TransportVehicle::input_info() {
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter distance (км): ";
    std::cin >> distanceKm;
    std::cout << "Enter speed (км/ч): ";
    std::cin >> speedKmh;
    std::cout << "Enter cost per km (пассажир): ";
    std::cin >> passengerRatePerKm;
    std::cout << "Enter cost per km (кг груза): ";
    std::cin >> cargoRatePerKmPerKg;
}

void TransportVehicle::input_info_passengers(int numPassengers) const {
    std::cout << std::setw(25) << "Name: " << std::setw(15) << name << std::endl;
    std::cout << std::setw(25) << "Distance: " << std::setw(15) << distanceKm << " км" << std::endl;
    std::cout << std::setw(25) << "Cost per km:" << std::setw(15) << passengerRatePerKm << " руб/пасс" << std::endl;
    std::cout << std::setw(25) << "Speed: " << std::setw(15) << speedKmh << " км/ч" << std::endl;
    std::cout << std::setw(25) << "Passengers: " << std::setw(15) << numPassengers << std::endl;
    std::cout << std::setw(25) << "Cost of the all trip: " << std::setw(15)
              << std::fixed << std::setprecision(2) << cost_passengers(numPassengers) << " руб" << std::endl;
    std::cout << std::setw(25) << "Time in trip:" << std::setw(15)
              << std::fixed << std::setprecision(2) << time_in_path_hours() << " ч" << std::endl;
}

void TransportVehicle::input_info_cargo(double weightKg) const {
    std::cout << std::setw(25) << "Name: " << std::setw(15) << name << std::endl;
    std::cout << std::setw(25) << "Distance: " << std::setw(15) << distanceKm << " км" << std::endl;
    std::cout << std::setw(25) << "Cost per km:" << std::setw(15) << cargoRatePerKmPerKg << " руб/кг" << std::endl;
    std::cout << std::setw(25) << "Speed: " << std::setw(15) << speedKmh << " км/ч" << std::endl;
    std::cout << std::setw(25) << "Cargo weight: " << std::setw(15) << weightKg << " кг" << std::endl;
    std::cout << std::setw(25) << "Cost of the all trip: " << std::setw(15)
              << std::fixed << std::setprecision(2) << cost_cargo(weightKg) << " руб" << std::endl;
    std::cout << std::setw(25) << "Time in trip:" << std::setw(15)
              << std::fixed << std::setprecision(2) << time_in_path_hours() << " ч" << std::endl;
}

void TransportVehicle::printHeader() {
    std::cout << std::left
              << std::setw(5)  << "#"
              << std::setw(12) << "Type"
              << std::setw(20) << "Name"
              << std::setw(12) << "Distance"
              << std::setw(10) << "Speed"
              << std::setw(20) << "Price/km(pass)"
              << std::setw(15) << "Price/km(kg)"
              << std::setw(10) << "Time"
              << std::endl;

    std::cout << std::setfill('-') << std::setw(104) << "-" << std::setfill(' ') << std::endl;
}

void TransportVehicle::printTable() {
    std::cout << std::left
              << std::setw(5)  << ""
              << std::setw(12) << type_name()
              << std::setw(20) << name
              << std::setw(12) << std::fixed << std::setprecision(2) << distanceKm
              << std::setw(10) << std::fixed << std::setprecision(2) << speedKmh
              << std::setw(20) << std::fixed << std::setprecision(2) << passengerRatePerKm
              << std::setw(15) << std::fixed << std::setprecision(2) << cargoRatePerKmPerKg
              << std::setw(10) << std::fixed << std::setprecision(2) << time_in_path_hours()
              << std::endl;
}

void TransportVehicle::display(int index) {
    // Если это первый объект, выводим шапку таблицы
    if (index == 0) {
        std::cout << "\n" << std::setfill('=') << std::setw(120) << "=" << std::setfill(' ') << std::endl;
        std::cout << "                 TRANSPORT VEHICLES" << std::endl;
        std::cout << std::setfill('=') << std::setw(120) << "=" << std::setfill(' ') << std::endl;
        printHeader();
        std::cout << std::setfill('-') << std::setw(120) << "-" << std::setfill(' ') << std::endl;
    }
    // Выводим данные объекта
    std::cout << std::setw(4) << (index + 1);
    printTable();
}


std::ostream& operator<<(std::ostream& os, const TransportVehicle& vehicle) {
    os << vehicle.type_name() << " - " << vehicle.get_name();
    return os;
}

std::istream& operator>>(std::istream& is, TransportVehicle& vehicle) {
    vehicle.input_info();
    return is;
}
