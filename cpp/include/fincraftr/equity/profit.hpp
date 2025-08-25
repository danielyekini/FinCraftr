#pragma once
#include <cmath>

namespace fc::equity {
    /// Calculate simple profit from holding a stock position
    /// @param S0 Initial stock price
    /// @param ST Final stock price
    /// @param r Risk-free rate (continuous)
    /// @param tau Holding period
    /// @return Profit after accounting for opportunity cost
    inline double profit_simple(double S0, double ST, double r, double tau) {
        return ST - S0 * std::exp(r * tau);
    }

    /// Calculate profit from holding a stock position with transaction costs and dividends
    /// @param S0 Initial stock price
    /// @param ST Final stock price
    /// @param r Risk-free rate (continuous)
    /// @param tau Holding period
    /// @param D_tau Dividends received during holding period
    /// @param C0 Initial transaction costs
    /// @return Total profit including dividends and costs
    inline double profit_with_costs(double S0, double ST, double r, double tau,
        double D_tau, double C0) {
        return ST + D_tau - C0 * std::exp(r * tau);
    }
}