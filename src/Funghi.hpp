#pragma once
#include "Pizza.hpp"

class Funghi : public ConcretePizza
{
public:
    Funghi() = delete;
    Funghi(double price);
};
