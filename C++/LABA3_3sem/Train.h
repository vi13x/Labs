#pragma once

#include "Passenger_carrier.h"

class Train : public Passenger_carrier {
private:
    double time_stops;
    int wagon_count;
    std::string train_type;

public:
    Train();
    Train(double Time_stops,
          int Wagon_count,
          const std::string& Train_type,
          const std::string& Name,
          double Distance,
          double Money_km,
          double Speed);
    Train(const Train& other);
    ~Train();

    double time_in_path() override;
    double cost_path() override;
    void menu() override;

    double GetTime_stops();
    int GetWagon_count();
    std::string GetTrain_type();

    void SetTime_stops(double Time_stops);
    void SetWagon_count(int Wagon_count);
    void SetTrain_type(const std::string& Train_type);

    friend std::istream& operator>>(std::istream& is, Train& ob);
    friend std::ostream& operator<<(std::ostream& os, Train& ob);
    Train& operator=(const Train& other);

    void print_header() const override;
    void print_table() const override;
};
