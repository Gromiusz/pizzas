add_library(lib STATIC Pizzeria.cpp Pizza.cpp Margherita.cpp Funghi.cpp)
add_executable(Pizza main.cpp)
target_link_libraries(Pizza lib)