#include "option.h"
#include <stdexcept>

Option::Option(double S0_, double K_, double r_, double volatility_, double T_)
    : S0(S0_), K(K_), r(r_), volatility(volatility_), T(T_) {
    validateCommonInputs();
}

Option::~Option() {}

void Option::validateCommonInputs() const {
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
    if (T > 10) {
        throw std::invalid_argument("Time to expiration seems unreasonably large (>10 years)");
    }
    if (volatility > 5.0) {
        throw std::invalid_argument("Volatility seems unreasonably large (>500%)");
    }
}
