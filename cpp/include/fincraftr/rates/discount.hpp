#pragma once
#include <cmath>

namespace fc::rates {

    /// Roll a value forward in time using continuous compounding
    /// @param P_t Present value at time t
    /// @param r Continuous interest rate
    /// @param tau Time period to roll forward
    /// @return Future value after rolling forward tau time units
    inline double roll_forward_cont(double P_t, double r, double tau) {
        return P_t * std::exp(r * tau);
    }
    
    /// Discount a value back in time using continuous compounding
    /// @param P_t Future value at time t
    /// @param r Continuous interest rate
    /// @param tau Time period to discount back
    /// @return Present value after discounting back tau time units
    inline double roll_back_cont(double P_t, double r, double tau) {
        return P_t * std::exp(-r * tau);
    }
}