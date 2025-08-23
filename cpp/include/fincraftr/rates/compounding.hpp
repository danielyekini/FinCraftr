#pragma once
#include <cmath>

namespace fc::rates {
    inline double compound_discrete(double p0, double r, int m, double years) {
        return p0 * std::pow(1 + r / m, m * years);
    }

    inline double compound_continuous(double p0, double r, double t) {
        return p0 * std::exp(r * t);
    }
}