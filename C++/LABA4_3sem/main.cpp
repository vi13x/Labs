#include <iostream>
#include <iomanip>
#include <limits>
#include <windows.h>

#include "Car.h"
#include "Bicycle.h"
#include "Cart.h"
#include "Deque.h"

using namespace std;

// ===========================================================
//   МЕНЮ РАБОТЫ С ОДНИМ ОБЪЕКТОМ + ДЕКОМ
// ===========================================================

template <typename T>
void menu_vehicle(T& t, Deque<T>& dq)
{
    while (true)
    {
        t.menu();

        cout << "14. Показать содержимое дека\n";
        cout << "15. Добавить в начало дека (push_front)\n";
        cout << "16. Добавить в конец дека (push_back)\n";
        cout << "17. Удалить из начала дека (pop_front)\n";
        cout << "18. Удалить с конца дека (pop_back)\n";
        cout << "19. Найти в деке по названию\n";
        cout << "20. Отсортировать дек по расстоянию\n";
        cout << "21. Показать дек подробно (в виде таблицы)\n";


        cout << "Выбор: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            // --------------------
            //     БАЗОВОЕ МЕНЮ
            // --------------------
            case 0:
                return;

            case 1:
                cout << "\nТЕКУЩИЕ ДАННЫЕ:\n";
                t.print_header();
                t.print_table();
                cout << endl;
                break;

            case 2: {
                string n;
                cout << "Введите новое название: ";
                getline(cin, n);
                t.SetName(n);
                break;
            }

            case 3: {
                double d;
                cout << "Введите новое расстояние: ";
                cin >> d;
                t.SetDistance(d);
                break;
            }

            case 4: {
                double p;
                cout << "Введите новую цену за км (пассажиры): ";
                cin >> p;
                t.SetPassengerRate(p);
                break;
            }

            case 5: {
                double c;
                cout << "Введите новую цену за км (груз): ";
                cin >> c;
                t.SetCargoRate(c);
                break;
            }

            case 6: {
                double v;
                cout << "Введите новую скорость: ";
                cin >> v;
                t.SetSpeed(v);
                break;
            }

            case 7:
                cout << "Название: " << t.GetName() << endl;
                break;

            case 8:
                cout << "Расстояние: " << t.GetDistance() << endl;
                break;

            case 9:
                cout << "Цена/км пассажиров: " << t.GetPassengerRate() << endl;
                break;

            case 10:
                cout << "Цена/км груза: " << t.GetCargoRate() << endl;
                break;

            case 11:
                cout << "Скорость: " << t.GetSpeed() << endl;
                break;

            case 12: {
                int p;
                cout << "Введите количество пассажиров: ";
                cin >> p;
                cout << "Стоимость: " << t.cost_passengers(p) << endl;
                cout << "Время: " << t.time_in_path() << endl;
                break;
            }

            case 13: {
                double kg;
                cout << "Введите массу груза: ";
                cin >> kg;
                cout << "Стоимость: " << t.cost_cargo(kg) << endl;
                cout << "Время: " << t.time_in_path() << endl;
                break;
            }

                // =====================================================
                //                МЕНЮ РАБОТЫ С ДЕКОМ (14–20)
                // =====================================================

            case 14:
                cout << "\n=== ДЕК ===\n";
                dq.print();
                break;

            case 15: {
                T obj;
                cout << "Введите данные для вставки в начало:\n";
                cin >> obj;
                dq.push_front(obj);
                cout << "Добавлено!\n";
                break;
            }

            case 16: {
                T obj;
                cout << "Введите данные для вставки в конец:\n";
                cin >> obj;
                dq.push_back(obj);
                cout << "Добавлено!\n";
                break;
            }

            case 17:
                if (dq.pop_front()) cout << "Удалено!\n";
                else cout << "Дек пуст!\n";
                break;

            case 18:
                if (dq.pop_back()) cout << "Удалено!\n";
                else cout << "Дек пуст!\n";
                break;

            case 19: {
                string query;
                cout << "Введите название поиска: ";
                getline(cin, query);

                T key;
                key.SetName(query);

                const T *found = dq.find(key);

                if (found) {
                    cout << "Найдено:\n";
                    found->print_header();
                    found->print_table();
                } else cout << "Не найдено!\n";

                break;
            }

            case 20: {
                dq.sort([](const T &a, const T &b) {
                    return a.GetDistance() < b.GetDistance();
                });
                cout << "Отсортировано!\n";
                break;

                default:
                    cout << "Некорректный ввод!\n";
                break;
            }
            case 21:
            {
                if (dq.empty())
                {
                    cout << "Дек пуст!\n";
                    break;
                }

                cout << "\n=== ДЕК (подробно) ===\n";

                T temp;
                temp.print_header();

                dq.for_each([](const T& obj)
                            {
                                obj.print_table();
                            });

                break;
            }


        }
    }
}

// ===========================================================
//                        MAIN
// ===========================================================

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int carCount;
    cout << "Сколько автомобилей создать? (минимум 2): ";
    cin >> carCount;

    while (carCount < 2)
    {
        cout << "Ошибка! Минимум 2.\nПовторите ввод: ";
        cin >> carCount;
    }

    int bicycleCount;
    cout << "Сколько велосипедов создать? ";
    cin >> bicycleCount;

    int cartCount;
    cout << "Сколько повозок создать? ";
    cin >> cartCount;

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

    // ---------------------------
    //       ДЕКИ ДЛЯ ВСЕХ
    // ---------------------------
    Deque<Car> carDeque;
    Deque<Bicycle> bicycleDeque;
    Deque<Cart> cartDeque;

    for (int i = 0; i < carCount; i++) carDeque.push_back(cars[i]);
    for (int i = 0; i < bicycleCount; i++) bicycleDeque.push_back(bicycles[i]);
    for (int i = 0; i < cartCount; i++) cartDeque.push_back(carts[i]);

    cout << "\nВыберите тип транспорта:\n";
    cout << "1 — Автомобили\n";
    cout << "2 — Велосипеды\n";
    cout << "3 — Повозки\n";
    cout << "0 — Выход\n";

    int type;
    cin >> type;

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
            if (index >= 1 && index <= carCount)
                menu_vehicle(cars[index - 1], carDeque);
            break;

        case 2:
            cout << "Выберите велосипед (1-" << bicycleCount << "): ";
            cin >> index;
            if (index >= 1 && index <= bicycleCount)
                menu_vehicle(bicycles[index - 1], bicycleDeque);
            break;

        case 3:
            cout << "Выберите повозку (1-" << cartCount << "): ";
            cin >> index;
            if (index >= 1 && index <= cartCount)
                menu_vehicle(carts[index - 1], cartDeque);
            break;
    }

    delete[] cars;
    delete[] bicycles;
    delete[] carts;

    return 0;
}
