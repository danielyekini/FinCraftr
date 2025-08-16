"""
Finite-frequency compounding & fixed-rate bond helpers
=====================================================

All rates are quoted in decimals (0.05 == 5 %), all times in *years*.
Day-count conversion happens **up-stream**: pass actual year-fractions
into the `t` arguments.

Author: FinCraftr project
"""
from __future__ import annotations

import math
from typing import Iterable, Callable, Sequence, Tuple, List


# ---------- Elementary transforms -------------------------------------------------

def discount_factor(rate: float, m: int, t: float) -> float:
    """(1 + rate/m)^(-m*t)  – finite-frequency discount factor."""
    return (1.0 + rate / m) ** (-m * t)


def future_value(pv: float, rate: float, m: int, t: float) -> float:
    """Compounds present value forward m-times-per-year for t years."""
    return pv * (1.0 + rate / m) ** (m * t)


def present_value(fv: float, rate: float, m: int, t: float) -> float:
    """Discounts a future value back to today."""
    return fv * discount_factor(rate, m, t)


def effective_annual_rate(rate: float, m: int) -> float:
    return (1.0 + rate / m) ** m - 1.0


def equivalent_cont_rate(rate: float, m: int) -> float:
    return m * math.log(1.0 + rate / m)


# ---------- Cash-flow scaffolding --------------------------------------------------

def generate_cashflows(
    face: float,
    coupon_rate: float,
    m: int,
    n_years: float
) -> List[Tuple[float, float]]:
    """
    Returns [(t_1, C_1), ..., (t_N, C_N + redemption)] where time is in years.
    Assumes regular schedule, no stubs, deterministic amounts.
    """
    dt = 1.0 / m
    n_payments = int(round(n_years * m))
    coupon = coupon_rate * face / m
    flows = [(k * dt, coupon) for k in range(1, n_payments + 1)]
    # add principal to last coupon
    t_last, c_last = flows[-1]
    flows[-1] = (t_last, c_last + face)
    return flows


# ---------- Pricing ----------------------------------------------------------------

def price_fixed_rate_bond(
    face: float,
    coupon_rate: float,
    m: int,
    n_years: float,
    curve: Callable[[float], float],
) -> float:
    """
    Present value of a fixed-rate bond under deterministic curve.
    `curve(t)` must return *annualised* zero rate on the **same** compounding basis m.
    """
    pv = 0.0
    for t, cf in generate_cashflows(face, coupon_rate, m, n_years):
        y_t = curve(t)
        pv += cf * discount_factor(y_t, m, t)
    return pv


# ---------- Yield-to-Maturity -------------------------------------------------------

def yield_to_maturity(
    price: float,
    face: float,
    coupon_rate: float,
    m: int,
    n_years: float,
    tol: float = 1e-10,
    max_iter: int = 100,
    guess: float = 0.03,
) -> float:
    """
    Solves PV(price) = price for the single YTM using Newton with bisection fallback.
    Returns nominal annual yield on the same compounding basis m.
    """
    flows = generate_cashflows(face, coupon_rate, m, n_years)

    def pv_at(y: float) -> float:
        return sum(cf * discount_factor(y, m, t) for t, cf in flows)

    # Newton iteration
    y = guess
    for _ in range(max_iter):
        pv = pv_at(y)
        diff = pv - price
        if abs(diff) < tol:
            return y
        # derivative dPV/dy
        d_pv = sum(
            -m * t * cf * discount_factor(y, m, t) / (1 + y / m)
            for t, cf in flows
        )
        step = diff / d_pv
        y -= step
        if not (0.0 < y < 1.0):  # Newton wandered off –> bisection
            break
    # Bisection safeguard
    lo, hi = 0.0, 1.0
    for _ in range(max_iter):
        mid = 0.5 * (lo + hi)
        if pv_at(mid) > price:
            lo = mid
        else:
            hi = mid
        if hi - lo < tol:
            return mid
    raise RuntimeError("YTM solver failed to converge")


# ---------- Risk measures ----------------------------------------------------------

def dv01(price: float, face: float, coupon_rate: float, m: int, n_years: float, ytm: float, bp: float = 1e-4) -> float:
    """Dollar value of a 1bp move, finite diff."""
    y_up = ytm + bp
    y_down = ytm - bp
    pv_up = price_fixed_rate_bond(face, coupon_rate, m, n_years, lambda _: y_up)
    pv_down = price_fixed_rate_bond(face, coupon_rate, m, n_years, lambda _: y_down)
    return 0.5 * (pv_down - pv_up)
