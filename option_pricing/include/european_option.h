#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H

#include "option.h"
#include <stdexcept>

class EuropeanOption : public Option {
private:
    char type;  

public:
    EuropeanOption(double S0_, double K_, double r_, double volatility_, double T_, char type_);
    virtual ~EuropeanOption();

    virtual double price() const override;
    
    double blackScholesPrice() const;
    
    char getType() const { return type; }

private:
    void validateInputs() const;
    
    double cumulativeNormal(double x) const;
};

#endif // EUROPEAN_OPTION_H
