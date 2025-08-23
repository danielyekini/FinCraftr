#pragma once
#include <cmath>

namespace fc::rates {

    inline double roll_forward_cont(double P_t, double r, double tau) {
        return P_t * std::exp(r * tau);
    }
    
    inline double roll_back_cont(double P_t, double r, double tau) {
        return P_t * std::exp(-r * tau);
    }
}