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

        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    Deque() : head(nullptr), tail(nullptr) {}
    ~Deque() { clear(); }

    bool empty() const { return head == nullptr; }

    void clear()
    {
        while (!empty()) pop_front();
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
    bool pop_front()
    {
        if (empty()) return false;
        Node* t = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete t;
        return true;
    }

    bool pop_back()
    {
        if (empty()) return false;
        Node* t = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete t;
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

    const T* find(const T& key) const
    {
        Node* cur = head;
        while (cur)
        {
            if (cur->data == key)
                return &(cur->data);
            cur = cur->next;
        }
        return nullptr;
    }

    void sort(bool (*comp)(const T&, const T&))
    {
        if (!head || !head->next) return;

        bool swapped;
        do
        {
            swapped = false;
            Node* cur = head;

            while (cur->next)
            {
                if (!comp(cur->data, cur->next->data))
                {
                    T tmp = cur->data;
                    cur->data = cur->next->data;
                    cur->next->data = tmp;
                    swapped = true;
                }
                cur = cur->next;
            }

        } while (swapped);
    }
};
