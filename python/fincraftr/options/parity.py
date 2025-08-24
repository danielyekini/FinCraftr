import math

def check_put_call_parity(C: float, P: float, S: float, K: float, r: float, tau: float,
                          D: float=0.0, q: float=None, tol: float=1e-6) -> bool:
    if q is None:  # discrete dividend case
        lhs = P + S
        rhs = C + D + K * math.exp(-r * tau)
    else:  # continuous yield
        lhs = P + S * math.exp((q - r) * tau)
        rhs = C + K * math.exp(-r * tau)
    return abs(lhs - rhs) < tol
