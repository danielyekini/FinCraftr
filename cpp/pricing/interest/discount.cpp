#pragma once
/*
   Finite-frequency compounding & fixed-rate bond helpers
   ======================================================

   Header-only; include <cmath>, <vector>, <functional>.
   All rates in decimals, times in years.  Deterministic cash-flows, no options.
*/

#include <cmath>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits>

namespace fc::interest {

// ---------- Elementary transforms -------------------------------------------------

inline double discount_factor(double rate, int m, double t) {
    return std::pow(1.0 + rate / m, -m * t);
}

inline double future_value(double pv, double rate, int m, double t) {
    return pv * std::pow(1.0 + rate / m, m * t);
}

inline double present_value(double fv, double rate, int m, double t) {
    return fv * discount_factor(rate, m, t);
}

inline double effective_annual_rate(double rate, int m) {
    return std::pow(1.0 + rate / m, m) - 1.0;
}

inline double equivalent_cont_rate(double rate, int m) {
    return m * std::log(1.0 + rate / m);
}

// ---------- Cash-flow scaffolding --------------------------------------------------

inline std::vector<std::pair<double, double>>
generate_cashflows(double face, double coupon_rate, int m, double n_years)
{
    const double dt = 1.0 / m;
    const int n_payments = static_cast<int>(std::round(n_years * m));
    const double coupon = coupon_rate * face / m;
    std::vector<std::pair<double, double>> flows;
    flows.reserve(n_payments);

    for (int k = 1; k <= n_payments; ++k)
        flows.emplace_back(k * dt, coupon);

    // add principal to last coupon
    flows.back().second += face;
    return flows;
}

// ---------- Pricing ----------------------------------------------------------------

inline double price_fixed_rate_bond(
    double face,
    double coupon_rate,
    int m,
    double n_years,
    const std::function<double(double)>& curve // zero rate y(t)
)
{
    double pv = 0.0;
    for (auto [t, cf] : generate_cashflows(face, coupon_rate, m, n_years)) {
        const double y = curve(t);
        pv += cf * discount_factor(y, m, t);
    }
    return pv;
}

// ---------- Yield-to-Maturity -------------------------------------------------------

inline double yield_to_maturity(
    double price,
    double face,
    double coupon_rate,
    int m,
    double n_years,
    double tol = 1e-10,
    int    max_iter = 100,
    double guess = 0.03
)
{
    const auto flows = generate_cashflows(face, coupon_rate, m, n_years);

    auto pv_at = [&](double y) {
        double pv = 0.0;
        for (auto [t, cf] : flows)
            pv += cf * discount_factor(y, m, t);
        return pv;
    };

    // Newton iteration
    double y = guess;
    for (int i = 0; i < max_iter; ++i) {
        double pv  = pv_at(y);
        double diff = pv - price;
        if (std::abs(diff) < tol) return y;

        double d_pv = 0.0;
        for (auto [t, cf] : flows) {
            d_pv += -m * t * cf * discount_factor(y, m, t) / (1.0 + y / m);
        }
        double step = diff / d_pv;
        y -= step;
        if (!(y > 0.0 && y < 1.0)) break;        // fall back to bisection
    }

    // Bisection safeguard
    double lo = 0.0, hi = 1.0;
    for (int i = 0; i < max_iter; ++i) {
        double mid = 0.5 * (lo + hi);
        if (pv_at(mid) > price)
            lo = mid;
        else
            hi = mid;
        if (hi - lo < tol) return mid;
    }
    throw std::runtime_error("yield_to_maturity did not converge");
}

// ---------- Risk measures ----------------------------------------------------------

inline double dv01(
    double price,
    double face,
    double coupon_rate,
    int m,
    double n_years,
    double ytm,
    double bp = 1e-4
)
{
    const auto curve_up   = [ytm, bp](double){ return ytm + bp; };
    const auto curve_down = [ytm, bp](double){ return ytm - bp; };

    double pv_up   = price_fixed_rate_bond(face, coupon_rate, m, n_years, curve_up);
    double pv_down = price_fixed_rate_bond(face, coupon_rate, m, n_years, curve_down);

    return 0.5 * (pv_down - pv_up);
}

} // namespace fc::interest
