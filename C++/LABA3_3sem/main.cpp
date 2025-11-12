#include <iostream>
#include <iomanip>
#include <limits>
#include <windows.h>

#include "TransportVehicle.h"
#include "Car.h"
#include "Bicycle.h"
#include "Cart.h"

using namespace std;

const int MAX_OBJECTS = 10;
TransportVehicle* objects[MAX_OBJECTS];
int objectCount = 0;

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
    cout << " |  0. Exit" << setw(width - 11) << " " << "|" << endl;

    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
    cout << " Select option: ";
}

void addObject() {
    if (objectCount >= MAX_OBJECTS) {
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

    // Вызовется operator>> из базового класса,
    // который дернёт виртуальную input_info(),
    // а там уже свои "[Car] Input data:" / "[Bicycle] ..." и т.п.
    cin >> *newObject;

    objects[objectCount] = newObject;
    objectCount++;
    cout << "Transport Vehicle added successfully!\n";
}

void showAll() {
    if (objectCount > 0) {
        std::cout << "\nALL TRANSPORT VEHICLES\n";
        objects[0]->printHeader();

        for (int i = 0; i < objectCount; i++) {
            std::cout << "| " << std::setw(2) << std::left << i + 1;
            objects[i]->printTable();
        }

        // Закрывающая линия таблицы
        std::cout << "+----+------------+----------------------+------------+----------+--------------------+---------------+----------+\n";
    } else {
        std::cout << "\nNo Transport Vehicles found.\n";
    }
}

void editObject() {
    if (objectCount == 0) {
        cout << "No objects to edit.\n";
        return;
    }

    cout << "\nAvailable Transport Vehicles:\n";
    for (int i = 0; i < objectCount; i++) {
        cout << i + 1 << ". " << *objects[i] << endl;
    }

    cout << "Select object to edit: ";
    int index;
    cin >> index;
    clearInput();

    if (index < 1 || index > objectCount) {
        cout << "Invalid selection.\n";
        return;
    }

    TransportVehicle& obj = *objects[index - 1];

    cout << "Current data: " << obj << endl;
    cout << "Enter new data:\n";
    cin >> obj;

    cout << "Object updated successfully!\n";
}

void deleteObject() {
    if (objectCount == 0) {
        cout << "No objects to delete.\n";
        return;
    }

    cout << "\nAvailable Transport Vehicles:\n";
    for (int i = 0; i < objectCount; i++) {
        cout << i + 1 << ". " << *objects[i] << endl;
    }

    cout << "Select object to delete: ";
    int index;
    cin >> index;
    clearInput();

    if (index < 1 || index > objectCount) {
        cout << "Invalid selection.\n";
        return;
    }

    cout << "Deleting: " << *objects[index - 1] << endl;

    delete objects[index - 1];

    for (int i = index - 1; i < objectCount - 1; i++) {
        objects[i] = objects[i + 1];
    }
    objectCount--;

    cout << "Object deleted successfully!\n";
}

void calculateCosts() {
    if (objectCount == 0) {
        cout << "No objects to calculate.\n";
        return;
    }

    cout << "\nAvailable Transport Vehicles:\n";
    for (int i = 0; i < objectCount; i++) {
        cout << i + 1 << ". " << *objects[i] << endl;
    }

    cout << "Select object for calculation: ";
    int index;
    cin >> index;
    clearInput();

    if (index < 1 || index > objectCount) {
        cout << "Invalid selection.\n";
        return;
    }

    TransportVehicle& obj = *objects[index - 1];

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

    // Очистка
    for (int i = 0; i < objectCount; i++) {
        delete objects[i];
    }

    return 0;
}
