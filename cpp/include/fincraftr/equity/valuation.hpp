#pragma once

#include <stdexcept>
#include <vector>
#include <cmath>

namespace fc::equity {
    /// Single-period dividend discount model
    /// @param D1 Expected dividend at end of period
    /// @param S1 Expected stock price at end of period
    /// @param r Required rate of return
    /// @return Present value of stock
    inline double ddm_single_period(double D1, double S1, double r) {
        return (D1 + S1) / (1.0 + r);
    }

    /// Multi-period dividend discount model with terminal value
    /// @param dividends Vector of expected dividends for each period
    /// @param ST Terminal stock price after dividend periods
    /// @param r Required rate of return
    /// @return Present value of stock
    inline double ddm_multi_period(const std::vector<double>& dividends,
        double ST, double r) {
        double pv = 0.0;
        for (size_t t=0; t<dividends.size(); ++t)
            pv += dividends[t] / std::pow(1.0 + r, static_cast<int>(t+1));
        pv += ST / std::pow(1.0 + r, dividends.size());
        return pv;
    }

    /// Infinite-period dividend discount model (perpetuity)
    /// @param dividends Vector of expected dividends for each period
    /// @param r Required rate of return
    /// @return Present value assuming dividends continue indefinitely
    inline double ddm_infinite(const std::vector<double>& dividends, double r) {
        double pv = 0.0;
        for (size_t t=0; t<dividends.size(); ++t)
            pv += dividends[t] / std::pow(1.0 + r, static_cast<int>(t+1));
        return pv;
    }

    /// Calculate cost of equity using dividend growth model
    /// @param D1 Expected dividend at end of period
    /// @param S1 Expected stock price at end of period
    /// @param S0 Current stock price (must be nonzero)
    /// @return Cost of equity as required rate of return
    /// @throws std::invalid_argument if S0 is zero
    inline double cost_of_equity(double D1, double S1, double S0) {
        if (S0 == 0.0) throw std::invalid_argument("S0 must be nonzero");
        return (D1 + S1) / S0 - 1.0;
    }

    /// Gordon growth model for dividend discount valuation
    /// @param D1 Expected dividend next period
    /// @param r Required rate of return
    /// @param g Constant growth rate of dividends (must be < r)
    /// @return Present value of stock with constant dividend growth
    /// @throws std::invalid_argument if g >= r
    inline double ddm_gordon_growth(double D1, double r, double g) {
        if (g >= r) throw std::invalid_argument("g must be less than r");
        return D1 / (r - g);
    }
}