#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

// Function to generate random numbers (standard normal distribution)
double random_normal(double mean, double stddev) {
    static std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}

// Function to simulate Geometric Brownian Motion (GBM)
double geometric_brownian_motion(double S0, double drift, double volatility, double T, double dt) {
    double S = S0;
    for (double t = 0; t < T; t += dt) {
        double W = random_normal(0.0, 1.0);
        S *= exp((drift - 0.5 * volatility * volatility) * dt + volatility * sqrt(dt) * W);
    }
    return S;
}

// Function to calculate European Call option price using GBM
double european_call_option_price(double S0, double K, double r, double volatility, double T) {
    // Parameters
    int num_simulations = 100000; // Number of Monte Carlo simulations
    double dt = T; // Time steps (assuming annualized)
    double discounted_expected_payoff = 0.0;

    // Simulate asset prices and calculate option payoffs
    for (int i = 0; i < num_simulations; ++i) {
        double S_T = geometric_brownian_motion(S0, r, volatility, T, dt);
        double payoff = max(S_T - K, 0.0); // Payoff for European Call option
        discounted_expected_payoff += payoff / num_simulations;
    }

    // Discounted expected payoff to present value
    double option_price = exp(-r * T) * discounted_expected_payoff;

    return option_price;
}

int main() {
    // Option parameters
    double S0 = 100.0; // Initial stock price
    double K = 100.0; // Strike price
    double r = 0.05; // Risk-free interest rate
    double volatility = 0.2; // Volatility
    double T = 1.0; // Time to expiration (in years)

    // Calculate European Call option price using GBM
    double call_price = european_call_option_price(S0, K, r, volatility, T);

    // Output the option price
    cout << fixed << setprecision(4);
    cout << "European Call Option Price: " << call_price << endl;

    return 0;
}
