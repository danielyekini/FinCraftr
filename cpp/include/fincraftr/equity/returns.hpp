#pragma once
#include <stdexcept>

namespace fc::equity {
    /// How much did this stock gain/lose relative to its previous price?
    /// @param Pt Current price
    /// @param Pt_prev Previous price (must be nonzero)
    /// @return Simple return as (Pt / Pt_prev) - 1.0
    /// @throws std::invalid_argument if Pt_prev is zero
    inline double return_simple(double Pt, double Pt_prev) {
        if (Pt_prev == 0.0) throw std::invalid_argument("Previous price must be nonzero");
        return (Pt / Pt_prev) - 1.0;
    }
}