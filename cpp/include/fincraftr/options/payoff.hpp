#pragma once

namespace fc::options {
    /// Calculate the payoff of a European call option at expiration
    /// @param ST Stock price at expiration
    /// @param K Strike price
    /// @return Call option payoff: max(ST - K, 0)
    inline double payoff_call(double ST, double K) {
        return (ST > K) ? (ST - K) : 0.0;
    }

    /// Calculate the payoff of a European put option at expiration
    /// @param ST Stock price at expiration
    /// @param K Strike price
    /// @return Put option payoff: max(K - ST, 0)
    inline double payoff_put(double ST, double K) {
        return (ST < K) ? (K - ST) : 0.0;
    }

    /// Calculate the payoff of an Asian call option at expiration
    /// @param average_price Average price of the underlying over the option's life
    /// @param K Strike price
    /// @return Asian call option payoff: max(average_price - K, 0)
    inline double payoff_asian_call(double average_price, double K) {
        return (average_price > K) ? (average_price - K) : 0.0;
    }
}