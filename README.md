# Stochastic Processes and Option Pricing

In this repository, we explore the application of stochastic processes, specifically Geometric Brownian Motion (GBM), in option pricing.

## Theory of Geometric Brownian Motion

Geometric Brownian Motion (GBM) is defined by the stochastic differential equation:

$$ dS_t = \mu S_t dt + \sigma S_t dW_t $$

where:
- \( S_t \) is the asset price at time \( t \),
- \( \mu \) is the drift rate (expected return of the asset),
- \( \sigma \) is the volatility (standard deviation of the asset's returns),
- \( W_t \) is a Wiener process (standard Brownian motion).

The solution to this SDE is:

$$ S_t = S_0 \exp \left( \left( \mu - \frac{\sigma^2}{2} \right)t + \sigma W_t \right) $$

## Option Pricing using GBM

To price European options under GBM, we simulate the asset price using Monte Carlo methods. The price of a European Call option can be estimated as:

$$ C(S_0, K, r, \sigma, T) = e^{-rT} \mathbb{E} \left[ \max(S_T - K, 0) \right] $$

where:
- \( S_0 \) is the initial stock price,
- \( K \) is the strike price,
- \( r \) is the risk-free interest rate,
- \( \sigma \) is the volatility,
- \( T \) is the time to expiration,
- \( S_T \) is the asset price at expiration,
- \( \mathbb{E} \) denotes the expectation operator.

## Repository Contents

- `main.cpp`: C++ implementation of GBM for option pricing.
- `README.md`: This file providing an overview of the project.

## Usage

Clone the repository and compile `main.cpp` using a C++ compiler. Run the executable to calculate the European Call option price based on specified parameters.

```bash
g++ main.cpp -o option_pricing
./option_pricing
```
## Results
The C++ program will output the European Call option price based on the parameters set in main.cpp.


