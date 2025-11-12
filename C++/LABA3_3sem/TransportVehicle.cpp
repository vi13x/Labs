#include "TransportVehicle.h"
#include <limits>

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
    std::getline(std::cin >> std::ws, name);
    std::cout << "Enter distance (km): ";
    std::cin >> distanceKm;
    std::cout << "Enter speed (km/h): ";
    std::cin >> speedKmh;
    std::cout << "Enter cost per km (passenger): ";
    std::cin >> passengerRatePerKm;
    std::cout << "Enter cost per km (kg of cargo): ";
    std::cin >> cargoRatePerKmPerKg;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void TransportVehicle::input_info_passengers(int numPassengers) const {
    std::cout << std::setw(25) << "Name: " << std::setw(15) << name << std::endl;
    std::cout << std::setw(25) << "Distance: " << std::setw(15) << distanceKm << " km" << std::endl;
    std::cout << std::setw(25) << "Cost per km:" << std::setw(15) << passengerRatePerKm << " per passenger" << std::endl;
    std::cout << std::setw(25) << "Speed: " << std::setw(15) << speedKmh << " km/h" << std::endl;
    std::cout << std::setw(25) << "Passengers: " << std::setw(15) << numPassengers << std::endl;
    std::cout << std::setw(25) << "Total cost: " << std::setw(15)
              << std::fixed << std::setprecision(2) << cost_passengers(numPassengers) << std::endl;
    std::cout << std::setw(25) << "Time in trip:" << std::setw(15)
              << std::fixed << std::setprecision(2) << time_in_path_hours() << " h" << std::endl;
}

void TransportVehicle::input_info_cargo(double weightKg) const {
    std::cout << std::setw(25) << "Name: " << std::setw(15) << name << std::endl;
    std::cout << std::setw(25) << "Distance: " << std::setw(15) << distanceKm << " km" << std::endl;
    std::cout << std::setw(25) << "Cost per km:" << std::setw(15) << cargoRatePerKmPerKg << " per kg" << std::endl;
    std::cout << std::setw(25) << "Speed: " << std::setw(15) << speedKmh << " km/h" << std::endl;
    std::cout << std::setw(25) << "Cargo weight: " << std::setw(15) << weightKg << " kg" << std::endl;
    std::cout << std::setw(25) << "Total cost: " << std::setw(15)
              << std::fixed << std::setprecision(2) << cost_cargo(weightKg) << std::endl;
    std::cout << std::setw(25) << "Time in trip:" << std::setw(15)
              << std::fixed << std::setprecision(2) << time_in_path_hours() << " h" << std::endl;
}

void TransportVehicle::printHeader() {
    std::cout << "+----+------------+----------------------+------------+----------+--------------------+---------------+----------+\n";
    std::cout << "| #  | Type       | Name                 |   Distance |   Speed  |   Price/km(pass.)  |  Price/km(kg) |   Time   |\n";
    std::cout << "+----+------------+----------------------+------------+----------+--------------------+---------------+----------+\n";
}

void TransportVehicle::printTable() {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);

    std::cout << "" << std::setw(1) << std::left << " "
              << "|" << std::setw(12) << std::left << type_name()
              << "| " << std::setw(20) << std::left << name
              << " | " << std::setw(10) << std::right << distanceKm
              << " | " << std::setw(8)  << std::right << speedKmh
              << " | " << std::setw(18) << std::right << passengerRatePerKm
              << " | " << std::setw(13) << std::right << cargoRatePerKmPerKg
              << " | " << std::setw(8)  << std::right << time_in_path_hours()
              << " |\n";
}

void TransportVehicle::display(int index) {
    if (index == 0) {
        std::cout << "\nALL TRANSPORT VEHICLES\n";
        printHeader();
    }

    std::cout << "| " << std::setw(2) << std::left << index + 1;
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