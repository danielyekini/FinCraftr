import math

def nominal_to_continuous(R: float, m: int) -> float:
    return m * math.log(1 + R / m)

def continuous_to_nominal(r: float, m: int) -> float:
    return m *(math.exp(r / m)-1)