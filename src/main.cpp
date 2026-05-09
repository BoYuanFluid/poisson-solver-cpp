#include <iostream>

#include "grid.hpp"
#include "poisson_solver.hpp"

int main() {
    std::cout << "Poisson Solver Starting..." << std::endl;

    Grid u(5, 4);

    u.print_info();

    u(2, 1) = 3.14;

    std::cout << "u(2, 1) = "
              << u(2,1)
              << std::endl;

    run_poisson_solver();

    return 0;
}