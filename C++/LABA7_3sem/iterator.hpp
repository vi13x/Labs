#pragma once
#include "ExceptionHandler.h"

// Forward declaration структуры Node
template <typename T>
struct DequeNode;

// Шаблонный класс итератора для Deque
template <typename T>
class Iterator
{
private:
    // Используем указатель на узел
    // Структура DequeNode должна быть определена при использовании
    DequeNode<T>* current;

    // Конструктор доступен только для Deque
    explicit Iterator(DequeNode<T>* node) : current(node) {}

    // Deque - дружественный класс, чтобы иметь доступ к конструктору
    template <typename U>
    friend class Deque;

public:
    // Конструктор по умолчанию
    Iterator() : current(nullptr) {}

    // Перегрузка оператора разыменования * (неконстантная версия)
    T& operator*()
    {
        if (!current)
            throw RuntimeErrorException("Попытка разыменования нулевого итератора");
        return current->data;
    }

    // Перегрузка оператора разыменования * (константная версия)
    const T& operator*() const
    {
        if (!current)
            throw RuntimeErrorException("Попытка разыменования нулевого итератора");
        return current->data;
    }

    // Префиксный инкремент ++it
    Iterator& operator++()
    {
        if (current)
            current = current->next;
        return *this;
    }

    // Постфиксный инкремент it++
    Iterator operator++(int)
    {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    // Префиксный декремент --it
    Iterator& operator--()
    {
        if (current)
            current = current->prev;
        return *this;
    }

    // Постфиксный декремент it--
    Iterator operator--(int)
    {
        Iterator temp = *this;
        --(*this);
        return temp;
    }

    // Оператор сравнения ==
    bool operator==(const Iterator& other) const
    {
        return current == other.current;
    }

    // Оператор сравнения !=
    bool operator!=(const Iterator& other) const
    {
        return current != other.current;
    }

    // Получить указатель на узел (для внутреннего использования)
    DequeNode<T>* getNode() const { return current; }
};
