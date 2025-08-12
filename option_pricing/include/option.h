#ifndef OPTION_H
#define OPTION_H

#include <stdexcept>

class Option {
protected:
    double S0;          
    double K;           
    double r;           
    double volatility;  
    double T;           

public:
    Option(double S0_, double K_, double r_, double volatility_, double T_);
    virtual ~Option();

    virtual double price() const = 0;
    
    double getS0() const { return S0; }
    double getK() const { return K; }
    double getR() const { return r; }
    double getVolatility() const { return volatility; }
    double getT() const { return T; }

protected:
    void validateCommonInputs() const;
};

#endif 