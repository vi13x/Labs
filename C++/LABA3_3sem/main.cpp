#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

#include "TransportVehicle.h"
#include "Car.h"
#include "Bicycle.h"
#include "Cart.h"

using namespace std;

namespace {
const char* TABLE_FOOTER =
    "+----+------------+----------------------+------------+----------+--------------------+---------------+---------+\n";

void printVehiclesTable(const vector<TransportVehicle*>& vehicles) {
    if (vehicles.empty()) {
        cout << "Нет объектов для отображения." << endl;
        return;
    }

    vehicles.front()->printHeader();
    for (size_t i = 0; i < vehicles.size(); ++i) {
        cout << "| " << setw(2) << left << i + 1;
        vehicles[i]->printTable();
    }
    cout << TABLE_FOOTER;
}

void printSingleVehicle(TransportVehicle& vehicle) {
    vector<TransportVehicle*> single{ &vehicle };
    printVehiclesTable(single);
}

void menu_vehicle(TransportVehicle& vehicle) {
    while (true) {
        cout << "\n=============МЕНЮ============" << endl;
        cout << "0. Выйти" << endl;
        cout << "1. Вывести объект" << endl;
        cout << "2. Изменить название" << endl;
        cout << "3. Изменить расстояние" << endl;
        cout << "4. Изменить скорость" << endl;
        cout << "5. Изменить стоимость за км (пассажиры)" << endl;
        cout << "6. Изменить стоимость за км (груз)" << endl;
        cout << "7. Получить название" << endl;
        cout << "8. Получить расстояние" << endl;
        cout << "9. Получить скорость" << endl;
        cout << "10. Получить стоимость за км (пассажиры)" << endl;
        cout << "11. Получить стоимость за км (груз)" << endl;
        cout << "12. Расчет пассажирской перевозки" << endl;
        cout << "13. Расчет грузовой перевозки" << endl;
        cout << "Выбор: ";

        int choice;
        if (!(cin >> choice)) {
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 0:
                return;
            case 1:
                printSingleVehicle(vehicle);
                cout << endl;
                break;
            case 2: {
                cout << "Введите новое название: ";
                string newName;
                getline(cin, newName);
                vehicle.set_name(newName);
                cout << "Название обновлено." << endl;
                break;
            }
            case 3: {
                cout << "Введите новое расстояние (км): ";
                double value;
                cin >> value;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                vehicle.set_distance_km(value);
                cout << "Расстояние обновлено." << endl;
                break;
            }
            case 4: {
                cout << "Введите новую скорость (км/ч): ";
                double value;
                cin >> value;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                vehicle.set_speed_kmh(value);
                cout << "Скорость обновлена." << endl;
                break;
            }
            case 5: {
                cout << "Введите новую стоимость за км для пассажиров: ";
                double value;
                cin >> value;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                vehicle.set_passenger_rate_per_km(value);
                cout << "Стоимость обновлена." << endl;
                break;
            }
            case 6: {
                cout << "Введите новую стоимость за км для груза: ";
                double value;
                cin >> value;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                vehicle.set_cargo_rate_per_km_per_kg(value);
                cout << "Стоимость обновлена." << endl;
                break;
            }
            case 7:
                cout << "Название: " << vehicle.get_name() << endl;
                break;
            case 8:
                cout << "Расстояние (км): " << vehicle.get_distance_km() << endl;
                break;
            case 9:
                cout << "Скорость (км/ч): " << vehicle.get_speed_kmh() << endl;
                break;
            case 10:
                cout << "Стоимость за км (пассажиры): " << vehicle.get_passenger_rate_per_km() << endl;
                break;
            case 11:
                cout << "Стоимость за км (груз): " << vehicle.get_cargo_rate_per_km_per_kg() << endl;
                break;
            case 12: {
                cout << "Введите количество пассажиров: ";
                int passengers;
                cin >> passengers;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                vehicle.input_info_passengers(passengers);
                break;
            }
            case 13: {
                cout << "Введите вес груза (кг): ";
                double cargoWeight;
                cin >> cargoWeight;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                vehicle.input_info_cargo(cargoWeight);
                break;
            }
            default:
                cout << "Неверный пункт меню." << endl;
                break;
        }
    }
}

template <typename T>
void inputVehicle(T& vehicle, const string& prompt) {
    cout << prompt << endl;
    cin >> vehicle;
    cout << endl;
}
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "ru_RU.UTF-8");

    Car car;
    Bicycle bicycle;
    Cart cart;

    inputVehicle(car, "Введите данные для автомобиля:");
    inputVehicle(bicycle, "Введите данные для велосипеда:");
    inputVehicle(cart, "Введите данные для повозки:");

    vector<TransportVehicle*> vehicles{ &car, &bicycle, &cart };

    cout << setw(70) << "=== ТРАНСПОРТНЫЕ СРЕДСТВА ===" << endl;
    printVehiclesTable(vehicles);

    cout << endl << "=== ПРОВЕРКА ПЕРЕГРУЗОК ВЫВОДА ===" << endl;
    cout << car << endl;
    cout << bicycle << endl;
    cout << cart << endl;

    cout << endl << "=== РАСЧЕТ ВРЕМЕНИ И СТОИМОСТИ ===" << endl;
    cout << "Введите количество пассажиров для расчета: ";
    int passengers = 0;
    cin >> passengers;
    cout << "Введите вес груза (кг) для расчета: ";
    double cargoWeight = 0.0;
    cin >> cargoWeight;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;

    for (TransportVehicle* vehicle : vehicles) {
        ios::fmtflags oldFlags = cout.flags();
        streamsize oldPrecision = cout.precision();

        cout << vehicle->type_name() << " \"" << vehicle->get_name() << "\" - время: "
             << fixed << setprecision(2) << vehicle->time_in_path_hours()
             << " ч, стоимость (пассажиры): " << vehicle->cost_passengers(passengers)
             << " руб, стоимость (груз): " << vehicle->cost_cargo(cargoWeight) << " руб" << endl;

        cout.flags(oldFlags);
        cout.precision(oldPrecision);
    }

    cout << endl << "=== МЕНЮ УПРАВЛЕНИЯ ДЛЯ " << cart.type_name() << " ===" << endl;
    menu_vehicle(cart);

    cout << "Работа программы завершена." << endl;
    return 0;
}
