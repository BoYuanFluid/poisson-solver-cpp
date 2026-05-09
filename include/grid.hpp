#pragma once

#include <vector>

class Grid {
public:
    Grid(int nx, int ny);

    double& operator()(int i, int j);

    void print_info() const;

private:
    int nx_;
    int ny_;

    std::vector<double> data_;
};