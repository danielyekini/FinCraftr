/**
 * Example usage of FinCraftr C++ library demonstrating header-only functions.
 * 
 * Compile with:
 *   g++ -std=c++20 -I cpp/include example_usage.cpp -o example_usage
 * 
 * Or using CMake after installation:
 *   find_package(fincraftr CONFIG REQUIRED)
 *   target_link_libraries(myapp PRIVATE fincraftr::fincraftr)
 */

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

void equity_analysis_example() {
    std::cout << "=== Equity Analysis ===\n";
    
    // Stock returns
    double initial_price = 100.0;
    double final_price = 105.0;
    double simple_return = fc::equity::return_simple(final_price, initial_price);
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Simple return from $" << initial_price << " to $" << final_price 
              << ": " << simple_return << " (" << simple_return * 100 << "%)\n";
    
    // Market cap calculation
    double shares_outstanding = 1'000'000;
    double current_price = 50.0;
    double market_cap = fc::equity::market_cap(shares_outstanding, current_price);
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Market cap: " << shares_outstanding << " shares × $" << current_price 
              << " = $" << market_cap << "\n";
    
    // Dividend discount model (Gordon growth)
    double next_dividend = 2.50;
    double required_return = 0.10;
    double growth_rate = 0.03;
    double fair_value = fc::equity::ddm_gordon_growth(next_dividend, required_return, growth_rate);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Gordon growth model fair value: $" << fair_value << "\n\n";
}

void options_analysis_example() {
    std::cout << "=== Options Analysis ===\n";
    
    // Option payoffs
    double stock_price_expiry = 105.0;
    double strike_price = 100.0;
    
    double call_payoff = fc::options::payoff_call(stock_price_expiry, strike_price);
    double put_payoff = fc::options::payoff_put(stock_price_expiry, strike_price);
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "At expiry: S=$" << stock_price_expiry << ", K=$" << strike_price << "\n";
    std::cout << "Call payoff: $" << call_payoff << "\n";
    std::cout << "Put payoff: $" << put_payoff << "\n";
    
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
    std::cout << "Put-call parity check: " << (parity_holds ? "✓ Holds" : "✗ Violated") << "\n\n";
}

void rates_analysis_example() {
    std::cout << "=== Interest Rates ===\n";
    
    // Compounding
    double principal = 10'000.0;
    double annual_rate = 0.06;
    double years = 5.0;
    
    // Discrete compounding (quarterly)
    int quarterly_periods = 4;
    double discrete_value = fc::rates::compound_discrete(principal, annual_rate, quarterly_periods, years);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "$" << principal << " @ " << annual_rate * 100 << "% for " << years 
              << " years (quarterly): $" << discrete_value << "\n";
    
    // Continuous compounding
    double continuous_value = fc::rates::compound_continuous(principal, annual_rate, years);
    std::cout << "$" << principal << " @ " << annual_rate * 100 << "% for " << years 
              << " years (continuous): $" << continuous_value << "\n";
    
    // Rate conversions
    double nominal_rate = 0.06;
    double continuous_equiv = fc::rates::nominal_to_continuous(nominal_rate, quarterly_periods);
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Nominal " << nominal_rate * 100 << "% (quarterly) = " 
              << continuous_equiv * 100 << "% (continuous)\n";
    
    // Present value / discounting
    double future_value = 15'000.0;
    double discount_rate = 0.08;
    double time_periods = 3.0;
    double present_value = fc::rates::roll_back_cont(future_value, discount_rate, time_periods);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "PV of $" << future_value << " in " << time_periods 
              << " years @ " << discount_rate * 100 << "%: $" << present_value << "\n\n";
}

void forwards_analysis_example() {
    std::cout << "=== Forward Contracts ===\n";
    
    double spot_price = 100.0;
    double risk_free_rate = 0.04;
    double time_to_maturity = 0.5;  // 6 months
    
    // Forward without dividends
    double forward_no_div = fc::forwards::forward_price_no_div(spot_price, risk_free_rate, time_to_maturity);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Forward price (no dividends): $" << forward_no_div << "\n";
    
    // Forward with discrete dividend
    double dividend_pv = 2.0;  // Present value of dividends
    double forward_with_div = fc::forwards::forward_price_with_div(spot_price, dividend_pv, risk_free_rate, time_to_maturity);
    std::cout << "Forward price (with $" << dividend_pv << " dividend): $" << forward_with_div << "\n";
    
    // Forward with continuous yield
    double dividend_yield = 0.02;  // 2% continuous yield
    double forward_cont_yield = fc::forwards::forward_price_cont_yield(spot_price, risk_free_rate, dividend_yield, time_to_maturity);
    std::cout << "Forward price (with " << dividend_yield * 100 << "% yield): $" << forward_cont_yield << "\n\n";
}

int main() {
    std::cout << "FinCraftr C++ Usage Examples\n";
    std::cout << std::string(50, '=') << "\n";
    std::cout << "Header-only C++20 quantitative finance functions\n\n";
    
    try {
        equity_analysis_example();
        options_analysis_example();
        rates_analysis_example();
        forwards_analysis_example();
        
        std::cout << "🎉 All examples completed successfully!\n";
        std::cout << "\nNote: These are the same functions available in Python via pybind11 bindings.\n";
        std::cout << "The library supports both header-only and compiled library usage.\n";
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error running examples: " << e.what() << "\n";
        std::cerr << "Make sure FinCraftr headers are in your include path.\n";
        return 1;
    }
    
    return 0;
}
