cmake_minimum_required(VERSION 3.2)

project(tst_cow)

find_package(Qt5Test REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
enable_testing()

add_executable(${PROJECT_NAME} tst_cow.cpp testcow.cpp)
add_test(${PROJECT_NAME} ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Test)
