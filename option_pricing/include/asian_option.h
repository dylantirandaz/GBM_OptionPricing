#ifndef ASIAN_OPTION_H
#define ASIAN_OPTION_H

#include "option.h"

class AsianOption : public Option {
public:
    AsianOption(double S0_, double K_, double r_, double volatility_, double T_);
    virtual ~AsianOption();

    // Override to calculate Asian option price
    virtual double price() const override;
};

#endif // ASIAN_OPTION_H
