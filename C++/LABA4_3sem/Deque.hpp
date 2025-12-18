#pragma once
#include <iostream>

template <typename T>
class Deque
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;

        explicit Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    Deque() : head(nullptr), tail(nullptr) {}
    ~Deque() { clear(); }

    bool empty() const { return head == nullptr; }

    void clear()
    {
        T dummy;
        while (!empty()) pop_front(dummy);
    }

    void push_front(const T& value)
    {
        Node* n = new Node(value);
        n->next = head;
        if (head) head->prev = n;
        else tail = n;
        head = n;
    }

    void push_back(const T& value)
    {
        Node* n = new Node(value);
        n->prev = tail;
        if (tail) tail->next = n;
        else head = n;
        tail = n;
    }

    template<typename Func>
    void for_each(Func f) const
    {
        Node* cur = head;
        while (cur)
        {
            f(cur->data);
            cur = cur->next;
        }
    }

    bool pop_front(T& t)
    {
        if (empty()) return false;
        Node* node = head;
        t = node->data;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete node;
        return true;
    }

    bool pop_back(T& t)
    {
        if (empty()) return false;
        Node* node = tail;
        t = node->data;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete node;
        return true;
    }

    void print() const
    {
        Node* cur = head;
        while (cur)
        {
            std::cout << cur->data << std::endl;
            cur = cur->next;
        }
    }

    // Метод поиска (для обратной совместимости)
    bool find(const T& key, T& t) const
    {
        Node* cur = head;
        while (cur)
        {
            if (cur->data == key)
            {
                t = cur->data;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // Метод поиска с предикатом (по любому полю)
    template<typename Predicate>
    bool find_if(Predicate pred, T& t) const
    {
        Node* cur = head;
        while (cur)
        {
            if (pred(cur->data))
            {
                t = cur->data;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // Метод сортировки (шаблонный функтор)
    template<typename Compare>
    void sort(Compare comp)
    {
        if (!head || !head->next) return;

        // Подсчитываем количество элементов для безопасности
        int count = 0;
        Node* countNode = head;
        while (countNode)
        {
            count++;
            countNode = countNode->next;
        }

        // Пузырьковая сортировка с защитой от зацикливания
        bool swapped;
        int iterations = 0;
        int maxIterations = count * count; // Максимальное число итераций для безопасности

        do
        {
            swapped = false;
            Node* cur = head;

            while (cur && cur->next)
            {
                if (!comp(cur->data, cur->next->data))
                {
                    // Обмен данными
                    T tmp = cur->data;
                    cur->data = cur->next->data;
                    cur->next->data = tmp;
                    swapped = true;
                }
                cur = cur->next;
            }

            iterations++;
            if (iterations > maxIterations)
            {
                // Защита от зацикливания
                break;
            }

        } while (swapped);
    }
};

