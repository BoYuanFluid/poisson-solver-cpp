#include <iostream>
#include <cmath>
#include <algorithm>

#include "poisson_solver.hpp"

void run_poisson_solver(Grid& u) {
    Grid u_new(u.nx(), u.ny());

    // int max_iters = 10;
    const int max_iters = 10000;
    const double tolerance = 1e-6;

    bool converged = false;
    double max_change = 0.0;

    for (int iter = 0; iter < max_iters; ++iter) {
        for (int j = 1; j < u.ny() - 1; ++j) {
            for (int i = 1; i < u.nx() - 1; ++i) {
                u_new(i, j) = 0.25 * (u(i+1, j) + u(i-1, j)
                                    + u(i, j+1) + u(i, j-1));
            }
        }

        max_change = 0.0;
        for (int j = 1; j < u.ny() - 1; ++j) {
            for (int i = 1; i < u.nx() - 1; ++i) {
                double change = std::abs(u_new(i,j) - u(i,j));
                max_change = std::max(max_change, change);
                u(i, j) = u_new(i, j);
            }
        }

        double max_residual = compute_max_residual(u);

        if ((iter + 1) % 10 == 0 || max_change < tolerance) {
            std::cout << "Iteration " << iter + 1 << ", max change = " << max_change << ", max residual = " << max_residual << std::endl;
        }

        if (max_change < tolerance) {

            converged = true;
            std::cout << "Converged after " << iter + 1 << " iterations with max change: " << max_change << std::endl;
            break;
        }
    }

    if (!converged) {
        std::cout << "Warning: Solver did not converge after " << max_iters << " iterations. Final max change = " << max_change << '\n';
    }
}

    
double compute_max_residual(const Grid& u) {

    double max_residual = 0.0;

    for (int j = 1; j < u.ny() - 1; ++j) {
            for (int i = 1; i < u.nx() - 1; ++i) {
                double res = u(i+1, j) + u(i-1, j) + u(i, j+1) + u(i, j-1) - 4.0 * u(i, j);
                max_residual = std::max(max_residual, std::abs(res));
            }
        }

    return max_residual;

}