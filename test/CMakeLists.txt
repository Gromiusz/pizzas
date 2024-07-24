enable_testing()
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

include(GoogleTest)

add_executable(PizzeriaTest PizzeriaTest.cpp)

target_link_libraries(PizzeriaTest PUBLIC PizzaLib GTest::gtest_main GTest::gmock_main)
target_include_directories(PizzeriaTest PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src")

gtest_discover_tests(PizzeriaTest)
