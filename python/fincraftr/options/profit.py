import math

def profit_call(ST: float, K: float, premium: float, r: float, tau: float) -> float:
    payoff = max(ST - K, 0.0)
    cost = premium * math.exp(r * tau)
    return payoff - cost
