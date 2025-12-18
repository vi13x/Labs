#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "Car.h"
#include "Bicycle.h"
#include "Cart.h"
#include <windows.h>

using namespace std;

void menu_vehicle(TransportVehicle& t)
{
    while (true)
    {
        t.menu();
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 0:
                return;

            case 1:
                cout << "\nТЕКУЩИЕ ДАННЫЕ:\n";
                cout << t << endl;
                t.print_separator();
                cout << endl;
                break;

            case 2:
            {
                string n;
                cout << "Введите новое название: ";
                getline(cin, n);
                t.SetName(n);
                cout << endl;
                break;
            }

            case 3:
            {
                double d;
                cout << "Введите новое расстояние: ";
                cin >> d;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                t.SetDistance(d);
                cout << endl;
                break;
            }

            case 4:
            {
                double p;
                cout << "Введите новую цену за км (пассажиры): ";
                cin >> p;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                t.SetPassengerRate(p);
                cout << endl;
                break;
            }

            case 5:
            {
                double c;
                cout << "Введите новую цену за км груза (кг): ";
                cin >> c;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                t.SetCargoRate(c);
                cout << endl;
                break;
            }

            case 6:
            {
                double v;
                cout << "Введите новую скорость: ";
                cin >> v;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                t.SetSpeed(v);
                cout << endl;
                break;
            }

            case 7:
                cout << "Название: " << t.GetName() << endl << endl;
                break;

            case 8:
                cout << "Расстояние: " << t.GetDistance() << endl << endl;
                break;

            case 9:
                cout << "Цена/км пассажиров: " << t.GetPassengerRate() << endl << endl;
                break;

            case 10:
                cout << "Цена/км груза: " << t.GetCargoRate() << endl << endl;
                break;

            case 11:
                cout << "Скорость: " << t.GetSpeed() << endl << endl;
                break;

            case 12:
            {
                int people;
                cout << "Введите количество пассажиров: ";
                cin >> people;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Стоимость: " << t.cost_passengers(people) << endl;
                cout << "Время: " << t.time_in_path() << " ч" << endl << endl;
                break;
            }

            case 13:
            {
                double kg;
                cout << "Введите массу груза (кг): ";
                cin >> kg;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Стоимость: " << t.cost_cargo(kg) << endl;
                cout << "Время: " << t.time_in_path() << " ч" << endl << endl;
                break;
            }
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int carCount;
    cout << "Сколько автомобилей создать? (минимум 2): ";
    cin >> carCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (carCount < 2)
    {
        cout << "ОШИБКА! Автомобилей должно быть минимум 2.\nПовторите ввод: ";
        cin >> carCount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int bicycleCount;
    cout << "Сколько велосипедов создать? ";
    cin >> bicycleCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int cartCount;
    cout << "Сколько повозок создать? ";
    cin >> cartCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    Car* cars = new Car[carCount];
    Bicycle* bicycles = new Bicycle[bicycleCount];
    Cart* carts = new Cart[cartCount];


    for (int i = 0; i < carCount; i++)
    {
        cout << "\nВведите данные автомобиля #" << i + 1 << ":\n";
        cin >> cars[i];
    }

    for (int i = 0; i < bicycleCount; i++)
    {
        cout << "\nВведите данные велосипеда #" << i + 1 << ":\n";
        cin >> bicycles[i];
    }

    for (int i = 0; i < cartCount; i++)
    {
        cout << "\nВведите данные повозки #" << i + 1 << ":\n";
        cin >> carts[i];
    }



    cout << "\n\n===== ВСЕ ТРАНСПОРТЫ =====\n";

    if (carCount > 0)
    {
        cout << "\n-- Автомобили --\n";
        cars[0].print_header();
        for (int i = 0; i < carCount; i++)
        {
            cout << "| " << setw(2) << right << (i + 1) << " | ";
            cout << cars[i] << endl;
        }
        cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
    }

    if (bicycleCount > 0)
    {
        cout << "\n-- Велосипеды --\n";
        bicycles[0].print_header();
        for (int i = 0; i < bicycleCount; i++)
        {
            cout << "| " << setw(2) << right << (i + 1) << " | ";
            cout << bicycles[i] << endl;
        }
        cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
    }

    if (cartCount > 0)
    {
        cout << "\n-- Повозки --\n";
        carts[0].print_header();
        for (int i = 0; i < cartCount; i++)
        {
            cout << "| " << setw(2) << right << (i + 1) << " | ";
            cout << carts[i] << endl;
        }
        cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
    }



    cout << "\nВыберите тип транспорта для редактирования:\n";
    cout << "1 — Автомобили\n2 — Велосипеды\n3 — Повозки\n0 — Выход\n";
    int type;
    cin >> type;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (type == 0)
    {
        delete[] cars;
        delete[] bicycles;
        delete[] carts;
        return 0;
    }

    int index;
    switch (type)
    {
        case 1:
            cout << "Выберите автомобиль (1-" << carCount << "): ";
            cin >> index;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index >= 1 && index <= carCount)
                menu_vehicle(cars[index - 1]);
            break;

        case 2:
            cout << "Выберите велосипед (1-" << bicycleCount << "): ";
            cin >> index;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index >= 1 && index <= bicycleCount)
                menu_vehicle(bicycles[index - 1]);
            break;

        case 3:
            cout << "Выберите повозку (1-" << cartCount << "): ";
            cin >> index;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index >= 1 && index <= cartCount)
                menu_vehicle(carts[index - 1]);
            break;
    }



    delete[] cars;
    delete[] bicycles;
    delete[] carts;

    return 0;
}