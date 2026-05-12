#include <iostream>

#include "poisson_solver.hpp"

void run_poisson_solver(Grid& u) {
    Grid u_new(u.nx(), u.ny());

    int max_iters = 10;

    for (int iter = 0; iter < max_iters; ++iter) {
        for (int j = 1; j < u.ny() - 1; ++j) {
            for (int i = 1; i < u.nx() - 1; ++i) {
                u_new(i, j) = 0.25 * (u(i+1, j) + u(i-1, j)
                                    + u(i, j+1) + u(i, j-1));
            }
        }

        for (int j = 1; j < u.ny() - 1; ++j) {
            for (int i = 1; i < u.nx() - 1; ++i) {
                u(i, j) = u_new(i, j);
            }
        }

        std :: cout << "Iteration "
                    << iter
                    << " completed."
                    << std::endl;
    }

}

    
