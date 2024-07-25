#pragma once
#include <string>
#include <tuple>
#include <vector>
#include <chrono>
#include "Pizza.hpp"
#include <memory>

enum class Status
{
    New,
    Paid,
    Baked,
    Completed
};

using Order = std::tuple<int, Pizzas, std::chrono::system_clock::time_point, Status>;

class TimeForBakePizza {
public:
    virtual ~TimeForBakePizza();
    virtual void startBakingPizza(minutes time) = 0;
};

class RealTimeForBakePizza : public TimeForBakePizza {
public:
    void startBakingPizza(minutes time) override;
};

class FakeTimeForBakePizza : public TimeForBakePizza {
public:
    void startBakingPizza(minutes time) override;
};

using KindOfTime = std::shared_ptr<TimeForBakePizza>;

class Pizzeria
{
public:
    Pizzeria(std::string const & name, KindOfTime kindOfTime);
    int makeOrder(Pizzas pizzas);
    double calculatePrice(int orderId);
    void bakePizzas(int orderId);
    void completeOrder(int orderId);


private:
    std::string name_;
    std::vector<Order> orders_;
    KindOfTime kindOfTime_;
};

