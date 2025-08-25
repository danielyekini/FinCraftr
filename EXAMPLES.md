# FinCraftr Usage Examples

This document provides comprehensive examples of using FinCraftr in both Python and C++ for common quantitative finance tasks.

## 📊 Overview

FinCraftr provides parallel APIs in both Python and C++ for:
- **Equity Analysis**: Returns, valuations, market cap calculations
- **Options Pricing**: Payoffs, binomial models, put-call parity
- **Interest Rates**: Compounding, discounting, rate conversions  
- **Forward Contracts**: Pricing with and without dividends

---

## 🐍 Python Examples

### Installation
```bash
pip install fincraftr
```

### Basic Import and Setup
```python
import fincraftr as fc
import numpy as np

# FinCraftr provides both top-level convenience functions
# and module-specific access for organized code
```

### 1. Equity Analysis

#### Simple Returns Calculation
```python
# Calculate simple returns for a stock price movement
initial_price = 100.0
final_price = 105.0

simple_return = fc.return_simple(final_price, initial_price)
print(f"Simple return: {simple_return:.4f} ({simple_return*100:.2f}%)")
# Output: Simple return: 0.0500 (5.00%)

# Using module access for clarity
return_val = fc.equity.return_simple(110.0, 100.0)
print(f"10% price increase return: {return_val:.4f}")
# Output: 10% price increase return: 0.1000
```

#### Market Capitalization
```python
# Calculate market cap for a publicly traded company
shares_outstanding = 1_000_000
current_price = 50.25

market_cap = fc.equity.market_cap(shares_outstanding, current_price)
print(f"Market cap: ${market_cap:,.0f}")
# Output: Market cap: $50,250,000

# Ownership calculation
shares_owned = 25_000
ownership_pct = fc.equity.ownership_fraction(shares_owned, shares_outstanding)
print(f"Ownership: {ownership_pct:.1%}")
# Output: Ownership: 2.5%
```

#### Dividend Discount Model (Gordon Growth)
```python
# Value a stock using the Gordon growth model
next_dividend = 2.50        # Next year's expected dividend
required_return = 0.10      # 10% required return
growth_rate = 0.03          # 3% perpetual growth

fair_value = fc.equity.ddm_gordon_growth(next_dividend, required_return, growth_rate)
print(f"Gordon growth model fair value: ${fair_value:.2f}")
# Output: Gordon growth model fair value: $35.71

# Compare with current market price
market_price = 32.00
if fair_value > market_price:
    print(f"Stock appears undervalued by ${fair_value - market_price:.2f}")
else:
    print(f"Stock appears overvalued by ${market_price - fair_value:.2f}")
```

### 2. Options Analysis

#### Option Payoffs at Expiration
```python
# Calculate payoffs for European options
stock_price_at_expiry = 105.0
strike_price = 100.0

# Call option payoff
call_payoff = fc.options.payoff_call(stock_price_at_expiry, strike_price)
print(f"Call option payoff: ${call_payoff:.2f}")
# Output: Call option payoff: $5.00

# Put option payoff  
put_payoff = fc.options.payoff_put(stock_price_at_expiry, strike_price)
print(f"Put option payoff: ${put_payoff:.2f}")
# Output: Put option payoff: $0.00

# Test with different scenarios
scenarios = [90, 95, 100, 105, 110]
print("\\nPayoff Analysis:")
print("Stock Price | Call Payoff | Put Payoff")
print("-" * 38)
for price in scenarios:
    call = fc.options.payoff_call(price, strike_price)
    put = fc.options.payoff_put(price, strike_price)
    print(f"    ${price:3.0f}    |    ${call:5.2f}   |   ${put:5.2f}")
```

#### Put-Call Parity Verification
```python
# Verify put-call parity relationship
call_price = 8.0
put_price = 3.0
current_stock = 100.0
strike = 100.0
risk_free_rate = 0.05
time_to_expiry = 1.0  # 1 year

parity_holds = fc.options.check_put_call_parity(
    call_price, put_price, current_stock, strike, 
    risk_free_rate, time_to_expiry
)

print(f"Put-call parity {'✓ holds' if parity_holds else '✗ violated'}")

# Calculate theoretical values for comparison
import math
pv_strike = strike * math.exp(-risk_free_rate * time_to_expiry)
theoretical_difference = call_price - put_price
actual_difference = current_stock - pv_strike
print(f"Theoretical C-P: ${theoretical_difference:.2f}")
print(f"Actual S-PV(K): ${actual_difference:.2f}")
```

