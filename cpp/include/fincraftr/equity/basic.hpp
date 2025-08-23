#pragma once
#include <stdexcept>

namespace fc::equity {
    inline double market_cap(double shares_outstanding, double price) {
        return shares_outstanding * price;
    }

    inline double ownership_fraction(double shares_owned, double shares_outstanding) {
        if (shares_outstanding <= 0.0) throw std::invalid_argument("shares_outstanding must be > 0");
        return shares_owned / shares_outstanding;
    }
}
    