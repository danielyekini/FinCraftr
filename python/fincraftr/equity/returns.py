def return_simple(Pt: float, Pt_prev: float) -> float:
    if Pt_prev == 0:
        raise ValueError("Previous price must be nonzero")
    return (Pt / Pt_prev) - 1.0
