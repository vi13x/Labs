#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <type_traits>
#include <string>

#include "Car.h"
#include "Bicycle.h"
#include "Cart.h"
#include "Deque.hpp"

using namespace std;



class MenuManager
{
private:
    template<typename T>
    static void handleDequeOperation(T& t, Deque<T>& dq, int choice, int firstDequeItem, bool isCart);
    
    template<typename T>
    static void handleUniqueMenuItems(T& t, int choice);

public:
    template<typename T>
    static void menu_object(T& t, Deque<T>& dq);
};

template<typename T>
void MenuManager::menu_object(T& t, Deque<T>& dq)
{
    // Определяем номер первого пункта меню для работы с деком
    // Car и Cart: последний пункт меню = 22, поэтому дек начинается с 23
    // Bicycle: последний пункт меню = 19, поэтому дек начинается с 20
    constexpr int firstDequeItem = (std::is_same_v<T, Bicycle>) ? 20 : 23;
    constexpr bool isCart = std::is_same_v<T, Cart>;
    
    while (true)
    {
        t.menu();

        cout << firstDequeItem << ". Показать содержимое дека\n";
        cout << (firstDequeItem + 1) << ". Добавить в начало дека (push_front)\n";
        cout << (firstDequeItem + 2) << ". Добавить в конец дека (push_back)\n";
        cout << (firstDequeItem + 3) << ". Удалить из начала дека (pop_front)\n";
        cout << (firstDequeItem + 4) << ". Удалить с конца дека (pop_back)\n";
        cout << (firstDequeItem + 5) << ". Найти в деке по предикату\n";
        cout << (firstDequeItem + 6) << ". Отсортировать дек по расстоянию\n";
        cout << (firstDequeItem + 7) << ". Показать дек подробно (в виде таблицы)\n";

        cout << "Выбор: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 0:
                return;

            case 1: {
                cout << "\nТЕКУЩИЕ ДАННЫЕ:\n";
                if (isCart) {
                    cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
                    cout << "| №  | Тип           | Название| Расстояние| Скорость       | Цена/км  | Цена/км  | Время          | Лошадей     | Тип повозки | Часов с корм.  |" << endl;
                    cout << "|    |               |         |          |                 | пасс     | кг       |                |             |             |                |" << endl;
                    cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
                } else {
                    cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
                    cout << "| №  | Название | Расстояние| Скорость | Цена/км  | Цена/км  | Время    |" << endl;
                    cout << "|    |          |          |           | пасс     | кг       |          |" << endl;
                    cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
                }
                cout << "| " << setw(2) << right << 1 << " | ";
                cout << t << endl;
                if (isCart) {
                    cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
                } else {
                    cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
                }
                cout << endl;
                break;
            }

            case 2: {
                string n;
                cout << "Введите новое название: ";
                getline(cin, n);
                t.SetName(n);
                if (!isCart) cout << endl;
                break;
            }

            case 3: {
                double d;
                cout << "Введите новое расстояние: ";
                cin >> d;
                if (!isCart) cin.ignore(numeric_limits<streamsize>::max(), '\n');
                t.SetDistance(d);
                if (isCart) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl;
                }
                break;
            }

            case 4: {
                double p;
                cout << "Введите новую цену за км (пассажиры): ";
                cin >> p;
                if (!isCart) cin.ignore(numeric_limits<streamsize>::max(), '\n');
                t.SetPassengerRate(p);
                if (isCart) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl;
                }
                break;
            }

            case 5: {
                double c;
                cout << "Введите новую цену за км (груз): ";
                cin >> c;
                if (!isCart) cin.ignore(numeric_limits<streamsize>::max(), '\n');
                t.SetCargoRate(c);
                if (isCart) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl;
                }
                break;
            }

            case 6: {
                double v;
                cout << "Введите новую скорость: ";
                cin >> v;
                if (!isCart) cin.ignore(numeric_limits<streamsize>::max(), '\n');
                t.SetSpeed(v);
                if (isCart) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl;
                }
                break;
            }

            case 7:
                cout << "Название: " << t.GetName() << endl;
                if (isCart) cout << endl;
                break;

            case 8:
                cout << "Расстояние: " << t.GetDistance() << endl;
                if (isCart) cout << endl;
                break;

            case 9:
                cout << "Цена/км пассажиров: " << t.GetPassengerRate() << endl;
                if (isCart) cout << endl;
                break;

            case 10:
                cout << "Цена/км груза: " << t.GetCargoRate() << endl;
                if (isCart) cout << endl;
                break;

            case 11:
                cout << "Скорость: " << t.GetSpeed() << endl;
                if (isCart) cout << endl;
                break;

            case 12: {
                int people;
                cout << "Введите количество пассажиров: ";
                cin >> people;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Стоимость: " << t.cost_passengers(people) << endl;
                cout << "Время: " << t.time_in_path() << " ч" << endl << endl;
                break;
            }

            case 13: {
                double kg;
                cout << "Введите массу груза (кг): ";
                cin >> kg;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Стоимость: " << t.cost_cargo(kg) << endl;
                cout << "Время: " << t.time_in_path() << " ч" << endl << endl;
                break;
            }

            // Уникальные методы для каждого типа
            default:
                if (choice >= 14 && choice < firstDequeItem)
                {
                    handleUniqueMenuItems(t, choice);
                }
                else if (choice >= firstDequeItem && choice <= firstDequeItem + 7)
                {
                    handleDequeOperation(t, dq, choice, firstDequeItem, isCart);
                }
                else
                {
                    cout << "Некорректный ввод!\n";
                }
                break;
        }
    }
}

