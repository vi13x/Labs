#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <type_traits>
#include "Car.h"
#include "Bicycle.h"
#include "Cart.h"
#include "Deque.hpp"
#include "ExceptionHandler.h"

using namespace std;

class Application
{
private:
    int carCount;
    int bicycleCount;
    int cartCount;
    Car* cars;
    Bicycle* bicycles;
    Cart* carts;
    Deque<Car> carDeque;
    Deque<Bicycle> bicycleDeque;
    Deque<Cart> cartDeque;

    void inputCounts();
    void createVehicles();
    
    template<typename T>
    void fillObjects(T* objects, int count, const std::string& typeName);
    
    template<typename T>
    void initializeDeque(T* objects, int count, Deque<T>& deque);
    
    template<typename T>
    void printObjects(T* objects, int count, const std::string& typeName, const std::string& header);
    
    void selectAndEditVehicle();
    void cleanup();
    
    // Методы для работы с файлами
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    
    template<typename T>
    void saveArrayToFile(std::ofstream& file, T* objects, int count) const;
    
    template<typename T>
    void loadArrayFromFile(std::ifstream& file, T*& objects, int& count);
    
    template<typename T>
    void saveDequeToFile(std::ofstream& file, const Deque<T>& deque) const;
    
    template<typename T>
    void loadDequeFromFile(std::ifstream& file, Deque<T>& deque);

public:
    Application();
    ~Application();
    void run();
};

// Реализация шаблонных методов
template<typename T>
void Application::fillObjects(T* objects, int count, const string& typeName)
{
    for (int i = 0; i < count; i++)
    {
        cout << "\nВведите данные " << typeName << " #" << i + 1 << ":\n";
        cin >> objects[i];
    }
}

template<typename T>
void Application::initializeDeque(T* objects, int count, Deque<T>& deque)
{
    for (int i = 0; i < count; i++)
    {
        deque.push_back(objects[i]);
    }
}

template<typename T>
void Application::printObjects(T* objects, int count, const string& typeName, const string& header)
{
    if (count > 0)
    {
        cout << "\n-- " << typeName << " --\n";
        cout << header << endl;
        for (int i = 0; i < count; i++)
        {
            cout << "| " << setw(2) << right << (i + 1) << " | ";
            cout << objects[i] << endl;
        }
        // Определяем разделитель в зависимости от типа
        if (typeName == "Повозки")
        {
            cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
        }
        else
        {
            cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
        }
    }
}

template<typename T>
void Application::saveArrayToFile(std::ofstream& file, T* objects, int count) const
{
    file << count << "\n";
    for (int i = 0; i < count; i++)
    {
        file << objects[i].GetName() << "\n";
        file << objects[i].GetDistance() << "\n";
        file << objects[i].GetPassengerRate() << "\n";
        file << objects[i].GetCargoRate() << "\n";
        file << objects[i].GetSpeed() << "\n";
        
        // Сохраняем специфичные поля для каждого типа
        if constexpr (std::is_same_v<T, Car>)
        {
            file << objects[i].get_fuel_consumption() << "\n";
            file << objects[i].get_fuel_type() << "\n";
            file << objects[i].get_mileage_since_maintenance() << "\n";
        }
        else if constexpr (std::is_same_v<T, Bicycle>)
        {
            file << objects[i].get_gears() << "\n";
            file << objects[i].get_bicycle_type() << "\n";
        }
        else if constexpr (std::is_same_v<T, Cart>)
        {
            file << objects[i].get_horse_count() << "\n";
            file << objects[i].get_cart_type() << "\n";
            file << objects[i].get_hours_since_last_feed() << "\n";
        }
    }
}