### 3. Interest Rates and Discounting

#### Compound Interest Calculations
```python
# Compare different compounding frequencies
principal = 10_000.0
annual_rate = 0.06
years = 5.0

# Quarterly compounding
quarterly_value = fc.rates.compound_discrete(principal, annual_rate, 4, years)
print(f"Quarterly compounding: ${quarterly_value:,.2f}")
# Output: Quarterly compounding: $13,468.55

# Continuous compounding
continuous_value = fc.rates.compound_continuous(principal, annual_rate, years)
print(f"Continuous compounding: ${continuous_value:,.2f}")
# Output: Continuous compounding: $13,498.59

# Compare the difference
difference = continuous_value - quarterly_value
print(f"Continuous vs Quarterly difference: ${difference:.2f}")
```

#### Present Value Calculations
```python
# Discount future cash flows to present value
future_value = 15_000.0
discount_rate = 0.08
time_periods = 3.0

present_value = fc.rates.roll_back_cont(future_value, discount_rate, time_periods)
print(f"PV of ${future_value:,.0f} in {time_periods} years: ${present_value:,.2f}")
# Output: PV of $15,000 in 3.0 years: $11,836.24

# Verify by rolling forward
verification = fc.rates.roll_forward_cont(present_value, discount_rate, time_periods)
print(f"Verification (should equal ${future_value:,.0f}): ${verification:,.2f}")
```

#### Interest Rate Conversions
```python
# Convert between nominal and continuous rates
nominal_rate = 0.06
compounding_frequency = 4  # Quarterly

continuous_rate = fc.rates.nominal_to_continuous(nominal_rate, compounding_frequency)
print(f"Nominal {nominal_rate:.1%} (quarterly) = {continuous_rate:.4f} (continuous)")

# Convert back to verify
back_to_nominal = fc.rates.continuous_to_nominal(continuous_rate, compounding_frequency)
print(f"Verification: {back_to_nominal:.6f} ≈ {nominal_rate:.6f}")
```

### 4. Forward Contract Pricing

#### Forward Pricing Scenarios
```python
# Basic forward pricing without dividends
spot_price = 100.0
risk_free_rate = 0.04
time_to_maturity = 0.5  # 6 months

forward_no_div = fc.forwards.forward_price_no_div(spot_price, risk_free_rate, time_to_maturity)
print(f"Forward price (no dividends): ${forward_no_div:.2f}")
# Output: Forward price (no dividends): $102.02

# Forward pricing with discrete dividend
dividend_pv = 2.0  # Present value of dividends
forward_with_div = fc.forwards.forward_price_with_div(
    spot_price, dividend_pv, risk_free_rate, time_to_maturity
)
print(f"Forward price (with ${dividend_pv} dividend): ${forward_with_div:.2f}")
# Output: Forward price (with $2.0 dividend): $100.02

# Forward pricing with continuous dividend yield
dividend_yield = 0.02  # 2% continuous yield
forward_cont_yield = fc.forwards.forward_price_cont_yield(
    spot_price, risk_free_rate, dividend_yield, time_to_maturity
)
print(f"Forward price (with {dividend_yield:.1%} yield): ${forward_cont_yield:.2f}")
```