template<typename T>
void MenuManager::handleDequeOperation(T& t, Deque<T>& dq, int choice, int firstDequeItem, bool isCart)
{
    switch (choice - firstDequeItem) {
        case 0: // Показать содержимое дека
                cout << "\n=== ДЕК ===\n";
                dq.print();
                break;

        case 1: { // Добавить в начало
                T obj;
                cout << "Введите данные для вставки в начало:\n";
                cin >> obj;
                dq.push_front(obj);
                cout << "Добавлено!\n";
                break;
            }

        case 2: { // Добавить в конец
                T obj;
                cout << "Введите данные для вставки в конец:\n";
                cin >> obj;
                dq.push_back(obj);
                cout << "Добавлено!\n";
                break;
            }

        case 3: { // Удалить из начала
            T temp;
            if (dq.pop_front(temp)) {
                    cout << "Удалено: ";
                cout << temp << endl;
                }
                else cout << "Дек пуст!\n";
                break;
            }

        case 4: { // Удалить с конца
            T temp;
            if (dq.pop_back(temp)) {
                    cout << "Удалено: ";
                cout << temp << endl;
                }
                else cout << "Дек пуст!\n";
                break;
            }

        case 5: { // Найти
                cout << "\nВыберите поле для поиска:\n";
                cout << "1 - По названию\n";
                cout << "2 - По расстоянию\n";
                cout << "3 - По скорости\n";
                cout << "4 - По цене за км (пассажиры)\n";
                cout << "5 - По цене за км (груз)\n";
                cout << "Выбор: ";
                int searchField;
                cin >> searchField;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                T found;
                bool foundResult = false;

                switch (searchField) {
                    case 1: { // По названию
                        string query;
                        cout << "Введите название: ";
                        getline(cin, query);
                        foundResult = dq.find_if([&query](const T& obj) {
                            return obj.GetName() == query;
                        }, found);
                        break;
                    }
                    case 2: { // По расстоянию
                        double distance;
                        cout << "Введите расстояние: ";
                        cin >> distance;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        foundResult = dq.find_if([&distance](const T& obj) {
                            return obj.GetDistance() == distance;
                        }, found);
                        break;
                    }
                    case 3: { // По скорости
                        double speed;
                        cout << "Введите скорость: ";
                        cin >> speed;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        foundResult = dq.find_if([&speed](const T& obj) {
                            return obj.GetSpeed() == speed;
                        }, found);
                        break;
                    }
                    case 4: { // По цене за км (пассажиры)
                        double rate;
                        cout << "Введите цену за км (пассажиры): ";
                        cin >> rate;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        foundResult = dq.find_if([&rate](const T& obj) {
                            return obj.GetPassengerRate() == rate;
                        }, found);
                        break;
                    }
                    case 5: { // По цене за км (груз)
                        double rate;
                        cout << "Введите цену за км (груз): ";
                        cin >> rate;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        foundResult = dq.find_if([&rate](const T& obj) {
                            return obj.GetCargoRate() == rate;
                        }, found);
                        break;
                    }
                    default:
                        cout << "Некорректный выбор!\n";
                        break;
                }

                if (foundResult) {
                    cout << "Найдено:\n";
                if (isCart) {
                    cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
                    cout << "| №  | Тип           | Название| Расстояние| Скорость       | Цена/км  | Цена/км  | Время          | Лошадей     | Тип повозки | Часов с корм.  |" << endl;
                    cout << "|    |               |         |           |                | пасс     | кг       |                |             |             |                |" << endl;
                    cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
                } else {
                    cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
                    cout << "| №  | Название | Расстояние| Скорость | Цена/км  | Цена/км  | Время    |" << endl;
                    cout << "|    |          |          |           | пасс     | кг       |          |" << endl;
                    cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
                }
                cout << "| " << setw(2) << right << 1 << " | ";
                cout << found << endl;
                if (isCart) {
                    cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
                } else {
                    cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
                }
                } else if (searchField >= 1 && searchField <= 5) {
                    cout << "Не найдено!\n";
                }
                break;
            }

        case 6: { // Сортировать
                dq.sort([](const T &a, const T &b) {
                    return a.GetDistance() < b.GetDistance();
                });
                cout << "Отсортировано!\n";
                break;
            }

        case 7: { // Показать подробно
            if (dq.empty()) {
                cout << "Дек пуст!\n";
                break;
            }
            cout << "\n=== ДЕК (подробно) ===\n";
            if (isCart) {
                cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
                cout << "| №  | Тип           | Название| Расстояние| Скорость       | Цена/км | Цена/км  | Время          | Лошадей     | Тип повозки | Часов с корм.  |" << endl;
                cout << "|    |               |         |          |                | пасс     | кг       |                |             |             |                |" << endl;
                cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
            } else {
                cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
                cout << "| №  | Название |Расстояние| Скорость | Цена/км  | Цена/км  | Время    |" << endl;
                cout << "|    |          |          |          | пасс     | кг       |          |" << endl;
                cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
            }
            int idx = 1;
            dq.for_each([&idx](const T& obj) {
                cout << "| " << setw(2) << right << idx++ << " | ";
                cout << obj << endl;
            });
            if (isCart) {
                cout << "+----+---------------+----------+----------+---------------+----------+----------+----------------+-------------+-------------+----------------+" << endl;
            } else {
                cout << "+----+----------+----------+----------+----------+----------+----------+" << endl;
            }
            break;
        }
    }
}

