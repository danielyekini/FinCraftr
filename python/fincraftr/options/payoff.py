def payoff_call(ST: float, K: float) -> float:
    return max(ST - K, 0.0)

def payoff_put(ST: float, K: float) -> float:
    return max(K - ST, 0.0)

def payoff_asian_call(average_price: float, K: float) -> float:
    return max(average_price - K, 0.0)
