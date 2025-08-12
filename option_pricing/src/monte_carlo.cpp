#include "monte_carlo.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <numeric>

MonteCarlo::MonteCarlo(int num_simulations_, int num_time_steps_)
    : num_simulations(num_simulations_), num_time_steps(num_time_steps_), 
      generator(std::chrono::steady_clock::now().time_since_epoch().count()),
      normal_dist(0.0, 1.0) {
    
    if (num_simulations <= 0) {
        throw std::invalid_argument("Number of simulations must be positive");
    }
    if (num_time_steps <= 0) {
        throw std::invalid_argument("Number of time steps must be positive");
    }
}

MonteCarlo::~MonteCarlo() {}

void MonteCarlo::setSeed(unsigned int seed) {
    generator.seed(seed);
}

double MonteCarlo::simulateEuropean(double S0, double K, double r, double volatility, double T, char type) const {
    validateParameters(S0, K, r, volatility, T);
    
    if (type != 'C' && type != 'P') {
        throw std::invalid_argument("Option type must be 'C' (Call) or 'P' (Put)");
    }
    
    double sum_payoff = 0.0;
    
    for (int i = 0; i < num_simulations; ++i) {
        std::vector<double> path = generateGBMPath(S0, r, volatility, T);
        double S_T = path.back();  // Final price
        
        double payoff = 0.0;
        if (type == 'C') {
            payoff = std::max(S_T - K, 0.0);  
        } else {
            payoff = std::max(K - S_T, 0.0);  
        }
        
        sum_payoff += payoff;
    }
    
    return std::exp(-r * T) * (sum_payoff / num_simulations);
}

double MonteCarlo::simulateAsian(double S0, double K, double r, double volatility, double T, char type) const {
    validateParameters(S0, K, r, volatility, T);
    
    if (type != 'C' && type != 'P') {
        throw std::invalid_argument("Option type must be 'C' (Call) or 'P' (Put)");
    }
    
    double sum_payoff = 0.0;
    
    for (int i = 0; i < num_simulations; ++i) {
        std::vector<double> path = generateGBMPath(S0, r, volatility, T);
        
        double average_price = std::accumulate(path.begin(), path.end(), 0.0) / path.size();
        
        double payoff = 0.0;
        if (type == 'C') {
            payoff = std::max(average_price - K, 0.0);  
        } else {
            payoff = std::max(K - average_price, 0.0);  
        }
        
        sum_payoff += payoff;
    }
    
    return std::exp(-r * T) * (sum_payoff / num_simulations);
}

std::vector<double> MonteCarlo::generateGBMPath(double S0, double drift, double volatility, double T) const {
    std::vector<double> path;
    path.reserve(num_time_steps + 1);
    
    double dt = T / num_time_steps;
    double S = S0;
    path.push_back(S);  
    
    for (int i = 0; i < num_time_steps; ++i) {
        double W = randomNormal();
        S *= std::exp((drift - 0.5 * volatility * volatility) * dt + volatility * std::sqrt(dt) * W);
        path.push_back(S);
    }
    
    return path;
}

double MonteCarlo::randomNormal() const {
    return normal_dist(generator);
}

void MonteCarlo::validateParameters(double S0, double K, double r, double volatility, double T) const {
    if (S0 <= 0) {
        throw std::invalid_argument("Initial stock price must be positive");
    }
    if (K <= 0) {
        throw std::invalid_argument("Strike price must be positive");
    }
    if (r < 0) {
        throw std::invalid_argument("Risk-free rate cannot be negative");
    }
    if (volatility < 0) {
        throw std::invalid_argument("Volatility cannot be negative");
    }
    if (T <= 0) {
        throw std::invalid_argument("Time to expiration must be positive");
    }
}
