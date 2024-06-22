#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H

#include "option.h"

class EuropeanOption : public Option {
private:
    char type;  // 'C' for Call, 'P' for Put

public:
    EuropeanOption(double S0_, double K_, double r_, double volatility_, double T_, char type_);
    virtual ~EuropeanOption();

    // Override to calculate European option price
    virtual double price() const override;
};

#endif // EUROPEAN_OPTION_H
