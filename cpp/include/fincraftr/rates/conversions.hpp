#pragma once
#include <cmath>

namespace fc::rates {
    inline double nominal_to_continuous(double R, double m) {
        return m * std::log(1 + R / m);
    }

    inline double continuous_to_nominal(double r, double m) {
        return m * (std::exp(r / m) - 1);
    }
}