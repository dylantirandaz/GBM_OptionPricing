#include "option.h"
#include "european_option.h"
#include "asian_option.h"
#include "monte_carlo.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

int main() {
    try {
        double S0 = 100.0;          
        double K = 100.0;           
        double r = 0.05;            
        double volatility = 0.2;    
        double T = 1.0;             

        int num_simulations = 100000;
        int num_time_steps = 252;  

        std::cout << "=== Option Pricing using Monte Carlo Simulation ===" << std::endl;
        std::cout << "Parameters:" << std::endl;
        std::cout << "  Initial Stock Price (S0): $" << S0 << std::endl;
        std::cout << "  Strike Price (K): $" << K << std::endl;
        std::cout << "  Risk-free Rate (r): " << (r * 100) << "%" << std::endl;
        std::cout << "  Volatility (σ): " << (volatility * 100) << "%" << std::endl;
        std::cout << "  Time to Expiration (T): " << T << " year(s)" << std::endl;
        std::cout << "  Monte Carlo Simulations: " << num_simulations << std::endl;
        std::cout << "  Time Steps: " << num_time_steps << std::endl;
        std::cout << std::endl;

        EuropeanOption euro_call(S0, K, r, volatility, T, 'C');
        EuropeanOption euro_put(S0, K, r, volatility, T, 'P');
        AsianOption asian_call(S0, K, r, volatility, T, 'C');
        AsianOption asian_put(S0, K, r, volatility, T, 'P');

        MonteCarlo mc(num_simulations, num_time_steps);
        mc.setSeed(42);  

        std::cout << "Calculating prices..." << std::endl;
        
        double euro_call_mc = euro_call.price();
        double euro_put_mc = euro_put.price();
        double euro_call_bs = euro_call.blackScholesPrice();
        double euro_put_bs = euro_put.blackScholesPrice();
        
        double asian_call_price = asian_call.price();
        double asian_put_price = asian_put.price();

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "\n=== EUROPEAN OPTIONS ===" << std::endl;
        std::cout << "European Call Option:" << std::endl;
        std::cout << "  Monte Carlo Price: $" << euro_call_mc << std::endl;
        std::cout << "  Black-Scholes Price: $" << euro_call_bs << std::endl;
        std::cout << "  Difference: $" << std::abs(euro_call_mc - euro_call_bs) << std::endl;
        
        std::cout << "\nEuropean Put Option:" << std::endl;
        std::cout << "  Monte Carlo Price: $" << euro_put_mc << std::endl;
        std::cout << "  Black-Scholes Price: $" << euro_put_bs << std::endl;
        std::cout << "  Difference: $" << std::abs(euro_put_mc - euro_put_bs) << std::endl;

        std::cout << "\n=== ASIAN OPTIONS ===" << std::endl;
        std::cout << "Asian Call Option Price: $" << asian_call_price << std::endl;
        std::cout << "Asian Put Option Price: $" << asian_put_price << std::endl;

        double put_call_parity_lhs = euro_call_bs + K * std::exp(-r * T);
        double put_call_parity_rhs = euro_put_bs + S0;
        std::cout << "\n=== PUT-CALL PARITY VERIFICATION ===" << std::endl;
        std::cout << "C + K*e^(-rT) = " << put_call_parity_lhs << std::endl;
        std::cout << "P + S0 = " << put_call_parity_rhs << std::endl;
        std::cout << "Difference: " << std::abs(put_call_parity_lhs - put_call_parity_rhs) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }

    return 0;
}
