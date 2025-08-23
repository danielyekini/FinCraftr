def market_cap(shares_outstanding: float, price: float) -> float:
    return shares_outstanding * price

def ownership_fraction(shares_owned: float, shares_outstanding: float) -> float:
    if shares_outstanding <= 0:
        raise ValueError("shares_outstanding must be positive")
    return shares_owned / shares_outstanding