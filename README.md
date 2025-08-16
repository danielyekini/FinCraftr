# FinCraftr

**FinCraftr** is a bilingual (Python + C++20) toolkit for **quantitative finance**.
Its goal is to provide clean, composable building blocks for **pricing, risk, portfolio analytics, and market data modelling**, implemented with parallel APIs across both languages.

> **Disclaimer:** This software is for research and engineering purposes only and does not constitute investment advice.

---

## Purpose & Scope

* **Production-minded primitives.** Small, orthogonal functions and components that can be assembled into full valuation and risk workflows: discounting/curves, cash-flow schedules, instrument pricing, time-series/econometrics, portfolio construction, and diagnostics.
* **Bilingual parity.** Each major concept appears in **Python** (for exploration and pipelines) and **C++20** (for performance and embedding). Namespaces and semantics mirror each other to minimise cognitive switching.
* **Transparency of assumptions.** Modules make **units, conventions, and modelling choices explicit** (e.g., compounding basis, day-count, interpolation). Where trade-offs exist, they’re documented at the module boundary.
* **Deterministic & testable.** Functions are pure (no hidden globals), accept explicit inputs, and are covered by language-specific unit tests for reproducibility and cross-language consistency.
* **Interoperability.** Designed to plug into existing research stacks (NumPy/Pandas, CMake-based C++ projects) without bespoke infrastructure.

**What this repository aims to cover**

* Core **rates/curves** utilities (discount factors, compounding conventions, bootstrapping & interpolation).
* **Instrument pricing** surfaces (fixed-income, equity/vanilla options, swaps) that depend on the core utilities.
* **Time-series & econometrics** helpers (returns, diagnostics, forecasting) used by risk and strategy modules.
* **Portfolio & risk** primitives (covariance handling, optimisation interfaces, sensitivities/Greeks, P\&L explain).
* **Validation tools** (reference datasets, sanity checks, numerical diagnostics).

**What is explicitly out of scope**

* Live brokerage/exchange connectivity and order routing.
* Proprietary vendor data access layers.
* High-frequency trading engines or latency-sensitive infra.
* A drop-in replacement for QuantLib—FinCraftr is intentionally lighter-weight and modular.

---

## Design Principles

1. **Separation of concerns:** low-level rate/curve mechanics are isolated from instrument pricing; pricing is isolated from portfolio/risk layers.
2. **Explicit conventions:** compounding basis, day-count, calendars, and interpolation must be provided or selected; no silent defaults that change results across environments.
3. **Numerical robustness:** prefer stable formulations; document error bounds and known edge cases.
4. **Small surface area:** fewer, clearer functions over large, opinionated classes.
5. **Symmetry:** Python and C++ exports follow the same naming and signatures where practical.

---

## Repository Layout

```text
fin_craftr/                # Python package
├─ interest/               # rate/curve mechanics (discounting, compounding, bootstrapping)
├─ pricing/                # instrument-level valuation built on interest/*
├─ stats/                  # time-series & diagnostics
├─ portfolio/              # optimisation & risk primitives
include/fin_craftr/        # C++20 headers mirroring the Python modules
tests/
├─ python/                 # pytest suites
└─ cpp/                    # Catch2 suites
docs/                      # short concept notes and API docs
data/                      # small, non-proprietary fixtures for tests
examples/                  # minimal runnable snippets (both languages)
```

> Module borders matter: **`interest/`** hosts reusable rate/curve utilities; **`pricing/`** hosts instrument calculators that *consume* them. Other top-level modules follow the same pattern.

---

## Language & Tooling

* **Python:** 3.10+ (type-hinted).
* **C++:** C++20 headers (header-only where sensible).
* **Build/Test:** CMake for C++; pytest for Python; Catch2 for C++ tests.
* **Style:** Black/Ruff for Python; clang-format for C++.

---

## Contributing

* Keep modules **small and orthogonal**; document inputs, conventions, and failure modes in a short module README (see module templates in `docs/`).
* Add matching unit tests in **both languages** where it makes sense.
* Include tiny, attribution-safe test fixtures in `data/` if needed.

---

## License

MIT. See `LICENSE` for details.

---
