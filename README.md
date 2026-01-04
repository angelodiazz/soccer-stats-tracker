# Soccer Stats Tracker (C++)

A C++ application for tracking and analyzing soccer player performance statistics using validated user input and structured data handling. This project was built to demonstrate clean program organization, defensive input validation, and modular object-oriented design.

## Features
- Create and manage **soccer player profiles** with unique identifiers
- Record and track **player performance statistics** across matches
- Automatically compute **per-match performance metrics**
- Generate **individual player summaries** and **team-level analytics**
- **Input validation** to prevent invalid or inconsistent entries
- **CSV-based persistence** to save and load player data

## Design Overview
The program is structured into focused components:
- **Player data models** represent individual players and their statistics
- **Tracking and analytics logic** manages aggregation and performance calculations
- **CSV file handling utilities** provide persistent storage of player data
- **User input handling** is centralized to ensure valid and consistent data entry

This design improves maintainability, data integrity, and extensibility.

## Project Structure
```text
soccer-stats-tracker/
├── src/
│   ├── main.cpp
│   ├── Player.h
│   ├── Player.cpp
│   ├── StatsTracker.h
│   ├── StatsTracker.cpp
│   ├── Input.h
│   └── Input.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Build & Run
# Configure the project
cmake -S . -B build

# Build the executable
cmake --build build

# Run the application
./build/soccer-stats-tracker
