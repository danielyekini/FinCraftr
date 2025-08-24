import math

def payoff_binomial_call(Su: float, Sd: float, K: float) -> tuple[float,float]:
    Cu = max(Su - K, 0.0)
    Cd = max(Sd - K, 0.0)
    return Cu, Cd

def hedge_ratio_binomial(Cu: float, Cd: float, Su: float, Sd: float) -> float:
    return (Cu - Cd) / (Su - Sd)

def loan_binomial(Cu: float, Cd: float, Su: float, Sd: float, r: float) -> float:
    Δ = hedge_ratio_binomial(Cu, Cd, Su, Sd)
    return (Δ * Sd - Cd) / (1.0 + r)

def price_binomial_one_period(S0: float, Delta: float, B_hat: float, r: float, tau: float=1.0) -> float:
    return Delta * S0 - (1.0 + r)**tau * B_hat

def price_risk_neutral_one_period(S0: float, Su: float, Sd: float,
                                  Cu: float, Cd: float,
                                  r: float, tau: float=1.0) -> float:
    u, d = Su / S0, Sd / S0
    p_star = (math.exp(r * tau) - d) / (u - d)
    expected_payoff = p_star * Cu + (1 - p_star) * Cd
    return math.exp(-r * tau) * expected_payoff