// Специализация для Car
template<>
void MenuManager::handleUniqueMenuItems<Car>(Car& t, int choice)
{
    switch (choice) {
        case 14: {
            cout << "Расход топлива: " << t.get_fuel_consumption() << " л/100км" << endl << endl;
            break;
        }
        case 15: {
            double consumption;
            cout << "Введите расход топлива (л/100км): ";
            cin >> consumption;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t.set_fuel_consumption(consumption);
            cout << endl;
            break;
        }
        case 16: {
            cout << "Тип топлива: " << t.get_fuel_type() << endl << endl;
            break;
        }
        case 17: {
            string fuelType;
            cout << "Введите тип топлива: ";
            getline(cin, fuelType);
            t.set_fuel_type(fuelType);
            cout << endl;
            break;
        }
        case 18: {
            cout << "Пробег с последнего ТО: " << t.get_mileage_since_maintenance() << " км" << endl << endl;
            break;
        }
        case 19: {
            double mileage;
            cout << "Введите пробег с последнего ТО (км): ";
            cin >> mileage;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t.set_mileage_since_maintenance(mileage);
            cout << endl;
            break;
        }
        case 20: {
            if (t.needs_maintenance())
                cout << "Требуется ТО!" << endl;
            else
                cout << "ТО не требуется" << endl;
            cout << endl;
            break;
        }
            case 21: {
            double fuelPrice;
            cout << "Введите цену топлива за литр: ";
            cin >> fuelPrice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Стоимость топлива для поездки: " << t.calculate_fuel_cost(fuelPrice) << endl << endl;
            break;
        }
        case 22: {
            double additionalMileage;
            cout << "Введите дополнительный пробег (км): ";
            cin >> additionalMileage;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t.update_mileage(additionalMileage);
            cout << endl;
            break;
        }
    }
}

