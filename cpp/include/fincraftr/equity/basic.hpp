#pragma once
#include <stdexcept>

namespace fc::equity {
    /// Calculate the market capitalization of a company
    /// @param shares_outstanding Total number of shares outstanding
    /// @param price Current price per share
    /// @return Market capitalization (shares_outstanding * price)
    inline double market_cap(double shares_outstanding, double price) {
        return shares_outstanding * price;
    }

    /// Calculate the ownership fraction for a given number of shares
    /// @param shares_owned Number of shares owned
    /// @param shares_outstanding Total number of shares outstanding (must be > 0)
    /// @return Ownership fraction as shares_owned / shares_outstanding
    /// @throws std::invalid_argument if shares_outstanding <= 0
    inline double ownership_fraction(double shares_owned, double shares_outstanding) {
        if (shares_outstanding <= 0.0) throw std::invalid_argument("shares_outstanding must be > 0");
        return shares_owned / shares_outstanding;
    }
}
    