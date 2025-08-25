"""
FinCraftr - A bilingual quantitative finance toolkit

This package provides clean, composable building blocks for pricing, risk, 
portfolio analytics, and market data modelling, implemented with parallel 
APIs across Python and C++20.

Modules:
    equity: Equity analysis functions (returns, valuation, indices)
    options: Options pricing and analysis functions
    forwards: Forward contract pricing functions
    rates: Interest rate and discounting functions
"""

__version__ = "1.0.0"
__author__ = "FinCraftr Contributors"

# Import the compiled C++ extension
try:
    from .pyfincraftr import *
    from .pyfincraftr import equity, options, forwards, rates
    
    # Make functions available at top level for convenience
    from .pyfincraftr.equity import return_simple
    from .pyfincraftr.rates import compound_discrete, compound_continuous
    from .pyfincraftr.options import payoff_call, payoff_put
    from .pyfincraftr.forwards import forward_price_no_div
    
except ImportError as e:
    import warnings
    warnings.warn(f"Could not import C++ extension: {e}. "
                  "Using Python fallback implementations.")
    
    # Import Python fallback implementations
    from . import equity
    from . import options  
    from . import forwards
    from . import rates
    
    # Import key functions for top-level access
    from .equity.returns import return_simple
    from .rates.compounding import compound_discrete, compound_continuous
    from .options.payoff import payoff_call, payoff_put
    from .forwards.pricing import forward_price_no_div

__all__ = [
    "equity",
    "options", 
    "forwards",
    "rates",
    "return_simple",
    "compound_discrete",
    "compound_continuous", 
    "payoff_call",
    "payoff_put",
    "forward_price_no_div",
]
