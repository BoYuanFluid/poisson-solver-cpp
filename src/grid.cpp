#include <iostream>

#include "grid.hpp"

Grid::Grid(int nx, int ny)
    : nx_(nx), ny_(ny), data_(nx * ny, 0.0) 
{
}

double& Grid::operator()(int i, int j)
{
    return data_[j * nx_ + i];
}

void Grid::print_info() const
{
    std::cout << "Grid size: "
              << nx_ << " x " << ny_
              << std::endl;
}