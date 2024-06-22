#include "european_option.h"
#include <cmath>
#include <iostream>

EuropeanOption::EuropeanOption(double S0_, double K_, double r_, double volatility_, double T_, char type_)
    : Option(S0_, K_, r_, volatility_, T_), type(type_) {}

EuropeanOption::~EuropeanOption() {}

double EuropeanOption::price() const {
    double dt = T;
    double discounted_expected_payoff = 0.0;

    for (int i = 0; i < num_simulations; ++i) {
        double S_T = MonteCarlo::geometric_brownian_motion(S0, r, volatility, T, dt);
        double payoff = (type == 'C') ? std::max(S_T - K, 0.0) : std::max(K - S_T, 0.0);
        discounted_expected_payoff += payoff / num_simulations;
    }

    return exp(-r * T) * discounted_expected_payoff;
}
