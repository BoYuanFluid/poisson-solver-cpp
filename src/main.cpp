#include <iostream>
#include <cmath>

#include <iomanip>
#include <algorithm>

#include "grid.hpp"
#include "poisson_solver.hpp"

double compute_max_error(const Grid& u, double h) {

    const double pi = std::acos(-1.0);
    double max_error = 0.0;

    for (int j = 0; j < u.ny(); ++j) {
        for (int i = 0; i < u.nx(); ++i) {
            double x = i * h;
            double y = j * h;
            double u_exact = std::sin(pi * x) * std::sin(pi * y);
            double error = std::abs(u(i, j) - u_exact);
            max_error = std::max(max_error, error);
        }
    }
    return max_error;
}

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

    const double pi = std::acos(-1.0);
    const int grid_sizes[] = {9, 17, 33};

    for (int n : grid_sizes) {
        const double h = 1.0 / (n - 1);
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
        run_poisson_solver(u, f, h);

        std::cout << "Grid: " << n << " x " << n << '\n';
        
        double error = compute_max_error(u, h);

        std::cout << "Maximum error = " << error << '\n';

        std::cout << std::endl;

        std::cout << "Centre value: " << u(n / 2, n / 2) << '\n';

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

    

    
    // std::cout << "Final solution: " << std::endl;
    // for (int j = 0; j < u.ny(); ++j) {
    //     for (int i = 0; i < u.nx(); ++i) {
    //         std::cout << u(i, j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    

    return 0;
}