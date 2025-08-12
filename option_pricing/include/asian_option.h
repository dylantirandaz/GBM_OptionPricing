#ifndef ASIAN_OPTION_H
#define ASIAN_OPTION_H

#include "option.h"
#include <stdexcept>

class AsianOption : public Option {
private:
    char type;  //'C' for Call,'P' for Put

public:
    AsianOption(double S0_, double K_, double r_, double volatility_, double T_, char type_ = 'C');
    virtual ~AsianOption();

    //override to calculate Asian option price using Monte Carlo
    virtual double price() const override;
    
    char getType() const { return type; }

private:
    void validateInputs() const;
};

#endif 
