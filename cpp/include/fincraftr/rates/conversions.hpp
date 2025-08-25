#pragma once
#include <cmath>

namespace fc::rates {
    /// Convert nominal (discrete) interest rate to continuous compounding rate
    /// @param R Nominal annual interest rate (as decimal)
    /// @param m Number of compounding periods per year
    /// @return Equivalent continuous compounding rate
    inline double nominal_to_continuous(double R, double m) {
        return m * std::log(1 + R / m);
    }

    /// Convert continuous compounding rate to nominal (discrete) interest rate
    /// @param r Continuous compounding rate (as decimal)
    /// @param m Number of compounding periods per year
    /// @return Equivalent nominal annual interest rate
    inline double continuous_to_nominal(double r, double m) {
        return m * (std::exp(r / m) - 1);
    }
}