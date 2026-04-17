cmake_minimum_required(VERSION 3.16)

project(AuthTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую генерацию MOC
set(CMAKE_AUTOMOC ON)

# Включаем автоматическое добавление include для MOC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Ищем Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Sql Network)

# PostgreSQL
find_package(PostgreSQL REQUIRED)

# Исходники
set(SOURCES
    main.cpp
    AuthManager.cpp
)

set(HEADERS
    AuthManager.h
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

# Линкуем Qt6
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Sql
    Qt6::Network
    PostgreSQL::PostgreSQL
)

# Для Linux: добавить пути к Qt6
target_include_directories(${PROJECT_NAME} PRIVATE
    ${Qt6Core_INCLUDE_DIRS}
    ${Qt6Sql_INCLUDE_DIRS}
    ${Qt6Network_INCLUDE_DIRS}
)
