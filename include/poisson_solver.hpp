#pragma once

#include "grid.hpp"

void run_poisson_solver(Grid& u);

double compute_max_residual(const Grid& u);