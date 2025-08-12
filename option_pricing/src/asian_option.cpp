#include "asian_option.h"
#include "monte_carlo.h"
#include <cmath>
#include <stdexcept>

AsianOption::AsianOption(double S0_, double K_, double r_, double volatility_, double T_, char type_)
    : Option(S0_, K_, r_, volatility_, T_), type(type_) {
    validateInputs();
}

AsianOption::~AsianOption() {}

void AsianOption::validateInputs() const {
    if (type != 'C' && type != 'P') {
        throw std::invalid_argument("Option type must be 'C' (Call) or 'P' (Put)");
    }
}

double AsianOption::price() const {
    MonteCarlo mc(100000, 252);
    return mc.simulateAsian(S0, K, r, volatility, T, type);
}
