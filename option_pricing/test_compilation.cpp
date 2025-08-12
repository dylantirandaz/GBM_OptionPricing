#include "include/option.h"
#include "include/european_option.h"
#include "include/asian_option.h" 
#include "include/monte_carlo.h"
#include <iostream>

int main() {
    try {
        EuropeanOption euro(100, 100, 0.05, 0.2, 1.0, 'C');
        AsianOption asian(100, 100, 0.05, 0.2, 1.0, 'C');
        MonteCarlo mc(1000, 10);
        
        std::cout << "Classes instantiated successfully!" << std::endl;
        std::cout << "European Call BS Price: " << euro.blackScholesPrice() << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
}
