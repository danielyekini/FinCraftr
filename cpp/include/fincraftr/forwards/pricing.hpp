#pragma once

#include <cmath>

namespace fc::forwards {
    inline double forward_price_no_div(double S, double r, double tau) {
        return S * std::exp(r * tau);
    }
    inline double forward_price_with_div(double S, double D, double r, double tau) {
        return (S - D) * std::exp(r * tau);
    }
    inline double forward_price_cont_yield(double S, double r, double q, double tau) {
        return S * std::exp((r - q) * tau);
    }
}
