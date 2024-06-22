#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include "option.h"

class MonteCarlo {
private:
    int num_simulations;    // Number of Monte Carlo simulations

public:
    MonteCarlo(int num_simulations_);
    ~MonteCarlo();

    // Function to simulate GBM and calculate option price
    double simulate(const Option& option) const;
};

#endif // MONTE_CARLO_H
