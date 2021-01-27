cmake_minimum_required(VERSION 3.16)
project(multithread-computations-task)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(multithread-computations-task
    main.cpp
    include/indicators_view.h
    include/computation.h
    include/matrix_multiplication.h
    src/indicators_view.cpp
    src/matrix_multiplication.cpp
)

target_link_libraries(multithread-computations-task PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
