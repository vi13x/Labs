#include <iostream>
#include <iomanip>
#include <limits>
#include <windows.h>

#include "TransportVehicle.h"
#include "Car.h"
#include "Bicycle.h"
#include "Cart.h"
#include "Deque.h"

using namespace std;

const int MAX_OBJECTS = 10;

// Хранилище всех транспортных средств — шаблонный дек
Deque<TransportVehicle*> vehicleDeque;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu() {
    const int width = 60;

    cout << "\n " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;

    string title = "TRANSPORT VEHICLE MANAGEMENT SYSTEM";
    int padding = (width - 2 - (int)title.length()) / 2;
    cout << " |" << setw(padding) << " " << title
         << setw(width - 2 - padding - (int)title.length()) << " " << "|" << endl;

    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;

    cout << " |  1. Add Transport Vehicle" << setw(width - 28) << " " << "|" << endl;
    cout << " |  2. Show All" << setw(width - 15) << " " << "|" << endl;
    cout << " |  3. Edit Transport Vehicle" << setw(width - 29) << " " << "|" << endl;
    cout << " |  4. Delete Transport Vehicle" << setw(width - 31) << " " << "|" << endl;
    cout << " |  5. Calculate Cost and Time" << setw(width - 30) << " " << "|" << endl;
    cout << " |  6. Find by name" << setw(width - 21) << " " << "  |" << endl;
    cout << " |  7. Sort by name" << setw(width - 21) << " " << "  |" << endl;
    cout << " |  0. Exit" << setw(width - 11) << " " << "|" << endl;

    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
    cout << " Select option: ";
}

void addObject() {
    if (vehicleDeque.size() >= MAX_OBJECTS) {
        cout << "Cannot add more objects! Maximum reached.\n";
        return;
    }

    cout << "Select vehicle type:\n";
    cout << "1. Car\n";
    cout << "2. Bicycle\n";
    cout << "3. Cart\n";
    cout << "Choice: ";
    int type;
    cin >> type;
    clearInput();

    TransportVehicle* newObject = nullptr;

    switch (type) {
        case 1:
            newObject = new Car;
            break;
        case 2:
            newObject = new Bicycle;
            break;
        case 3:
            newObject = new Cart;
            break;
        default:
            cout << "Invalid type selection.\n";
            return;
    }

    // Вызовется базовый operator>> (TransportVehicle&),
    // который дернёт виртуальный input_info() (Car/Bicycle/Cart)
    cin >> *newObject;

    vehicleDeque.push_back(newObject);
    cout << "Transport Vehicle added successfully!\n";
}

void showAll() {
    if (!vehicleDeque.empty()) {
        for (std::size_t i = 0; i < vehicleDeque.size(); ++i) {
            vehicleDeque[i]->display(static_cast<int>(i));
        }
        cout << "+----+------------+----------------------+------------+----------+--------------------+---------------+----------+\n";
    } else {
        cout << "\nNo Transport Vehicles found.\n";
    }
}

void editObject() {
    if (vehicleDeque.empty()) {
        cout << "No objects to edit.\n";
        return;
    }

    cout << "\nAvailable Transport Vehicles:\n";
    for (std::size_t i = 0; i < vehicleDeque.size(); i++) {
        cout << i + 1 << ". " << *vehicleDeque[i] << endl;
    }

    cout << "Select object to edit: ";
    int index;
    cin >> index;
    clearInput();

    if (index < 1 || static_cast<std::size_t>(index) > vehicleDeque.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    TransportVehicle& obj = *vehicleDeque[index - 1];

    cout << "Current data: " << obj << endl;
    cout << "Enter new data:\n";
    cin >> obj;

    cout << "Object updated successfully!\n";
}

void deleteObject() {
    if (vehicleDeque.empty()) {
        cout << "No objects to delete.\n";
        return;
    }

    cout << "\nAvailable Transport Vehicles:\n";
    for (std::size_t i = 0; i < vehicleDeque.size(); i++) {
        cout << i + 1 << ". " << *vehicleDeque[i] << endl;
    }

    cout << "Select object to delete: ";
    int index;
    cin >> index;
    clearInput();

    if (index < 1 || static_cast<std::size_t>(index) > vehicleDeque.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    std::size_t idx = static_cast<std::size_t>(index) - 1;
    cout << "Deleting: " << *vehicleDeque[idx] << endl;

    delete vehicleDeque[idx];   // освобождаем память объекта
    vehicleDeque.erase(idx);    // удаляем указатель из дека

    cout << "Object deleted successfully!\n";
}

void calculateCosts() {
    if (vehicleDeque.empty()) {
        cout << "No objects to calculate.\n";
        return;
    }

    cout << "\nAvailable Transport Vehicles:\n";
    for (std::size_t i = 0; i < vehicleDeque.size(); i++) {
        cout << i + 1 << ". " << *vehicleDeque[i] << endl;
    }

    cout << "Select object for calculation: ";
    int index;
    cin >> index;
    clearInput();

    if (index < 1 || static_cast<std::size_t>(index) > vehicleDeque.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    TransportVehicle& obj = *vehicleDeque[index - 1];

    cout << "Enter number of passengers: ";
    int passengers;
    cin >> passengers;
    clearInput();

    cout << "Enter cargo weight (kg): ";
    double cargo;
    cin >> cargo;
    clearInput();

    cout << "\nCalculation Results:\n";
    cout << "Passenger Transport:\n";
    obj.input_info_passengers(passengers);
    cout << "\nCargo Transport:\n";
    obj.input_info_cargo(cargo);
}

// Поиск по имени (используем operator== в TransportVehicle)
void findByName() {
    if (vehicleDeque.empty()) {
        cout << "No objects to search.\n";
        return;
    }

    cout << "Enter name to search: ";
    std::string name;
    std::getline(cin, name);

    TransportVehicle pattern;
    pattern.set_name(name);

    bool found = false;
    for (std::size_t i = 0; i < vehicleDeque.size(); ++i) {
        if (*vehicleDeque[i] == pattern) {   // operator==
            cout << "Found at position " << (i + 1) << ": " << *vehicleDeque[i] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No TransportVehicle with name \"" << name << "\" found.\n";
    }
}

// Сортировка по имени (простая пузырьковая)
void sortByName() {
    if (vehicleDeque.size() < 2) {
        cout << "Not enough objects to sort.\n";
        return;
    }

    std::size_t n = vehicleDeque.size();
    for (std::size_t i = 0; i + 1 < n; ++i) {
        for (std::size_t j = 0; j + 1 < n - i; ++j) {
            if (vehicleDeque[j]->get_name() > vehicleDeque[j + 1]->get_name()) {
                std::swap(vehicleDeque[j], vehicleDeque[j + 1]);
            }
        }
    }

    cout << "Sorted by name.\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int choice;

    do {
        printMenu();
        cin >> choice;
        clearInput();

        switch (choice) {
            case 1:
                addObject();
                break;
            case 2:
                showAll();
                break;
            case 3:
                editObject();
                break;
            case 4:
                deleteObject();
                break;
            case 5:
                calculateCosts();
                break;
            case 6:
                findByName();
                break;
            case 7:
                sortByName();
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid option!\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    // Освобождаем память всех оставшихся объектов
    for (std::size_t i = 0; i < vehicleDeque.size(); ++i) {
        delete vehicleDeque[i];
    }
    vehicleDeque.clear();

    return 0;
}
