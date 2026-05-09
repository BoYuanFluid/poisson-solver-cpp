cmake_minimum_required(VERSION 3.15)

project(poisson_solver_cpp)

add_executable(poisson_solver
    src/main.cpp
    src/poisson_solver.cpp
    src/grid.cpp
)

target_include_directories(poisson_solver PRIVATE include)