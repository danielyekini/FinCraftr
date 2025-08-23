#pragma once
#include <stdexcept>

namespace fc::equity {
    inline double return_simple(double Pt, double Pt_prev) {
        if (Pt_prev == 0.0) throw std::invalid_argument("Previous price must be nonzero");
        return (Pt / Pt_prev) - 1.0;
    }
}