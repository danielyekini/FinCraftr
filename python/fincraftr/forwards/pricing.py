import math

def forward_price_no_div(S: float, r: float, tau: float) -> float:
    return S * math.exp(r * tau)

def forward_price_with_div(S: float, D: float, r: float, tau: float) -> float:
    return (S - D) * math.exp(r * tau)

def forward_price_cont_yield(S: float, r: float, q: float, tau: float) -> float:
    return S * math.exp((r - q) * tau)
