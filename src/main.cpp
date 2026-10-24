#include <iostream>
#include <cmath>
#include <vector>
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

    std::vector<double> errors;

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

        errors.push_back(error);

        std::cout << "Maximum error = " << error << '\n';

        std::cout << std::endl;

        std::cout << "Centre value: " << u(n / 2, n / 2) << '\n';

    }
    
    bool all_passed = true;

    const double expected_order = 2.0;
    const double order_tolerance = 0.1;

    for (std::size_t i = 1; i < errors.size(); ++i) {

        double p_rate = std::log(errors[i-1] / errors[i]) / std::log(2.0);

        std::cout << "Convergence rate between grid sizes " << grid_sizes[i-1] << " and " << grid_sizes[i] << ": " << p_rate << '\n';

        bool test_passed = std::isfinite(p_rate) &&
                std::abs(p_rate - expected_order) < order_tolerance;

        if (!test_passed) {
            all_passed = false;
            std::cout << "Failure: Convergence rate is not within the expected range. Expected: " << expected_order << ", Actual: " << p_rate << '\n';
        }
    }
    
    if (all_passed) {
        std::cout << "All numerical tests PASSED. \n";
    } else {
        std::cout << "Numerical tests FAILED. \n";
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


    return all_passed ? 0 : 1;
}