// Специализация для Bicycle
template<>
void MenuManager::handleUniqueMenuItems<Bicycle>(Bicycle& t, int choice)
{
    switch (choice) {
        case 14: {
            cout << "Количество передач: " << t.get_gears() << endl << endl;
            break;
        }
        case 15: {
            int gears;
            cout << "Введите количество передач: ";
            cin >> gears;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t.set_gears(gears);
            cout << endl;
            break;
        }
        case 16: {
            cout << "Тип велосипеда: " << t.get_bicycle_type() << endl << endl;
            break;
        }
        case 17: {
            string type;
            cout << "Введите тип велосипеда: ";
            getline(cin, type);
            t.set_bicycle_type(type);
            cout << endl;
            break;
        }
        case 18: {
            double gradient;
            cout << "Введите градиент подъема (%): ";
            cin >> gradient;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (t.can_climb_hill(gradient))
                cout << "Может подняться!" << endl;
            else
                cout << "Не может подняться!" << endl;
            cout << endl;
            break;
        }
        case 19: {
            cout << "Коэффициент усилия: " << t.calculate_effort_coefficient() << endl << endl;
            break;
        }
    }
}

// Специализация для Cart
template<>
void MenuManager::handleUniqueMenuItems<Cart>(Cart& t, int choice)
{
    switch (choice) {
        case 14: {
            cout << "Количество лошадей: " << t.get_horse_count() << endl << endl;
            break;
        }
        case 15: {
            int count;
            cout << "Введите количество лошадей: ";
            cin >> count;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t.set_horse_count(count);
            cout << endl;
            break;
        }
        case 16: {
            cout << "Тип повозки: " << t.get_cart_type() << endl << endl;
            break;
        }
        case 17: {
            string type;
            cout << "Введите тип повозки: ";
            getline(cin, type);
            t.set_cart_type(type);
            cout << endl;
            break;
        }
        case 18: {
            cout << "Часов с последнего кормления: " << t.get_hours_since_last_feed() << endl << endl;
            break;
        }
        case 19: {
            double hours;
            cout << "Введите часов с последнего кормления: ";
            cin >> hours;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t.set_hours_since_last_feed(hours);
            cout << endl;
            break;
        }
        case 20: {
            if (t.needs_horse_feed())
                cout << "Требуется кормление лошадей!" << endl;
            else
                cout << "Кормление не требуется" << endl;
            cout << endl;
            break;
        }
        case 21: {
            double feedPrice;
            cout << "Введите цену корма за лошадь: ";
            cin >> feedPrice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Стоимость корма: " << t.calculate_feed_cost(feedPrice) << endl << endl;
            break;
        }
        case 22: {
            t.feed_horses();
            cout << endl;
            break;
        }
    }
}


template<typename T>
void MenuManager::handleUniqueMenuItems(T& t, int choice)
{

}

