#pragma once
#include "TransportVehicle.h"

class Cart : public TransportVehicle
{
private:
    int horseCount;                  // Количество лошадей
    std::string cartType;            // Тип повозки (телега, карета, сани)
    double hoursSinceLastFeed;       // Часов с последнего кормления

public:
    Cart();
    Cart(const std::string& Name,
         double Distance,
         double PassengerRate,
         double CargoRate,
         double Speed);
    Cart(const Cart& other);
    ~Cart();

    std::string vehicle_type() const override;
    virtual void print_header() const override;
    virtual void print_separator() const override;
    virtual void menu() const override;

    // Уникальные методы для повозки
    int get_horse_count() const;                             // Получить количество лошадей
    void set_horse_count(int Count);                         // Установить количество лошадей
    std::string get_cart_type() const;                        // Получить тип повозки
    void set_cart_type(const std::string& Type);            // Установить тип повозки
    double get_hours_since_last_feed() const;                // Получить часов с последнего кормления
    void set_hours_since_last_feed(double Hours);           // Установить часов с последнего кормления
    bool needs_horse_feed() const;                            // Нужно ли кормить лошадей (если прошло > 6 часов)
    double calculate_feed_cost(double feedPricePerHorse) const; // Рассчитать стоимость корма
    void feed_horses();                                       // Покормить лошадей (сбросить счетчик часов)

    friend std::istream& operator>>(std::istream& is, Cart& ob);
    friend std::ostream& operator<<(std::ostream& os, Cart& ob);
    Cart& operator=(const Cart& other);
};