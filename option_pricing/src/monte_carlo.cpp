#include "monte_carlo.h"
#include <cmath>
#include <iostream>

MonteCarlo::MonteCarlo(int num_simulations_)
    : num_simulations(num_simulations_) {}

MonteCarlo::~MonteCarlo() {}

double MonteCarlo::simulate(const Option& option) const {
    return option.price();
}

// Private function to simulate Geometric Brownian Motion (GBM)
double MonteCarlo::geometric_brownian_motion(double S0, double drift, double volatility, double T, double dt) const {
    double S = S0;
    for (double t = 0; t < T; t += dt) {
        double W = random_normal(0.0, 1.0);
        S *= exp((drift - 0.5 * volatility * volatility) * dt + volatility * sqrt(dt) * W);
    }
    return S;
}
