#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include "Car.h"
#include "Bicycle.h"
#include "Cart.h"
#include "Deque.hpp"

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
