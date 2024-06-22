#include "option.h"
#include "european_option.h"
#include "asian_option.h"
#include "monte_carlo.h"
#include <iostream>
#include <iomanip>

int main() {
    // Option parameters
    double S0 = 100.0;          // Initial stock price
    double K = 100.0;           // Strike price
    double r = 0.05;            // Risk-free interest rate
    double volatility = 0.2;    // Volatility
    double T = 1.0;             // Time to expiration (in years)

    // Number of Monte Carlo simulations
    int num_simulations = 100000;

    // Create European Call option instance
    EuropeanOption euro_call(S0, K, r, volatility, T, 'C');

    // Create Asian option instance
    AsianOption asian_option(S0, K, r, volatility, T);

    // Monte Carlo simulation object
    MonteCarlo mc(num_simulations);

    // Calculate option prices
    double euro_call_price = mc.simulate(euro_call);
    double asian_option_price = mc.simulate(asian_option);

    // Output results
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "European Call Option Price: " << euro_call_price << std::endl;
    std::cout << "Asian Option Price: " << asian_option_price << std::endl;

    return 0;
}
