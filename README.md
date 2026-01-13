# Soccer Stats Tracker (C++17)

A robust performance analytics engine designed to track, aggregate, and analyze athlete metrics. This project demonstrates high-fidelity **Data Management**, **CSV Parsing Architecture**, and **Functional Programming** patterns in C++.

---

## 🚀 Key Engineering Features
* **Custom CSV Serialization Engine**: Engineered a manual CSV parser with support for **quoted-string escaping** and literal double-quote handling, ensuring data integrity for complex string inputs.
* **Performance Analytics Engine**: Utilized **STL Containers** (`std::vector`) and floating-point arithmetic to compute real-time performance ratios, including goals, assists, and minutes-per-match metrics.
* **Team-Level Aggregation**: Implemented global analytics logic to determine "Top Scorer" and "Most Minutes" across the entire dataset using optimized traversal patterns.
* **Modular Object-Oriented Design**: Decoupled the `Player` data model from the `StatsTracker` management logic, facilitating high maintainability and system extensibility.

---

## 🛡 Security & Defensive Design
* **Robust Input Validation**: Centralized user input handling within the `Input` namespace, utilizing `std::numeric_limits` for stream flushing and range-bound checks to prevent program crashes.
* **Data Sanitization**: Implemented safe integer conversion using **Lambda functions** and `std::stol` with comprehensive bounds checking to prevent integer overflow during CSV ingestion.
* **Memory Safety**: Leveraged **Pass-by-Reference-to-Const** and `std::move` semantics for efficient string handling and reduced memory overhead.

---

## 🛠 Tech Stack
| Category | Technologies |
| :--- | :--- |
| **Language** | C++17 |
| **Data Management** | STL Containers, custom CSV Serialization |
| **Logic Patterns** | Lambda Expressions, Stream Manipulation |
| **Build System** | CMake |
| **Development Tools** | CLion / Git / VS Code |

---

## 📂 Project Structure
```text
soccer-stats-tracker/
├── src/
│   ├── main.cpp            # Application Controller & Menu System
│   ├── Player.h/cpp        # Entity Model & Per-Player Metrics
│   ├── StatsTracker.h/cpp  # Collection Management & CSV Logic
│   ├── Input.h/cpp         # Defensive Input Namespace
├── CMakeLists.txt          # Build Configuration
└── .gitignore              # Version Control Optimization
```

## 🚀 Build & Run
Ensure you have **CMake 3.10+** and a **C++17** compatible compiler installed.

### 1. Configure and Build
```bash
# Generate build files
cmake -S . -B build

# Compile the project
cmake --build build

```
### 2. Execute the Application
# Run the binary
```bash
./build/soccer_stats_tracker
