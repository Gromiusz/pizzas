add_executable(PizzeriaTest PizzeriaTest.cpp)

target_link_libraries(PizzeriaTest PUBLIC PizzaLib)
target_include_directories(PizzeriaTest PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src"
                          "${gtest_SOURCE_DIR}/include"  # Include GoogleTest headers
                          "${gmock_SOURCE_DIR}/include"  # Include GoogleMock headers
                          )

target_link_libraries(PizzeriaTest PUBLIC GTest::gtest_main GMock:gmock_main)

include(GoogleTest)
gtest_discover_tests(PizzeriaTest)cd