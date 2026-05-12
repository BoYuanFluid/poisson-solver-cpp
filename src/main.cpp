#include <iostream>

#include "grid.hpp"
#include "poisson_solver.hpp"

int main() {
    std::cout << "Poisson Solver Starting..." << std::endl;

    Grid u(5, 4);

    u.print_info();

    // Initializing
    for (int j = 0; j < u.ny(); ++j) {
        for (int i = 0; i < u.nx(); ++i) {
            u(i, j) = 0.0;
        }
    }

    // Setting boundaries
    for (int i = 0; i < u.nx(); ++i) {
        u(i, u.ny() - 1) = 1.0;
    }

    for (int j = 0; j < u.ny(); ++j) {
        for (int i = 0; i < u.nx(); ++i) {
            std::cout << u(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // std::cout << "u(2, 1) = "
    //           << u(2,1)
    //           << std::endl;

    run_poisson_solver(u);

    std::cout << std::endl;
    std::cout << "Final solution: " << std::endl;
    for (int j = 0; j < u.ny(); ++j) {
        for (int i = 0; i < u.nx(); ++i) {
            std::cout << u(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}