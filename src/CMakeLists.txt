add_library(PizzaLib STATIC Funghi.cpp Margherita.cpp Pizza.cpp Pizzeria.cpp)

add_executable(Pizzas main.cpp)

target_link_libraries(Pizzas PUBLIC PizzaLib)