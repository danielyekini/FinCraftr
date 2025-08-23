#pragma once
#include <cmath>

namespace fc::equity {
    inline double profit_simple(double S0, double ST, double r, double tau) {
        return ST - S0 * std::exp(r * tau);
    }

    inline double profit_with_costs(double S0, double ST, double r, double tau,
        double D_tau, double C0) {
return ST + D_tau - C0 * std::exp(r * tau);
}
}