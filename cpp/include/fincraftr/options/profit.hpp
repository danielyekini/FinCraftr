#pragma once

#include <cmath>
namespace fc::options {
    inline double profit_call(double ST, double K, double premium,
                            double r, double tau) {
        double payoff = (ST > K) ? (ST - K) : 0.0;
        double cost = premium * std::exp(r * tau);
        return payoff - cost;
    }
}
