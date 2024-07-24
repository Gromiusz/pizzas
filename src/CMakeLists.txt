add_executable(Pizzas main.cpp)
add_library(PizzaLib STATIC Funghi.cpp Margherita.cpp Pizza.cpp Pizzeria.cpp)

target_link_libraries(Pizzas PUBLIC PizzaLib)
target_include_directories(Pizzas PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src")