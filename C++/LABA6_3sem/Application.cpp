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
#include "ExceptionHandler.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <fstream>
#include <type_traits>

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

    if (carCount < 0)
        throw InvalidArgumentException("carCount", "Количество не может быть отрицательным");
    
    if (carCount > 10000)
        throw OverflowErrorException("создание массива автомобилей", "Слишком большое количество автомобилей");

    while (carCount < 2)
    {
        cout << "ОШИБКА! Автомобилей должно быть минимум 2.\nПовторите ввод: ";
        cin >> carCount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (carCount < 0)
            throw InvalidArgumentException("carCount", "Количество не может быть отрицательным");
    }

    cout << "Сколько велосипедов создать? ";
    cin >> bicycleCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (bicycleCount < 0)
        throw InvalidArgumentException("bicycleCount", "Количество не может быть отрицательным");
    
    if (bicycleCount > 10000)
        throw OverflowErrorException("создание массива велосипедов", "Слишком большое количество велосипедов");

    cout << "Сколько повозок создать? ";
    cin >> cartCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (cartCount < 0)
        throw InvalidArgumentException("cartCount", "Количество не может быть отрицательным");
    
    if (cartCount > 10000)
        throw OverflowErrorException("создание массива повозок", "Слишком большое количество повозок");
}

void Application::createVehicles()
{
    try
    {
        cars = new Car[carCount];
    }
    catch (const std::bad_alloc&)
    {
        throw BadAllocException(carCount * sizeof(Car));
    }
    
    try
    {
        bicycles = new Bicycle[bicycleCount];
    }
    catch (const std::bad_alloc&)
    {
        if (cars) delete[] cars;
        throw BadAllocException(bicycleCount * sizeof(Bicycle));
    }
    
    try
    {
        carts = new Cart[cartCount];
    }
    catch (const std::bad_alloc&)
    {
        if (cars) delete[] cars;
        if (bicycles) delete[] bicycles;
        throw BadAllocException(cartCount * sizeof(Cart));
    }
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
            if (index < 1 || index > carCount)
                throw OutOfRangeException(index, carCount, "Индекс автомобиля вне допустимого диапазона");
            MenuManager::menu_object(cars[index - 1], carDeque);
            break;

        case 2:
            cout << "Выберите велосипед (1-" << bicycleCount << "): ";
            cin >> index;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index < 1 || index > bicycleCount)
                throw OutOfRangeException(index, bicycleCount, "Индекс велосипеда вне допустимого диапазона");
            MenuManager::menu_object(bicycles[index - 1], bicycleDeque);
            break;

        case 3:
            cout << "Выберите повозку (1-" << cartCount << "): ";
            cin >> index;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index < 1 || index > cartCount)
                throw OutOfRangeException(index, cartCount, "Индекс повозки вне допустимого диапазона");
            MenuManager::menu_object(carts[index - 1], cartDeque);
            break;
    }
}

void Application::cleanup()
{
    if (cars) 
    {
        delete[] cars;
        cars = nullptr;
    }
    if (bicycles) 
    {
        delete[] bicycles;
        bicycles = nullptr;
    }
    if (carts) 
    {
        delete[] carts;
        carts = nullptr;
    }
    carCount = 0;
    bicycleCount = 0;
    cartCount = 0;
    
    // Очищаем деки
    carDeque.clear();
    bicycleDeque.clear();
    cartDeque.clear();
}

bool Application::loadFromFile(const std::string& filename)
{
    try
    {
        std::ifstream file(filename, std::ios::in);
        if (!file.is_open())
        {
            throw FileErrorException(filename, "открытие", "Не удалось открыть файл для чтения");
        }
        
        cleanup(); // Очищаем существующие данные
        
        // Загружаем массивы
        try
        {
            loadArrayFromFile(file, cars, carCount);
            loadArrayFromFile(file, bicycles, bicycleCount);
            loadArrayFromFile(file, carts, cartCount);
            
            // Загружаем деки
            loadDequeFromFile(file, carDeque);
            loadDequeFromFile(file, bicycleDeque);
            loadDequeFromFile(file, cartDeque);
        }
        catch (...)
        {
            cleanup(); // Очищаем частично загруженные данные
            file.close();
            throw;
        }
        
        file.close();
        cout << "Данные успешно загружены из файла: " << filename << "\n";
        return true;
    }
    catch (const FileErrorException& e)
    {
        e.handle();
        cleanup(); // Убеждаемся, что данные очищены
        return false;
    }
    catch (const ExceptionHandler& e)
    {
        e.handle();
        cleanup(); // Убеждаемся, что данные очищены
        return false;
    }
    catch (const std::exception& e)
    {
        FileErrorException fe(filename, "чтение", std::string("Ошибка при чтении файла: ") + e.what());
        fe.handle();
        cleanup(); // Убеждаемся, что данные очищены
        return false;
    }
}

bool Application::saveToFile(const std::string& filename) const
{
    try
    {
        std::ofstream file(filename, std::ios::out | std::ios::trunc);
        if (!file.is_open())
        {
            throw FileErrorException(filename, "открытие", "Не удалось открыть файл для записи");
        }
        
        // Сохраняем массивы
        saveArrayToFile(file, cars, carCount);
        saveArrayToFile(file, bicycles, bicycleCount);
        saveArrayToFile(file, carts, cartCount);
        
        // Сохраняем деки
        saveDequeToFile(file, carDeque);
        saveDequeToFile(file, bicycleDeque);
        saveDequeToFile(file, cartDeque);
        
        file.close();
        cout << "Данные успешно сохранены в файл: " << filename << "\n";
        return true;
    }
    catch (const FileErrorException& e)
    {
        e.handle();
        return false;
    }
    catch (const std::exception& e)
    {
        throw FileErrorException(filename, "запись", std::string("Ошибка при записи файла: ") + e.what());
    }
}

void Application::run()
{
    SetConsoleOutputCP(CP_UTF8);
    
    try
    {
        // Предлагаем загрузить данные из файла или создать новые
        cout << "\n=== ЗАГРУЗКА ДАННЫХ ===\n";
        cout << "1. Загрузить данные из файла\n";
        cout << "2. Создать новые данные\n";
        cout << "Выбор: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        bool dataLoaded = false;
        if (choice == 1)
        {
            cout << "Введите имя файла для загрузки (по умолчанию: data.txt): ";
            string filename;
            getline(cin, filename);
            if (filename.empty())
                filename = "data.txt";
            
            dataLoaded = loadFromFile(filename);
        }
        
        if (!dataLoaded)
        {
            // Создаем новые данные
            inputCounts();
            createVehicles();
            
            fillObjects(cars, carCount, "автомобиля");
            fillObjects(bicycles, bicycleCount, "велосипеда");
            fillObjects(carts, cartCount, "повозки");
            
            initializeDeque(cars, carCount, carDeque);
            initializeDeque(bicycles, bicycleCount, bicycleDeque);
            initializeDeque(carts, cartCount, cartDeque);
        }
        
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
        
        // Предлагаем сохранить данные перед выходом
        cout << "\n=== СОХРАНЕНИЕ ДАННЫХ ===\n";
        cout << "Сохранить данные в файл? (y/n): ";
        char saveChoice;
        cin >> saveChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (saveChoice == 'y' || saveChoice == 'Y')
        {
            cout << "Введите имя файла для сохранения (по умолчанию: data.txt): ";
            string filename;
            getline(cin, filename);
            if (filename.empty())
                filename = "data.txt";
            
            saveToFile(filename);
        }
    }
    catch (const ExceptionHandler& e)
    {
        e.handle();
        throw; // Пробрасываем дальше для обработки в main
    }
}


