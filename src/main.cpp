#include "Margherita.hpp"
#include "Funghi.hpp"
#include "Pizzeria.hpp"
#include <memory>

int main()
{

    std::shared_ptr<RealTimeForBakePizza> realTime = std::make_shared<RealTimeForBakePizza>();
    Pizzeria bravo("Bravo Pizza", realTime);
    Pizzas pizzas = {new Margherita{25.0}, new Funghi{30.0}};

    auto orderId = bravo.makeOrder(pizzas);
    auto price = bravo.calculatePrice(orderId);
    bravo.bakePizzas(orderId);
    bravo.completeOrder(orderId);

    return 0;
}
