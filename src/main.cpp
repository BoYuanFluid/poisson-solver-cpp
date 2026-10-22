#include <iostream>
#include <cmath>

#include <iomanip>
#include <algorithm>

#include "grid.hpp"
#include "poisson_solver.hpp"

int main() {

    std::cout << std::scientific << std::setprecision(12);

    std::cout << "Poisson Solver Starting..." << std::endl;

    // Grid u(5, 4);

    // u.print_info();

    // // Initializing
    // for (int j = 0; j < u.ny(); ++j) {
    //     for (int i = 0; i < u.nx(); ++i) {
    //         u(i, j) = 0.0;
    //     }
    // }

    // // Setting boundaries
    // for (int i = 0; i < u.nx(); ++i) {
    //     u(i, u.ny() - 1) = 1.0;
    // }

    const int n = 33;
    const double h = 1.0 / (n - 1);

    const double pi = std::acos(-1.0);

    Grid u(n, n);
    Grid f(n ,n);

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
             double x = i * h;
             double y = j * h;

            //  Initial conditions and boundary values
            u(i ,j) = 0.0;

            // Source term
            f(i, j) = 2.0 * pi * pi * std::sin(pi * x) * std::sin(pi * y);
        }
    }

    // for (int j = 0; j < u.ny(); ++j) {
    //     for (int i = 0; i < u.nx(); ++i) {
    //         std::cout << u(i, j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "u(2, 1) = "
    //           << u(2,1)
    //           << std::endl;

    run_poisson_solver(u, f, h);

    std::cout << std::endl;
    // std::cout << "Final solution: " << std::endl;
    // for (int j = 0; j < u.ny(); ++j) {
    //     for (int i = 0; i < u.nx(); ++i) {
    //         std::cout << u(i, j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "Centre value: " << u(n / 2, n / 2) << '\n';

    return 0;
}