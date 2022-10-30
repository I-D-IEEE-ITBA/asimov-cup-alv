cmake_minimum_required(VERSION 3.0.0)
project(lap_chrono VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(lap_chrono main.cpp ../src/LapChrono.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
