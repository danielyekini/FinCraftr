#!/usr/bin/env python3
"""
Example usage of FinCraftr demonstrating both Python and C++ API access.

This script shows how to use FinCraftr functions for common quantitative finance tasks.
"""

import fincraftr as fc

def equity_analysis_example():
    """Demonstrate equity analysis functions."""
    print("=== Equity Analysis ===")
    
    # Stock returns
    initial_price = 100.0
    final_price = 105.0
    simple_return = fc.equity.return_simple(final_price, initial_price)
    print(f"Simple return from ${initial_price} to ${final_price}: {simple_return:.4f} ({simple_return*100:.2f}%)")
    
    # Market cap calculation
    shares_outstanding = 1_000_000
    current_price = 50.0
    market_cap = fc.equity.market_cap(shares_outstanding, current_price)
    print(f"Market cap: {shares_outstanding:,} shares × ${current_price} = ${market_cap:,.0f}")
    
    # Dividend discount model (Gordon growth)
    next_dividend = 2.50
    required_return = 0.10
    growth_rate = 0.03
    fair_value = fc.equity.ddm_gordon_growth(next_dividend, required_return, growth_rate)
    print(f"Gordon growth model fair value: ${fair_value:.2f}")
    print()

def options_analysis_example():
    """Demonstrate options pricing functions."""
    print("=== Options Analysis ===")
    
    # Option payoffs
    stock_price_expiry = 105.0
    strike_price = 100.0
    
    call_payoff = fc.options.payoff_call(stock_price_expiry, strike_price)
    put_payoff = fc.options.payoff_put(stock_price_expiry, strike_price)
    
    print(f"At expiry: S=${stock_price_expiry}, K=${strike_price}")
    print(f"Call payoff: ${call_payoff:.2f}")
    print(f"Put payoff: ${put_payoff:.2f}")
    
    # Put-call parity check
    call_price = 8.0
    put_price = 3.0
    current_stock = 100.0
    risk_free_rate = 0.05
    time_to_expiry = 1.0
    
    parity_holds = fc.options.check_put_call_parity(
        call_price, put_price, current_stock, strike_price, 
        risk_free_rate, time_to_expiry
    )
    print(f"Put-call parity check: {'✓ Holds' if parity_holds else '✗ Violated'}")
    
    # Binomial model
    stock_up = 110.0
    stock_down = 90.0
    payoffs = fc.options.payoff_binomial_call(stock_up, stock_down, strike_price)
    print(f"Binomial payoffs - Up: ${payoffs[0]:.2f}, Down: ${payoffs[1]:.2f}")
    print()

def rates_analysis_example():
    """Demonstrate interest rate functions."""
    print("=== Interest Rates ===")
    
    # Compounding
    principal = 10_000.0
    annual_rate = 0.06
    years = 5.0
    
    # Discrete compounding (quarterly)
    quarterly_periods = 4
    discrete_value = fc.rates.compound_discrete(principal, annual_rate, quarterly_periods, years)
    print(f"${principal:,.0f} @ {annual_rate*100}% for {years} years (quarterly): ${discrete_value:,.2f}")
    
    # Continuous compounding
    continuous_value = fc.rates.compound_continuous(principal, annual_rate, years)
    print(f"${principal:,.0f} @ {annual_rate*100}% for {years} years (continuous): ${continuous_value:,.2f}")
    
    # Rate conversions
    nominal_rate = 0.06
    continuous_equiv = fc.rates.nominal_to_continuous(nominal_rate, quarterly_periods)
    print(f"Nominal {nominal_rate*100}% (quarterly) = {continuous_equiv*100:.4f}% (continuous)")
    
    # Present value / discounting
    future_value = 15_000.0
    discount_rate = 0.08
    time_periods = 3.0
    present_value = fc.rates.roll_back_cont(future_value, discount_rate, time_periods)
    print(f"PV of ${future_value:,.0f} in {time_periods} years @ {discount_rate*100}%: ${present_value:,.2f}")
    print()

def forwards_analysis_example():
    """Demonstrate forward pricing functions."""
    print("=== Forward Contracts ===")
    
    spot_price = 100.0
    risk_free_rate = 0.04
    time_to_maturity = 0.5  # 6 months
    
    # Forward without dividends
    forward_no_div = fc.forwards.forward_price_no_div(spot_price, risk_free_rate, time_to_maturity)
    print(f"Forward price (no dividends): ${forward_no_div:.2f}")
    
    # Forward with discrete dividend
    dividend_pv = 2.0  # Present value of dividends
    forward_with_div = fc.forwards.forward_price_with_div(spot_price, dividend_pv, risk_free_rate, time_to_maturity)
    print(f"Forward price (with ${dividend_pv} dividend): ${forward_with_div:.2f}")
    
    # Forward with continuous yield
    dividend_yield = 0.02  # 2% continuous yield
    forward_cont_yield = fc.forwards.forward_price_cont_yield(spot_price, risk_free_rate, dividend_yield, time_to_maturity)
    print(f"Forward price (with {dividend_yield*100}% yield): ${forward_cont_yield:.2f}")
    print()

def main():
    """Run all examples."""
    print("FinCraftr Usage Examples")
    print("=" * 50)
    print(f"Using FinCraftr version: {fc.__version__}")
    print()
    
    try:
        equity_analysis_example()
        options_analysis_example()
        rates_analysis_example()
        forwards_analysis_example()
        
        print("🎉 All examples completed successfully!")
        print("\nNote: These examples demonstrate the C++ functions exposed to Python.")
        print("The same functions are available natively in C++ with identical signatures.")
        
    except Exception as e:
        print(f"❌ Error running examples: {e}")
        print("Make sure FinCraftr is properly installed: pip install fincraftr")
        return 1
    
    return 0

if __name__ == "__main__":
    exit(main())
