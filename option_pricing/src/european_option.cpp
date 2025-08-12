#include "european_option.h"
#include "monte_carlo.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

EuropeanOption::EuropeanOption(double S0_, double K_, double r_, double volatility_, double T_, char type_)
    : Option(S0_, K_, r_, volatility_, T_), type(type_) {
    validateInputs();
}

EuropeanOption::~EuropeanOption() {}

void EuropeanOption::validateInputs() const {
    if (type != 'C' && type != 'P') {
        throw std::invalid_argument("Option type must be 'C' (Call) or 'P' (Put)");
    }
}

double EuropeanOption::price() const {
    MonteCarlo mc(100000, 252);
    return mc.simulateEuropean(S0, K, r, volatility, T, type);
}

double EuropeanOption::blackScholesPrice() const {
    //Black-Scholes analytical formula for verification
    double d1 = (std::log(S0 / K) + (r + 0.5 * volatility * volatility) * T) / (volatility * std::sqrt(T));
    double d2 = d1 - volatility * std::sqrt(T);
    
    double N_d1 = cumulativeNormal(d1);
    double N_d2 = cumulativeNormal(d2);
    double N_minus_d1 = cumulativeNormal(-d1);
    double N_minus_d2 = cumulativeNormal(-d2);
    
    if (type == 'C') {
        //Call option: C = S0 * N(d1) - K * exp(-rT) * N(d2)
        return S0 * N_d1 - K * std::exp(-r * T) * N_d2;
    } else {
        //Put option: P = K * exp(-rT) * N(-d2) - S0 * N(-d1)
        return K * std::exp(-r * T) * N_minus_d2 - S0 * N_minus_d1;
    }
}

double EuropeanOption::cumulativeNormal(double x) const {
    //approximation of cumulative standard normal distribution sing abramowitz and stegun approximation
    const double a1 =  0.254829592;
    const double a2 = -0.284496736;
    const double a3 =  1.421413741;
    const double a4 = -1.453152027;
    const double a5 =  1.061405429;
    const double p  =  0.3275911;
    
    int sign = 1;
    if (x < 0) sign = -1;
    x = std::abs(x) / std::sqrt(2.0);
    
    //A&S formula 7.1.26
    double t = 1.0 / (1.0 + p * x);
    double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * std::exp(-x * x);
    
    return 0.5 * (1.0 + sign * y);
}
