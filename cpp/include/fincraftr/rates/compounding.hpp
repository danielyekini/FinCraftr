#pragma once
#include <cmath>

namespace fc::rates {
    /// Calculate compound interest with discrete compounding
    /// @param p0 Initial principal amount
    /// @param r Annual interest rate (as decimal, e.g., 0.05 for 5%)
    /// @param m Number of compounding periods per year
    /// @param years Time period in years
    /// @return Final amount after compound interest
    inline double compound_discrete(double p0, double r, int m, double years) {
        return p0 * std::pow(1 + r / m, m * years);
    }

    /// Calculate compound interest with continuous compounding
    /// @param p0 Initial principal amount
    /// @param r Annual interest rate (as decimal, e.g., 0.05 for 5%)
    /// @param t Time period in years
    /// @return Final amount after continuous compound interest
    inline double compound_continuous(double p0, double r, double t) {
        return p0 * std::exp(r * t);
    }
}