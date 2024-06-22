#ifndef OPTION_H
#define OPTION_H

class Option {
protected:
    double S0;          // Initial stock price
    double K;           // Strike price
    double r;           // Risk-free interest rate
    double volatility;  // Volatility
    double T;           // Time to expiration (in years)

public:
    Option(double S0_, double K_, double r_, double volatility_, double T_);
    virtual ~Option();

    // Virtual function to calculate option price
    virtual double price() const = 0;
};

#endif // OPTION_H
