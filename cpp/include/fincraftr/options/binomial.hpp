#pragma once
#include <cmath>
#include <utility>

namespace fc::options {
    inline std::pair<double,double> payoff_binomial_call(double Su, double Sd, double K) {
        double Cu = (Su > K) ? (Su - K) : 0.0;
        double Cd = (Sd > K) ? (Sd - K) : 0.0;
        return std::make_pair(Cu, Cd);
    }

    inline double hedge_ratio_binomial(double Cu, double Cd, double Su, double Sd) {
        return (Cu - Cd) / (Su - Sd);
    }

    inline double loan_binomial(double Cu, double Cd, double Su, double Sd, double r) {
        double Δ = hedge_ratio_binomial(Cu, Cd, Su, Sd);
        return (Δ * Sd - Cd) / (1.0 + r);
    }

    inline double price_binomial_one_period(double S0, double Delta, double B_hat,
                                            double r, double tau=1.0) {
        return Delta * S0 - std::pow(1.0 + r, tau) * B_hat;
    }

    inline double price_risk_neutral_one_period(double S0, double Su, double Sd,
                                                double Cu, double Cd,
                                                double r, double tau=1.0) {
        double u = Su / S0, d = Sd / S0;
        double p_star = (std::exp(r * tau) - d) / (u - d);
        double expected_payoff = p_star * Cu + (1.0 - p_star) * Cd;
        return std::exp(-r * tau) * expected_payoff;
    }
}