#pragma once

#include <cmath>
namespace fc::options {
    /// Calculate profit/loss from holding a call option to expiration
    /// @param ST Stock price at expiration
    /// @param K Strike price
    /// @param premium Option premium paid
    /// @param r Risk-free rate (continuous)
    /// @param tau Time to expiration
    /// @return Profit/loss including opportunity cost of premium
    inline double profit_call(double ST, double K, double premium,
                            double r, double tau) {
        double payoff = (ST > K) ? (ST - K) : 0.0;
        double cost = premium * std::exp(r * tau);
        return payoff - cost;
    }
}
