#pragma once
#include <cmath>
#include <utility>

namespace fc::options {
    /// Calculate call option payoffs in up and down states for binomial model
    /// @param Su Stock price in up state
    /// @param Sd Stock price in down state
    /// @param K Strike price
    /// @return Pair of (payoff_up, payoff_down)
    inline std::pair<double,double> payoff_binomial_call(double Su, double Sd, double K) {
        double Cu = (Su > K) ? (Su - K) : 0.0;
        double Cd = (Sd > K) ? (Sd - K) : 0.0;
        return std::make_pair(Cu, Cd);
    }

    /// Calculate hedge ratio (delta) for binomial option model
    /// @param Cu Option value in up state
    /// @param Cd Option value in down state
    /// @param Su Stock price in up state
    /// @param Sd Stock price in down state
    /// @return Hedge ratio (number of shares to hold)
    inline double hedge_ratio_binomial(double Cu, double Cd, double Su, double Sd) {
        return (Cu - Cd) / (Su - Sd);
    }

    /// Calculate loan amount needed for binomial replication strategy
    /// @param Cu Option value in up state
    /// @param Cd Option value in down state
    /// @param Su Stock price in up state
    /// @param Sd Stock price in down state
    /// @param r Risk-free rate
    /// @return Loan amount (negative means lending)
    inline double loan_binomial(double Cu, double Cd, double Su, double Sd, double r) {
        double Δ = hedge_ratio_binomial(Cu, Cd, Su, Sd);
        return (Δ * Sd - Cd) / (1.0 + r);
    }

    /// Price option using one-period binomial replication
    /// @param S0 Current stock price
    /// @param Delta Hedge ratio (number of shares)
    /// @param B_hat Loan amount
    /// @param r Risk-free rate
    /// @param tau Time to expiration (default 1.0)
    /// @return Option price
    inline double price_binomial_one_period(double S0, double Delta, double B_hat,
                                            double r, double tau=1.0) {
        return Delta * S0 - std::pow(1.0 + r, tau) * B_hat;
    }

    /// Price option using risk-neutral valuation in one-period binomial model
    /// @param S0 Current stock price
    /// @param Su Stock price in up state
    /// @param Sd Stock price in down state
    /// @param Cu Option value in up state
    /// @param Cd Option value in down state
    /// @param r Risk-free rate
    /// @param tau Time to expiration (default 1.0)
    /// @return Option price
    inline double price_risk_neutral_one_period(double S0, double Su, double Sd,
                                                double Cu, double Cd,
                                                double r, double tau=1.0) {
        double u = Su / S0, d = Sd / S0;
        double p_star = (std::exp(r * tau) - d) / (u - d);
        double expected_payoff = p_star * Cu + (1.0 - p_star) * Cd;
        return std::exp(-r * tau) * expected_payoff;
    }
}