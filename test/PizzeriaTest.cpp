//#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
//#include "mocks/PizzaMock.hpp"
#include "Pizzeria.hpp"
#include "Margherita.hpp"
#include "Funghi.hpp"

using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test
{
public:
    Pizzeria pizzeria = Pizzeria("dummyName"); 
};

class PizzaDummy : public Pizza
{
public:
    PizzaDummy(): Pizza("Dummy", 10.0, minutes(1)) {}
    std::string getName() const override {return "DummyPizza";}
    double getPrice() const override {return 10.0;}
    minutes getBakingTime() const override {return minutes(0);}
};

class PizzaStub : public Pizza
{
public:
    PizzaStub() = delete;
    PizzaStub(std::string const & name): Pizza(name, 20.0, minutes(1)) {}
    std::string getName() const override {return Pizza::getName();}
    double getPrice() const override 
    {
        std::string name__ = Pizza::getName();
        if(name__.size() < 4) return 15;
        return static_cast<double>(name__[3]);
    }
    minutes getBakingTime() const override
    {
        std::string name__ = Pizza::getName();
        long int sum = 0;
        for(const auto & letter: name__)
        {
            sum += static_cast<long int>(letter/100.0);
        }
        return minutes(sum);
    }
};

class PizzaMock : public Pizza
{
public:
    PizzaMock() : Pizza("PizzaMock", 25.0, minutes(0)) {}
    MOCK_METHOD(std::string, getName, (), (const, override));
    MOCK_METHOD(double, getPrice, (), (const, override));
    MOCK_METHOD(minutes, getBakingTime, (), (const, override));
};


TEST_F(PizzeriaTest, priceForMargherita25AndFunghi30ShouldBe55)
{
    // Given
    Pizzas pizzas = {new Margherita{25.0}, new Funghi{30.0}};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(55, price);
}

TEST_F(PizzeriaTest, bakeDummyPizza)
{
    // Given
    Pizzas pizzas = {new PizzaDummy{}};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock)
{   
    // Given
    PizzaMock* mock = new PizzaMock{};
    Pizzas pizzas = {mock};
    EXPECT_CALL(*mock, getPrice()).WillOnce(Return(40.0));
    
    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(40, price);

    delete mock;
}
