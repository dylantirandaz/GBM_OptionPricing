#include "monte_carlo.h"
#include <iostream>
#include <numeric>

MonteCarlo::MonteCarlo(int num_simulations_)
    : num_simulations(num_simulations_) {}

MonteCarlo::~MonteCarlo() {}

double MonteCarlo::simulate(const Option& option) const {
    return option.price();
}
