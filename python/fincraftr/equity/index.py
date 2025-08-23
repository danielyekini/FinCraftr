import math
from typing import Sequence

def index_price_weighted(prices: list[float], D: float) -> float:
    return sum(prices) / D

def index_cap_weighted(prev_index: float,
                       caps_now: list[float],
                       caps_prev: list[float],
                       J: float=0.0) -> float:
    return prev_index * (sum(caps_now) / (sum(caps_prev) + J))

def index_value_line_geo(prev_index: float,
                         prices_now: Sequence[float],
                         prices_prev: Sequence[float]) -> float:
    n = len(prices_now)
    product = 1.0
    for c_now, c_prev in zip(prices_now, prices_prev):
        product *= c_now / c_prev
    return prev_index * (product ** (1.0 / n))

def index_value_line_arith(prev_index: float,
                           prices_now: Sequence[float],
                           prices_prev: Sequence[float]) -> float:
    n = len(prices_now)
    ratios = [(c_now / c_prev) for c_now, c_prev in zip(prices_now, prices_prev)]
    return prev_index * (sum(ratios) / n)