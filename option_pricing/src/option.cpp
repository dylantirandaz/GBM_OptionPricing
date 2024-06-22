#include "option.h"

Option::Option(double S0_, double K_, double r_, double volatility_, double T_)
    : S0(S0_), K(K_), r(r_), volatility(volatility_), T(T_) {}

Option::~Option() {}
