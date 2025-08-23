import math


def compound_discrete(p0:float, r:float, m:int, years:float) -> float:
    return p0 * (1 + r / m) ** (m * years)

def compound_continuous(p0:float, r:float, t:float) -> float:
    return p0 * math.exp(r * t)
