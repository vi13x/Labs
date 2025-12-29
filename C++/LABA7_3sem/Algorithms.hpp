#pragma once
#include <iostream>
#include <iterator>
#include "ExceptionHandler.h"

// Класс алгоритмов, работающий с итераторами
// Параметры - итераторы вместо типа T, что делает алгоритмы универсальными для всех контейнеров
class Algorithms
{
public:
    // Алгоритм поиска элемента по значению
    template<typename Iterator, typename T>
    static Iterator find(Iterator first, Iterator last, const T& value)
    {
        Iterator it = first;
        while (it != last)
        {
            if (*it == value)
            {
                return it;
            }
            ++it;
        }
        return last; // Не найдено
    }

    // Алгоритм сортировки (пузырьковая сортировка)
    // Работает только с двунаправленными итераторами (поддерживающими --)
    template<typename Iterator>
    static void sort(Iterator first, Iterator last)
    {
        if (first == last)
            return;

        Iterator end = last;
        --end; // Последний элемент

        bool swapped;
        do
        {
            swapped = false;
            Iterator it = first;
            Iterator next = first;
            ++next;

            while (it != end)
            {
                if (*next < *it)
                {
                    // Обмен значений через temp
                    typename std::iterator_traits<Iterator>::value_type temp = *it;
                    *it = *next;
                    *next = temp;
                    swapped = true;
                }
                ++it;
                ++next;
            }
        } while (swapped);
    }
};