template<typename T>
void Application::loadArrayFromFile(std::ifstream& file, T*& objects, int& count)
{
    file >> count;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (count < 0 || count > 10000)
        throw InvalidArgumentException("count", "Некорректное количество объектов в файле");
    
    objects = new T[count];
    
    for (int i = 0; i < count; i++)
    {
        string name;
        double distance, passengerRate, cargoRate, speed;
        
        getline(file, name);
        file >> distance >> passengerRate >> cargoRate >> speed;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        
        objects[i] = T(name, distance, passengerRate, cargoRate, speed);
        
        // Загружаем специфичные поля для каждого типа
        if constexpr (std::is_same_v<T, Car>)
        {
            double fuelConsumption, mileage;
            string fuelType;
            file >> fuelConsumption;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(file, fuelType);
            file >> mileage;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            objects[i].set_fuel_consumption(fuelConsumption);
            objects[i].set_fuel_type(fuelType);
            objects[i].set_mileage_since_maintenance(mileage);
        }
        else if constexpr (std::is_same_v<T, Bicycle>)
        {
            int gears;
            string bicycleType;
            file >> gears;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(file, bicycleType);
            objects[i].set_gears(gears);
            objects[i].set_bicycle_type(bicycleType);
        }
        else if constexpr (std::is_same_v<T, Cart>)
        {
            int horseCount;
            double hours;
            string cartType;
            file >> horseCount;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(file, cartType);
            file >> hours;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            objects[i].set_horse_count(horseCount);
            objects[i].set_cart_type(cartType);
            objects[i].set_hours_since_last_feed(hours);
        }
    }
}

template<typename T>
void Application::saveDequeToFile(std::ofstream& file, const Deque<T>& deque) const
{
    int count = 0;
    deque.for_each([&count](const T&) { count++; });
    
    file << count << "\n";
    deque.for_each([&file](const T& obj) {
        file << obj.GetName() << "\n";
        file << obj.GetDistance() << "\n";
        file << obj.GetPassengerRate() << "\n";
        file << obj.GetCargoRate() << "\n";
        file << obj.GetSpeed() << "\n";
        
        if constexpr (std::is_same_v<T, Car>)
        {
            file << obj.get_fuel_consumption() << "\n";
            file << obj.get_fuel_type() << "\n";
            file << obj.get_mileage_since_maintenance() << "\n";
        }
        else if constexpr (std::is_same_v<T, Bicycle>)
        {
            file << obj.get_gears() << "\n";
            file << obj.get_bicycle_type() << "\n";
        }
        else if constexpr (std::is_same_v<T, Cart>)
        {
            file << obj.get_horse_count() << "\n";
            file << obj.get_cart_type() << "\n";
            file << obj.get_hours_since_last_feed() << "\n";
        }
    });
}

template<typename T>
void Application::loadDequeFromFile(std::ifstream& file, Deque<T>& deque)
{
    int count;
    file >> count;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    
    deque.clear();
    
    for (int i = 0; i < count; i++)
    {
        string name;
        double distance, passengerRate, cargoRate, speed;
        
        getline(file, name);
        file >> distance >> passengerRate >> cargoRate >> speed;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        
        T obj(name, distance, passengerRate, cargoRate, speed);
        
        if constexpr (std::is_same_v<T, Car>)
        {
            double fuelConsumption, mileage;
            string fuelType;
            file >> fuelConsumption;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(file, fuelType);
            file >> mileage;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            obj.set_fuel_consumption(fuelConsumption);
            obj.set_fuel_type(fuelType);
            obj.set_mileage_since_maintenance(mileage);
        }
        else if constexpr (std::is_same_v<T, Bicycle>)
        {
            int gears;
            string bicycleType;
            file >> gears;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(file, bicycleType);
            obj.set_gears(gears);
            obj.set_bicycle_type(bicycleType);
        }
        else if constexpr (std::is_same_v<T, Cart>)
        {
            int horseCount;
            double hours;
            string cartType;
            file >> horseCount;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(file, cartType);
            file >> hours;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            obj.set_horse_count(horseCount);
            obj.set_cart_type(cartType);
            obj.set_hours_since_last_feed(hours);
        }
        
        deque.push_back(obj);
    }
}


