#include <gtest/gtest.h>
#include "gmock/gmock.h"
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
    std::shared_ptr<FakeTimeForBakePizza> fakeTime = std::make_shared<FakeTimeForBakePizza>();
    Pizzeria pizzeria = Pizzeria("dummyName", fakeTime); 
};

class PizzaDummy : public Pizza 
{
public:
    std::string getName() const override {return "Dummy";}
    double getPrice() const override {return 10;}
    minutes getBakingTime() const override {return minutes(2);}
};

class PizzaStub : public Pizza
{
    std::string name_;
public:
    PizzaStub(std::string const & name) : name_(name) {}
    std::string getName() const override {return name_;}
    double getPrice() const override 
    {
        if(name_.size() >= 4)
        {
            return static_cast<double>(name_[3]);
        }
        return 10.0;
    }
    minutes getBakingTime() const override 
    {
        double sum = 0;
        for(const auto & letter : name_)
        {
            sum += (static_cast<double>(letter)/10);
        }
       return minutes(static_cast<long int>(sum));
    }
};

class PizzaMock : public Pizza
{
public:
    MOCK_METHOD(std::string, getName, (), (const, override));
    MOCK_METHOD(double, getPrice, (), (const, override));
    MOCK_METHOD(minutes, getBakingTime, (), (const, override));
};

class TimeMock : public Pizza
{
public:
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
    pizzeria.bakePizzas(orderId);

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
    Pizzas pizzas = {new PizzaStub{"Stub"}};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

}

TEST_F(PizzeriaTest, bakeWithStrictMock)
{
    // Given
    StrictMock<TimeMock> * mock = new StrictMock<TimeMock>();
    Pizzas pizzas = {mock};
    EXPECT_CALL(*mock, getName()).WillOnce(Return("StrictPizza"));
    EXPECT_CALL(*mock, getBakingTime()).WillOnce(Return(minutes(2)));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);

    delete mock;
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

TEST_F(PizzeriaTest, bakePizzasForPizzaMock)
{   
    // Given
    PizzaMock* mock = new PizzaMock{};
    Pizzas pizzas = {mock};
    EXPECT_CALL(*mock, getBakingTime()).WillOnce(Return(minutes(2)));
    EXPECT_CALL(*mock, getName()).WillOnce(Return("Hawajska"));
    
    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    delete mock;
}

TEST_F(PizzeriaTest, bakeLikeInMain)
{
    StrictMock<TimeMock> * strictMock = new StrictMock<TimeMock>();
    NiceMock<TimeMock> * niceMock = new NiceMock<TimeMock>();
    Pizzas pizzas = {new PizzaStub{"mainStub"}, new Funghi{30.0}, strictMock, niceMock};
    EXPECT_CALL(*strictMock, getBakingTime()).WillOnce(Return(minutes(2)));
    EXPECT_CALL(*strictMock, getName()).WillOnce(Return("Hawajska"));
    EXPECT_CALL(*strictMock, getPrice()).WillOnce(Return(30.0));

    EXPECT_CALL(*niceMock, getName()).WillOnce(Return("NicePizza"));

    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    delete strictMock;
    delete niceMock;
}
