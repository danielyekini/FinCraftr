#pragma once

#include <cmath>
namespace fc::options {
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
