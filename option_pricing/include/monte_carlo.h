#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include "option.h"
#include <vector>
#include <random>

class MonteCarlo {
private:
    int num_simulations;    
    int num_time_steps;    
    mutable std::mt19937 generator;  
    mutable std::normal_distribution<double> normal_dist;  

public:
    MonteCarlo(int num_simulations_, int num_time_steps_ = 252);
    ~MonteCarlo();

    double simulateEuropean(double S0, double K, double r, double volatility, double T, char type) const;
    
    double simulateAsian(double S0, double K, double r, double volatility, double T, char type = 'C') const;

    void setSeed(unsigned int seed);

private:
    std::vector<double> generateGBMPath(double S0, double drift, double volatility, double T) const;
    
    double randomNormal() const;
    
    void validateParameters(double S0, double K, double r, double volatility, double T) const;
};

#endif 
