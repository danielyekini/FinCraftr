import math


def roll_forward_cont(P_t:float, r:float, tau:float) -> float:
    return P_t * math.exp(r * tau)

def roll_back_cont(P_t:float, r:float, tau:float) -> float:
    return P_t * math.exp(-r * tau)