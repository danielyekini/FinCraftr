#pragma once

#include <cmath>
namespace fc::options {
    /// Check if put-call parity relationship holds within tolerance
    /// @param C Call option price
    /// @param P Put option price
    /// @param S Current stock price
    /// @param K Strike price
    /// @param r Risk-free rate (continuous)
    /// @param tau Time to expiration
    /// @param D Present value of dividends (default 0.0)
    /// @param q Continuous dividend yield (default NAN, uses discrete dividends)
    /// @param tol Tolerance for parity check (default 1e-8)
    /// @return True if parity holds within tolerance
    inline bool check_put_call_parity(double C, double P, double S, double K,
                                    double r, double tau,
                                    double D=0.0, double q=NAN,
                                    double tol=1e-8) {
        double lhs, rhs;
        if (std::isnan(q)) {
            lhs = P + S;
            rhs = C + D + K * std::exp(-r * tau);
        } else {
            lhs = P + S * std::exp((q - r) * tau);
            rhs = C + K * std::exp(-r * tau);
        }
        return std::abs(lhs - rhs) < tol;
    }
}
