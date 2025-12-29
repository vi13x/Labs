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
    ~Cart() override;

    std::string vehicle_type() const override;
    virtual void print_table() const override;
    virtual void print_separator() const override;
    virtual void menu() const override;

    int get_horse_count() const;
    void set_horse_count(int Count);
    std::string get_cart_type() const;
    void set_cart_type(const std::string& Type);
    double get_hours_since_last_feed() const;
    void set_hours_since_last_feed(double Hours);
    bool needs_horse_feed() const;
    double calculate_feed_cost(double feedPricePerHorse) const;
    void feed_horses();

    friend std::istream& operator>>(std::istream& is, Cart& ob);
    friend std::ostream& operator<<(std::ostream& os, const Cart& ob);
    Cart& operator=(const Cart& other);
};