### 5. Portfolio Analysis Example
```python
# Comprehensive portfolio analysis combining multiple modules
def analyze_portfolio():
    """Analyze a simple stock and options portfolio."""
    
    # Portfolio positions
    stock_shares = 1000
    call_contracts = 5  # Each contract = 100 shares
    stock_price = 50.0
    call_strike = 55.0
    
    # Market parameters
    risk_free_rate = 0.03
    time_to_expiry = 0.25  # 3 months
    
    # Calculate portfolio value
    stock_value = stock_shares * stock_price
    
    # Estimate call value using forward pricing as approximation
    forward_price = fc.forwards.forward_price_no_div(stock_price, risk_free_rate, time_to_expiry)
    call_intrinsic = max(0, forward_price - call_strike)
    call_value = call_contracts * 100 * call_intrinsic  # Simplified valuation
    
    total_value = stock_value + call_value
    
    print("Portfolio Analysis")
    print("-" * 30)
    print(f"Stock position: {stock_shares} shares @ ${stock_price}")
    print(f"Stock value: ${stock_value:,.2f}")
    print(f"Call options: {call_contracts} contracts, strike ${call_strike}")
    print(f"Estimated call value: ${call_value:,.2f}")
    print(f"Total portfolio value: ${total_value:,.2f}")
    
    # Scenario analysis
    price_scenarios = [45, 50, 55, 60, 65]
    print(f"\\nScenario Analysis (at expiry):")
    print("Stock Price | Portfolio Value | Return")
    print("-" * 40)
    
    for scenario_price in price_scenarios:
        stock_val = stock_shares * scenario_price
        call_payoff = fc.options.payoff_call(scenario_price, call_strike)
        call_val = call_contracts * 100 * call_payoff
        portfolio_val = stock_val + call_val
        portfolio_return = (portfolio_val - total_value) / total_value
        
        print(f"    ${scenario_price:2.0f}     |    ${portfolio_val:8,.0f}    | {portfolio_return:6.1%}")

# Run the analysis
analyze_portfolio()
```

---

## 🔧 C++ Examples

### Installation
```bash
# Using vcpkg
vcpkg install fincraftr

# Or add to vcpkg.json
{"dependencies": ["fincraftr"]}
```

### CMakeLists.txt Setup
```cmake
cmake_minimum_required(VERSION 3.20)
project(fincraftr_examples)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fincraftr CONFIG REQUIRED)

add_executable(examples main.cpp)
target_link_libraries(examples PRIVATE fincraftr::fincraftr)
```

### Complete C++ Example Program

Create a file `main.cpp`:

