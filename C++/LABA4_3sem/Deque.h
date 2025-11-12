#pragma once
#include <cstddef>
#include <stdexcept>

// Узел двунаправленной очереди
template<typename T>
struct DequeNode {
    T data;
    DequeNode* prev;
    DequeNode* next;

    explicit DequeNode(const T& value)
            : data(value), prev(nullptr), next(nullptr) {}
};

// Шаблонный класс двунаправленной очереди (deque)
template<typename T>
class Deque {
private:
    DequeNode<T>* head{};
    DequeNode<T>* tail{};
    std::size_t sz{};

public:
    Deque() = default;

    ~Deque() {
        clear();
    }

    bool empty() const {
        return sz == 0;
    }

    std::size_t size() const {
        return sz;
    }

    void push_back(const T& value) {
        auto* node = new DequeNode<T>(value);
        if (!tail) {
            head = tail = node;
        } else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        ++sz;
    }

    void push_front(const T& value) {
        auto* node = new DequeNode<T>(value);
        if (!head) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        ++sz;
    }

    void pop_back() {
        if (!tail) throw std::out_of_range("Deque is empty");
        auto* node = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete node;
        --sz;
    }

    void pop_front() {
        if (!head) throw std::out_of_range("Deque is empty");
        auto* node = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete node;
        --sz;
    }

    // Доступ по индексу [0..size-1]
    T& operator[](std::size_t index) {
        if (index >= sz) throw std::out_of_range("Deque index out of range");
        DequeNode<T>* cur = head;
        for (std::size_t i = 0; i < index; ++i)
            cur = cur->next;
        return cur->data;
    }

    const T& operator[](std::size_t index) const {
        if (index >= sz) throw std::out_of_range("Deque index out of range");
        DequeNode<T>* cur = head;
        for (std::size_t i = 0; i < index; ++i)
            cur = cur->next;
        return cur->data;
    }

    // Удалить элемент по индексу
    void erase(std::size_t index) {
        if (index >= sz) throw std::out_of_range("Deque index out of range");
        DequeNode<T>* cur = head;
        for (std::size_t i = 0; i < index; ++i)
            cur = cur->next;

        if (cur->prev) cur->prev->next = cur->next;
        else head = cur->next;

        if (cur->next) cur->next->prev = cur->prev;
        else tail = cur->prev;

        delete cur;
        --sz;
    }

    void clear() {
        DequeNode<T>* cur = head;
        while (cur) {
            DequeNode<T>* next = cur->next;
            delete cur;
            cur = next;
        }
        head = tail = nullptr;
        sz = 0;
    }
};
