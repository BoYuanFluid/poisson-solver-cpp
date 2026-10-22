#pragma once

#include "grid.hpp"

void run_poisson_solver(Grid& u, const Grid& f, double h);

double compute_max_residual(const Grid& u, const Grid& f, double h);