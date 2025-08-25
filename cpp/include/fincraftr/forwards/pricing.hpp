#pragma once

#include <cmath>

namespace fc::forwards {
    /// Calculate forward price for an asset with no dividends
    /// @param S Current spot price of the underlying asset
    /// @param r Risk-free interest rate (continuous)
    /// @param tau Time to expiration
    /// @return Forward price assuming no dividends
    inline double forward_price_no_div(double S, double r, double tau) {
        return S * std::exp(r * tau);
    }
    
    /// Calculate forward price for an asset with known discrete dividend
    /// @param S Current spot price of the underlying asset
    /// @param D Present value of known dividends during contract life
    /// @param r Risk-free interest rate (continuous)
    /// @param tau Time to expiration
    /// @return Forward price accounting for discrete dividends
    inline double forward_price_with_div(double S, double D, double r, double tau) {
        return (S - D) * std::exp(r * tau);
    }
    
    /// Calculate forward price for an asset with continuous dividend yield
    /// @param S Current spot price of the underlying asset
    /// @param r Risk-free interest rate (continuous)
    /// @param q Continuous dividend yield
    /// @param tau Time to expiration
    /// @return Forward price accounting for continuous dividend yield
    inline double forward_price_cont_yield(double S, double r, double q, double tau) {
        return S * std::exp((r - q) * tau);
    }
}
