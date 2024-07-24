#include "Pizza.hpp"

Pizza::~Pizza() {}

ConcretePizza::ConcretePizza(std::string const & name, double price, minutes bakingTime) : name_(name), price_(price), bakingTime_(bakingTime) {}

std::string ConcretePizza::getName() const
{
    return name_;
}

double ConcretePizza::getPrice() const
{
    return price_;
}

minutes ConcretePizza::getBakingTime() const
{
    return bakingTime_;
}