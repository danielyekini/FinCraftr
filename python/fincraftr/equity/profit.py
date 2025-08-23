import math

def profit_simple(S0: float, ST: float, r: float, tau: float) -> float:
    return ST - S0 * math.exp(r * tau)

def profit_with_costs(S0: float, ST: float, r: float, tau: float, D_tau: float, C0: float) -> float:
    return ST + D_tau - C0 * math.exp(r * tau)