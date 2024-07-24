#pragma once
#include "Pizza.hpp"

class Margherita : public ConcretePizza
{
public:
    Margherita() = delete;
    Margherita(double price);
};
