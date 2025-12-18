#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#undef byte
#include "Application.h"
#include "MenuManager.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

Application::Application() : carCount(0), bicycleCount(0), cartCount(0), cars(nullptr), bicycles(nullptr), carts(nullptr)
{
}

Application::~Application()
{
    cleanup();
}

void Application::inputCounts()
{
    cout << "Сколько автомобилей создать? (минимум 2): ";
    cin >> carCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (carCount < 2)
    {
        cout << "ОШИБКА! Автомобилей должно быть минимум 2.\nПовторите ввод: ";
        cin >> carCount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Сколько велосипедов создать? ";
    cin >> bicycleCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Сколько повозок создать? ";
    cin >> cartCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Application::createVehicles()
{
    cars = new Car[carCount];
    bicycles = new Bicycle[bicycleCount];
    carts = new Cart[cartCount];
}

void Application::selectAndEditVehicle()
{
    cout << "\nВыберите тип транспорта для редактирования:\n";
    cout << "1 — Автомобили\n2 — Велосипеды\n3 — Повозки\n0 — Выход\n";
    int type;
    cin >> type;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (type == 0)
    {
        return;
    }

    int index;
    switch (type)
    {
        case 1:
            cout << "Выберите автомобиль (1-" << carCount << "): ";
            cin >> index;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index >= 1 && index <= carCount)
                MenuManager::menu_object(cars[index - 1], carDeque);
            break;

        case 2:
            cout << "Выберите велосипед (1-" << bicycleCount << "): ";
            cin >> index;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index >= 1 && index <= bicycleCount)
                MenuManager::menu_object(bicycles[index - 1], bicycleDeque);
            break;

        case 3:
            cout << "Выберите повозку (1-" << cartCount << "): ";
            cin >> index;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index >= 1 && index <= cartCount)
                MenuManager::menu_object(carts[index - 1], cartDeque);
            break;
    }
}

void Application::cleanup()
{
    if (cars) delete[] cars;
    if (bicycles) delete[] bicycles;
    if (carts) delete[] carts;
}

void Application::run()
{
    SetConsoleOutputCP(CP_UTF8);
    inputCounts();
    createVehicles();
    
    fillObjects(cars, carCount, "автомобиля");
    fillObjects(bicycles, bicycleCount, "велосипеда");
    fillObjects(carts, cartCount, "повозки");
    
    initializeDeque(cars, carCount, carDeque);
    initializeDeque(bicycles, bicycleCount, bicycleDeque);
    initializeDeque(carts, cartCount, cartDeque);
    
    cout << "\n\n===== ВСЕ ТРАНСПОРТЫ =====\n";
    
    string carHeader = "+----+----------+----------+----------+----------+----------+----------+\n"
                       "| №  | Название | Расстояние| Скорость | Цена/км  | Цена/км | Время    |\n"
                       "|    |          |           |          | пасс     | кг      |          |\n"
                       "+----+----------+----------+----------+----------+----------+----------+";
    
    string bicycleHeader = "+----+----------+----------+----------+----------+----------+----------+\n"
                           "| №  | Название | Расстояние| Скорость | Цена/км  | Цена/км | Время    |\n"
                           "|    |          |           |          | пасс     | кг      |          |\n"
                           "+----+----------+----------+----------+----------+----------+----------+";
    
    string cartHeader = "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+\n"
                        "| №  | Тип           | Название| Расстояние| Скорость       | Цена/км  | Цена/км  | Время          | Лошадей     | Тип повозки | Часов с корм.  |\n"
                        "|    |               |         |           |                | пасс     | кг       |                |             |             |                |\n"
                        "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+";
    
    printObjects(cars, carCount, "Автомобили", carHeader);
    printObjects(bicycles, bicycleCount, "Велосипеды", bicycleHeader);
    printObjects(carts, cartCount, "Повозки", cartHeader);
    
    selectAndEditVehicle();
}

