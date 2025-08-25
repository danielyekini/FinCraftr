#pragma once
#include <numeric>
#include <vector>
#include <cmath>

namespace fc::equity {
    /// Calculate price-weighted index value
    /// @param prices Vector of current stock prices
    /// @param D Divisor used for index calculation
    /// @return Price-weighted index value
    inline double index_price_weighted(const std::vector<double>& prices, double D) {
        return std::accumulate(prices.begin(), prices.end(), 0.0) / D;
    }

    /// Calculate capitalization-weighted index value
    /// @param prev_index Previous index value
    /// @param caps_now Vector of current market capitalizations
    /// @param caps_prev Vector of previous market capitalizations
    /// @param J Adjustment factor for corporate actions (default 0.0)
    /// @return New capitalization-weighted index value
    inline double index_cap_weighted(double prev_index,
                                     const std::vector<double>& caps_now,
                                     const std::vector<double>& caps_prev,
                                     double J=0.0) {
        double sum_now = std::accumulate(caps_now.begin(), caps_now.end(), 0.0);
        double sum_prev = std::accumulate(caps_prev.begin(), caps_prev.end(), 0.0);
        return prev_index * (sum_now / (sum_prev + J));
    }

    /// Calculate Value Line geometric index
    /// @param prev_index Previous index value
    /// @param prices_now Vector of current stock prices
    /// @param prices_prev Vector of previous stock prices
    /// @return New Value Line geometric index value
    inline double index_value_line_geo(double prev_index,
                                       const std::vector<double>& prices_now,
                                       const std::vector<double>& prices_prev) {
        double product = 1.0;
        for (size_t i = 0; i < prices_now.size(); ++i)
            product *= prices_now[i] / prices_prev[i];
        return prev_index * std::pow(product, 1.0 / prices_now.size());
    }

    /// Calculate Value Line arithmetic index
    /// @param prev_index Previous index value
    /// @param prices_now Vector of current stock prices
    /// @param prices_prev Vector of previous stock prices
    /// @return New Value Line arithmetic index value
    inline double index_value_line_arith(double prev_index,
                                         const std::vector<double>& prices_now,
                                         const std::vector<double>& prices_prev) {
        std::vector<double> ratios(prices_now.size());
        for (size_t i=0; i<prices_now.size(); ++i)
            ratios[i] = prices_now[i] / prices_prev[i];
        double avg = std::accumulate(ratios.begin(), ratios.end(), 0.0) / ratios.size();
        return prev_index * avg;
    }
}