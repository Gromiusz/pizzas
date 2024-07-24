#pragma once
#include <list>
#include <set>
#include <chrono>
#include <string>

using minutes = std::chrono::seconds;   // To simulate time flow ;)

class Pizza
{
public:
    //Pizza(std::string const & name, double price, minutes bakingTime);
    virtual ~Pizza() = 0;
    virtual std::string getName() const = 0;
    virtual double getPrice() const = 0;
    virtual minutes getBakingTime() const = 0;
};

class ConcretePizza: public Pizza
{
protected:
    std::string name_;
    double price_;
    minutes bakingTime_;

public:
    ConcretePizza() = default;
    ConcretePizza(std::string const & name, double price, minutes bakingTime);
    std::string getName() const override;
    double getPrice() const override;
    minutes getBakingTime() const override;
};

using Pizzas = std::set<Pizza*>;
