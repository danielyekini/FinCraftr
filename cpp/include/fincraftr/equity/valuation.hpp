#pragma once

#include <stdexcept>
#include <vector>
#include <cmath>

namespace fc::equity {
    inline double ddm_single_period(double D1, double S1, double r) {
        return (D1 + S1) / (1.0 + r);
    }

    inline double ddm_multi_period(const std::vector<double>& dividends,
        double ST, double r) {
        double pv = 0.0;
        for (size_t t=0; t<dividends.size(); ++t)
            pv += dividends[t] / std::pow(1.0 + r, static_cast<int>(t+1));
        pv += ST / std::pow(1.0 + r, dividends.size());
        return pv;
    }

    inline double ddm_infinite(const std::vector<double>& dividends, double r) {
        double pv = 0.0;
        for (size_t t=0; t<dividends.size(); ++t)
            pv += dividends[t] / std::pow(1.0 + r, static_cast<int>(t+1));
        return pv;
    }

    inline double cost_of_equity(double D1, double S1, double S0) {
        if (S0 == 0.0) throw std::invalid_argument("S0 must be nonzero");
        return (D1 + S1) / S0 - 1.0;
    }

    inline double ddm_gordon_growth(double D1, double r, double g) {
        if (g >= r) throw std::invalid_argument("g must be less than r");
        return D1 / (r - g);
    }
}