cmake_minimum_required(VERSION 3.16)
project(Server VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Sql)

# Динамическая библиотека для вычислений (CalcLib)
add_library(CalcLib SHARED src/calc.cpp src/calc.h)
target_compile_definitions(CalcLib PRIVATE CALC_LIBRARY)
target_include_directories(CalcLib PUBLIC src)

# Исполняемый файл сервера
add_executable(TcpServer
    src/main.cpp
    src/Server.cpp src/Server.h
    src/AuthManager.cpp src/AuthManager.h
)

target_link_libraries(TcpServer PRIVATE Qt6::Core Qt6::Network Qt6::Sql CalcLib)

enable_testing()
# 1. Сборка Unit-тестов
add_executable(TestCalc tests/test_calc.cpp)
target_link_libraries(TestCalc PRIVATE Qt6::Core Qt6::Test CalcLib)
add_test(NAME CalcUnitTests COMMAND TestCalc)

# 2. Сборка Fuzz-таргета (Требует Clang)
option(BUILD_FUZZER "Build Fuzzing Target" OFF)
if(BUILD_FUZZER AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_executable(FuzzServer tests/fuzz_server.cpp src/Server.cpp)
    target_link_libraries(FuzzServer PRIVATE Qt6::Core Qt6::Network)
    # Добавляем флаги санитайзеров и фаззера
    target_compile_options(FuzzServer PRIVATE -fsanitize=address,undefined,fuzzer -g -O1)
    target_link_options(FuzzServer PRIVATE -fsanitize=address,undefined,fuzzer)
endif()