```cpp
#include <iostream>
#include <iomanip>
#include <vector>

// Include FinCraftr headers
#include <fincraftr/equity/returns.hpp>
#include <fincraftr/equity/basic.hpp>
#include <fincraftr/equity/valuation.hpp>
#include <fincraftr/options/payoff.hpp>
#include <fincraftr/options/parity.hpp>
#include <fincraftr/rates/compounding.hpp>
#include <fincraftr/rates/discount.hpp>
#include <fincraftr/rates/conversions.hpp>
#include <fincraftr/forwards/pricing.hpp>

int main() {
    std::cout << std::fixed << std::setprecision(4);
    
    // 1. Equity Analysis
    std::cout << "=== Equity Analysis ===\\n";
    
    double initial_price = 100.0;
    double final_price = 105.0;
    double simple_return = fc::equity::return_simple(final_price, initial_price);
    std::cout << "Simple return from $" << initial_price << " to $" << final_price 
              << ": " << simple_return << " (" << simple_return * 100 << "%)\\n";
    
    // Market cap calculation
    double shares_outstanding = 1'000'000;
    double current_price = 50.0;
    double market_cap = fc::equity::market_cap(shares_outstanding, current_price);
    std::cout << "Market cap: " << shares_outstanding << " shares × $" << current_price 
              << " = $" << market_cap << "\\n";
    
    // Gordon growth model
    double next_dividend = 2.50;
    double required_return = 0.10;
    double growth_rate = 0.03;
    double fair_value = fc::equity::ddm_gordon_growth(next_dividend, required_return, growth_rate);
    std::cout << "Gordon growth model fair value: $" << fair_value << "\\n\\n";
    
    // 2. Options Analysis
    std::cout << "=== Options Analysis ===\\n";
    
    double stock_price_expiry = 105.0;
    double strike_price = 100.0;
    
    double call_payoff = fc::options::payoff_call(stock_price_expiry, strike_price);
    double put_payoff = fc::options::payoff_put(stock_price_expiry, strike_price);
    
    std::cout << "At expiry: S=$" << stock_price_expiry << ", K=$" << strike_price << "\\n";
    std::cout << "Call payoff: $" << call_payoff << "\\n";
    std::cout << "Put payoff: $" << put_payoff << "\\n";
    
    // Put-call parity check
    double call_price = 8.0;
    double put_price = 3.0;
    double current_stock = 100.0;
    double risk_free_rate = 0.05;
    double time_to_expiry = 1.0;
    
    bool parity_holds = fc::options::check_put_call_parity(
        call_price, put_price, current_stock, strike_price, 
        risk_free_rate, time_to_expiry
    );
    std::cout << "Put-call parity check: " << (parity_holds ? "✓ Holds" : "✗ Violated") << "\\n\\n";
    
    // 3. Interest Rates Analysis
    std::cout << "=== Interest Rates ===\\n";
    
    double principal = 10'000.0;
    double annual_rate = 0.06;
    double years = 5.0;
    
    // Discrete compounding (quarterly)
    int quarterly_periods = 4;
    double discrete_value = fc::rates::compound_discrete(principal, annual_rate, quarterly_periods, years);
    std::cout << "$" << principal << " @ " << annual_rate * 100 << "% for " << years 
              << " years (quarterly): $" << discrete_value << "\\n";
    
    // Continuous compounding
    double continuous_value = fc::rates::compound_continuous(principal, annual_rate, years);
    std::cout << "$" << principal << " @ " << annual_rate * 100 << "% for " << years 
              << " years (continuous): $" << continuous_value << "\\n";
    
    // Rate conversions
    double nominal_rate = 0.06;
    double continuous_equiv = fc::rates::nominal_to_continuous(nominal_rate, quarterly_periods);
    std::cout << "Nominal " << nominal_rate * 100 << "% (quarterly) = " 
              << continuous_equiv * 100 << "% (continuous)\\n";
    
    // Present value / discounting
    double future_value = 15'000.0;
    double discount_rate = 0.08;
    double time_periods = 3.0;
    double present_value = fc::rates::roll_back_cont(future_value, discount_rate, time_periods);
    std::cout << "PV of $" << future_value << " in " << time_periods 
              << " years @ " << discount_rate * 100 << "%: $" << present_value << "\\n\\n";
    
    // 4. Forward Contracts
    std::cout << "=== Forward Contracts ===\\n";
    
    double spot_price = 100.0;
    double forward_risk_free_rate = 0.04;
    double time_to_maturity = 0.5;  // 6 months
    
    // Forward without dividends
    double forward_no_div = fc::forwards::forward_price_no_div(spot_price, forward_risk_free_rate, time_to_maturity);
    std::cout << "Forward price (no dividends): $" << forward_no_div << "\\n";
    
    // Forward with discrete dividend
    double dividend_pv = 2.0;  // Present value of dividends
    double forward_with_div = fc::forwards::forward_price_with_div(spot_price, dividend_pv, forward_risk_free_rate, time_to_maturity);
    std::cout << "Forward price (with $" << dividend_pv << " dividend): $" << forward_with_div << "\\n";
    
    // Forward with continuous yield
    double dividend_yield = 0.02;  // 2% continuous yield
    double forward_cont_yield = fc::forwards::forward_price_cont_yield(spot_price, forward_risk_free_rate, dividend_yield, time_to_maturity);
    std::cout << "Forward price (with " << dividend_yield * 100 << "% yield): $" << forward_cont_yield << "\\n\\n";
    
    std::cout << "🎉 All FinCraftr examples completed successfully!\\n";
    std::cout << "\\nNote: These functions are also available in Python via 'pip install fincraftr'\\n";
    
    return 0;
}
```

### Build and Run
```bash
mkdir build && cd build
cmake ..
cmake --build .
./examples  # or examples.exe on Windows
```

---

## 📚 Additional Resources

### Key Concepts

1. **Header-Only Design**: All C++ functions are implemented in headers for easy integration
2. **Parallel APIs**: Same function signatures and behavior in both Python and C++
3. **Pure Functions**: No hidden state - all inputs explicit, deterministic outputs
4. **Industry Standards**: Follows quantitative finance conventions and best practices

### Performance Notes

- **C++ Version**: Zero-overhead abstractions, compile-time optimizations
- **Python Version**: Uses compiled C++ extensions via pybind11 for performance
- **Fallback Mode**: Pure Python implementations available if C++ extension fails to load

### Error Handling

Both APIs use similar error handling:
- **C++**: Exceptions for invalid inputs (e.g., division by zero, negative time periods)
- **Python**: Same exceptions, plus Python-specific `ValueError` and `TypeError`

### Next Steps

1. **Explore Modules**: Each module has additional functions beyond these examples
2. **Read Documentation**: Use `help()` in Python or check header comments in C++
3. **Integration**: Combine FinCraftr with your existing analysis pipelines
4. **Contribute**: Submit issues or PRs on GitHub for improvements

---

*For more examples and advanced usage, see the full API documentation and test files in the repository.*
