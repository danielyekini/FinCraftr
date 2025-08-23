#pragma once

namespace fc::options {
    inline double payoff_call(double ST, double K) {
        return (ST > K) ? (ST - K) : 0.0;
    }

    inline double payoff_put(double ST, double K) {
        return (ST < K) ? (K - ST) : 0.0;
    }

    inline double payoff_asian_call(double average_price, double K) {
        return (average_price > K) ? (average_price - K) : 0.0;
    }
}