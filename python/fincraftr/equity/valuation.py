def ddm_single_period(D1: float, S1: float, r: float) -> float:
    return (D1 + S1) / (1.0 + r)

def ddm_multi_period(dividends: list[float], ST: float, r: float) -> float:
    T = len(dividends)
    pv = sum(Dt / (1.0 + r)**(t+1) for t, Dt in enumerate(dividends))
    pv += ST / (1.0 + r)**T
    return pv

def ddm_infinite(dividends: list[float], r: float) -> float:
    return sum(Dt / (1.0 + r)**(t+1) for t, Dt in enumerate(dividends))

def cost_of_equity(D1: float, S1: float, S0: float) -> float:
    if S0 == 0:
        raise ValueError("Current price must be nonzero")
    return (D1 + S1) / S0 - 1.0

def ddm_gordon_growth(D1: float, r: float, g: float) -> float:
    if g >= r:
        raise ValueError("Growth rate must be less than discount rate for convergence")
    return D1 / (r - g)