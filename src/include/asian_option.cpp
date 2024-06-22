#include "asian_option.h"
#include <cmath>

AsianOption::AsianOption(double S0_, double K_, double r_, double volatility_, double T_)
    : Option(S0_, K_, r_, volatility_, T_) {}

AsianOption::~AsianOption() {}

double AsianOption::price() const {
    double dt = T;
    double discounted_expected_payoff = 0.0;

    for (int i = 0; i < num_simulations; ++i) {
        double S_T = geometric_brownian_motion(S0, r, volatility, T, dt);
        double payoff = std::max(S_T - K, 0.0);
        discounted_expected_payoff += payoff / num_simulations;
    }

    return exp(-r * T) * discounted_expected_payoff;
}
