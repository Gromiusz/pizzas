add_executable(PizzeriaTest test_main.cpp PizzeriaTest.cpp)

target_link_libraries(PizzeriaTest PUBLIC PizzaLib GTest::gtest_main)
target_include_directories(PizzeriaTest PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src")

include(GoogleTest)
gtest_discover_tests(PizzeriaTest)