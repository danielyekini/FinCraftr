#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

// Include all FinCraftr headers
#include <fincraftr/equity/basic.hpp>
#include <fincraftr/equity/index.hpp>
#include <fincraftr/equity/profit.hpp>
#include <fincraftr/equity/returns.hpp>
#include <fincraftr/equity/valuation.hpp>
#include <fincraftr/forwards/pricing.hpp>
#include <fincraftr/options/binomial.hpp>
#include <fincraftr/options/parity.hpp>
#include <fincraftr/options/payoff.hpp>
#include <fincraftr/options/profit.hpp>
#include <fincraftr/rates/compounding.hpp>
#include <fincraftr/rates/conversions.hpp>
#include <fincraftr/rates/discount.hpp>

namespace py = pybind11;

PYBIND11_MODULE(pyfincraftr, m) {
    m.doc() = "FinCraftr - A bilingual quantitative finance toolkit";

    // Equity module
    py::module_ equity = m.def_submodule("equity", "Equity analysis functions");
    
    // Equity basic functions
    equity.def("market_cap", &fc::equity::market_cap,
        "Calculate the market capitalization of a company",
        py::arg("shares_outstanding"), py::arg("price"));
    
    equity.def("ownership_fraction", &fc::equity::ownership_fraction,
        "Calculate the ownership fraction for a given number of shares",
        py::arg("shares_owned"), py::arg("shares_outstanding"));
    
    // Equity returns
    equity.def("return_simple", &fc::equity::return_simple,
        "How much did this stock gain/lose relative to its previous price?",
        py::arg("Pt"), py::arg("Pt_prev"));
    
    // Equity index functions
    equity.def("index_price_weighted", &fc::equity::index_price_weighted,
        "Calculate price-weighted index value",
        py::arg("prices"), py::arg("D"));
    
    equity.def("index_cap_weighted", &fc::equity::index_cap_weighted,
        "Calculate capitalization-weighted index value",
        py::arg("prev_index"), py::arg("caps_now"), py::arg("caps_prev"), py::arg("J") = 0.0);
    
    equity.def("index_value_line_geo", &fc::equity::index_value_line_geo,
        "Calculate Value Line geometric index",
        py::arg("prev_index"), py::arg("prices_now"), py::arg("prices_prev"));
    
    equity.def("index_value_line_arith", &fc::equity::index_value_line_arith,
        "Calculate Value Line arithmetic index",
        py::arg("prev_index"), py::arg("prices_now"), py::arg("prices_prev"));
    
    // Equity profit functions
    equity.def("profit_simple", &fc::equity::profit_simple,
        "Calculate simple profit from holding a stock position",
        py::arg("S0"), py::arg("ST"), py::arg("r"), py::arg("tau"));
    
    equity.def("profit_with_costs", &fc::equity::profit_with_costs,
        "Calculate profit from holding a stock position with transaction costs and dividends",
        py::arg("S0"), py::arg("ST"), py::arg("r"), py::arg("tau"), py::arg("D_tau"), py::arg("C0"));
    
    // Equity valuation functions
    equity.def("ddm_single_period", &fc::equity::ddm_single_period,
        "Single-period dividend discount model",
        py::arg("D1"), py::arg("S1"), py::arg("r"));
    
    equity.def("ddm_multi_period", &fc::equity::ddm_multi_period,
        "Multi-period dividend discount model with terminal value",
        py::arg("dividends"), py::arg("ST"), py::arg("r"));
    
    equity.def("ddm_infinite", &fc::equity::ddm_infinite,
        "Infinite-period dividend discount model (perpetuity)",
        py::arg("dividends"), py::arg("r"));
    
    equity.def("cost_of_equity", &fc::equity::cost_of_equity,
        "Calculate cost of equity using dividend growth model",
        py::arg("D1"), py::arg("S1"), py::arg("S0"));
    
    equity.def("ddm_gordon_growth", &fc::equity::ddm_gordon_growth,
        "Gordon growth model for dividend discount valuation",
        py::arg("D1"), py::arg("r"), py::arg("g"));

    // Options module
    py::module_ options = m.def_submodule("options", "Options pricing and analysis functions");
    
    // Options payoff functions
    options.def("payoff_call", &fc::options::payoff_call,
        "Calculate the payoff of a European call option at expiration",
        py::arg("ST"), py::arg("K"));
    
    options.def("payoff_put", &fc::options::payoff_put,
        "Calculate the payoff of a European put option at expiration",
        py::arg("ST"), py::arg("K"));
    
    options.def("payoff_asian_call", &fc::options::payoff_asian_call,
        "Calculate the payoff of an Asian call option at expiration",
        py::arg("average_price"), py::arg("K"));
    
    // Options binomial functions
    options.def("payoff_binomial_call", &fc::options::payoff_binomial_call,
        "Calculate call option payoffs in up and down states for binomial model",
        py::arg("Su"), py::arg("Sd"), py::arg("K"));
    
    options.def("hedge_ratio_binomial", &fc::options::hedge_ratio_binomial,
        "Calculate hedge ratio (delta) for binomial option model",
        py::arg("Cu"), py::arg("Cd"), py::arg("Su"), py::arg("Sd"));
    
    options.def("loan_binomial", &fc::options::loan_binomial,
        "Calculate loan amount needed for binomial replication strategy",
        py::arg("Cu"), py::arg("Cd"), py::arg("Su"), py::arg("Sd"), py::arg("r"));
    
    options.def("price_binomial_one_period", &fc::options::price_binomial_one_period,
        "Price option using one-period binomial replication",
        py::arg("S0"), py::arg("Delta"), py::arg("B_hat"), py::arg("r"), py::arg("tau") = 1.0);
    
    options.def("price_risk_neutral_one_period", &fc::options::price_risk_neutral_one_period,
        "Price option using risk-neutral valuation in one-period binomial model",
        py::arg("S0"), py::arg("Su"), py::arg("Sd"), py::arg("Cu"), py::arg("Cd"), py::arg("r"), py::arg("tau") = 1.0);
    
    // Options parity functions
    options.def("check_put_call_parity", &fc::options::check_put_call_parity,
        "Check if put-call parity relationship holds within tolerance",
        py::arg("C"), py::arg("P"), py::arg("S"), py::arg("K"), py::arg("r"), py::arg("tau"),
        py::arg("D") = 0.0, py::arg("q") = NAN, py::arg("tol") = 1e-8);
    
    // Options profit functions
    options.def("profit_call", &fc::options::profit_call,
        "Calculate profit/loss from holding a call option to expiration",
        py::arg("ST"), py::arg("K"), py::arg("premium"), py::arg("r"), py::arg("tau"));

    // Forwards module
    py::module_ forwards = m.def_submodule("forwards", "Forward contract pricing functions");
    
    forwards.def("forward_price_no_div", &fc::forwards::forward_price_no_div,
        "Calculate forward price for an asset with no dividends",
        py::arg("S"), py::arg("r"), py::arg("tau"));
    
    forwards.def("forward_price_with_div", &fc::forwards::forward_price_with_div,
        "Calculate forward price for an asset with known discrete dividend",
        py::arg("S"), py::arg("D"), py::arg("r"), py::arg("tau"));
    
    forwards.def("forward_price_cont_yield", &fc::forwards::forward_price_cont_yield,
        "Calculate forward price for an asset with continuous dividend yield",
        py::arg("S"), py::arg("r"), py::arg("q"), py::arg("tau"));

    // Rates module
    py::module_ rates = m.def_submodule("rates", "Interest rate and discounting functions");
    
    // Compounding functions
    rates.def("compound_discrete", &fc::rates::compound_discrete,
        "Calculate compound interest with discrete compounding",
        py::arg("p0"), py::arg("r"), py::arg("m"), py::arg("years"));
    
    rates.def("compound_continuous", &fc::rates::compound_continuous,
        "Calculate compound interest with continuous compounding",
        py::arg("p0"), py::arg("r"), py::arg("t"));
    
    // Discount functions
    rates.def("roll_forward_cont", &fc::rates::roll_forward_cont,
        "Roll a value forward in time using continuous compounding",
        py::arg("P_t"), py::arg("r"), py::arg("tau"));
    
    rates.def("roll_back_cont", &fc::rates::roll_back_cont,
        "Discount a value back in time using continuous compounding",
        py::arg("P_t"), py::arg("r"), py::arg("tau"));
    
    // Conversion functions
    rates.def("nominal_to_continuous", &fc::rates::nominal_to_continuous,
        "Convert nominal (discrete) interest rate to continuous compounding rate",
        py::arg("R"), py::arg("m"));
    
    rates.def("continuous_to_nominal", &fc::rates::continuous_to_nominal,
        "Convert continuous compounding rate to nominal (discrete) interest rate",
        py::arg("r"), py::arg("m"));
}
