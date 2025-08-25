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

## Installation

### Python (PyPI)

Install the latest release from PyPI:

```bash
pip install fincraftr
```

Then use in Python:

```python
import fincraftr as fc

# Calculate simple return
return_val = fc.return_simple(105, 100)  # 0.05

# Access by module
option_payoff = fc.options.payoff_call(105, 100)  # 5.0
compound_value = fc.rates.compound_discrete(1000, 0.05, 12, 1)
forward_price = fc.forwards.forward_price_no_div(100, 0.05, 1)
```

### C++ (vcpkg)

Add FinCraftr to your `vcpkg.json`:

```json
{
  "dependencies": ["fincraftr"]
}
```

Then in your CMakeLists.txt:

```cmake
find_package(fincraftr CONFIG REQUIRED)
target_link_libraries(myapp PRIVATE fincraftr::fincraftr)
```

Use in C++:

```cpp
#include <fincraftr/equity/returns.hpp>
#include <fincraftr/options/payoff.hpp>

double return_val = fc::equity::return_simple(105.0, 100.0);  // 0.05
double call_payoff = fc::options::payoff_call(105.0, 100.0);  // 5.0
```

### Manual Build from Source

#### C++ Library

```bash
# Header-only (default)
cmake -B build -DFINCRAFTR_HEADER_ONLY=ON
cmake --build build
cmake --install build --prefix /usr/local

# Or with compiled libraries
cmake -B build -DFINCRAFTR_HEADER_ONLY=OFF -DFINCRAFTR_BUILD_SHARED=ON
cmake --build build
cmake --install build --prefix /usr/local
```

#### Python Package

```bash
# Install build dependencies
pip install pybind11 cmake ninja

# Build and install
pip install .

# Or build wheel
python -m build
pip install dist/*.whl
```

---

## Repository Layout

```text
cpp/include/fincraftr/     # C++20 headers (header-only implementations)
├─ equity/                 # equity analysis (returns, valuation, indices)
├─ options/                # options pricing and analysis
├─ forwards/               # forward contract pricing
└─ rates/                  # interest rates and discounting

python/
├─ fincraftr/              # Python package with fallback implementations
└─ bindings/               # pybind11 C++ bindings

CMakeLists.txt             # C++ build configuration
vcpkg.json                 # vcpkg package manifest
pyproject.toml             # Python package configuration
.github/workflows/         # CI/CD pipelines
```

---

## API Documentation

All functions include comprehensive docstrings accessible via `help()` in Python or doxygen-style comments in C++.

### Equity Module

- `return_simple(Pt, Pt_prev)` - Simple return calculation
- `market_cap(shares, price)` - Market capitalization
- `ddm_gordon_growth(D1, r, g)` - Gordon growth dividend discount model
- Index functions: `index_price_weighted`, `index_cap_weighted`, etc.

### Options Module  

- `payoff_call(ST, K)`, `payoff_put(ST, K)` - Option payoffs
- `price_binomial_one_period(...)` - Binomial option pricing
- `check_put_call_parity(...)` - Put-call parity validation

### Rates Module

- `compound_discrete(p0, r, m, years)` - Discrete compounding
- `compound_continuous(p0, r, t)` - Continuous compounding  
- `nominal_to_continuous(R, m)` - Rate conversions

### Forwards Module

- `forward_price_no_div(S, r, tau)` - Forward pricing without dividends
- `forward_price_with_div(S, D, r, tau)` - With discrete dividends
- `forward_price_cont_yield(S, r, q, tau)` - With continuous yield

---

## Language & Tooling

* **Python:** 3.8+ with NumPy support
* **C++:** C++20 headers (header-only by default, compiled libraries optional)
* **Build:** CMake 3.20+, vcpkg support, PyPI distribution
* **CI:** GitHub Actions for Windows, Linux, macOS

---

## Contributing

* Keep modules **small and orthogonal**; document inputs, conventions, and failure modes in a short module README (see module templates in `docs/`).
* Add matching unit tests in **both languages** where it makes sense.
* Include tiny, attribution-safe test fixtures in `data/` if needed.

---

## License

MIT. See `LICENSE` for details.

---
