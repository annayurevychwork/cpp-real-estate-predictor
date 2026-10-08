# 🏠 Real Estate Price Predictor

> A C++ command-line tool that estimates maximum property prices by analyzing market data, structural features, and calculating average market deviations.

---

## 🛠️ Tech Stack & Concepts
- **Language:** C++
- **Core Concepts:** Custom Data Structures (`struct`), Vectors, Standard Library Math, Input Validation, Formatted Console Output (`<iomanip>`).

---

## ⚙️ How It Works

The program calculates property values based on predefined cost constants (e.g., price per square meter, bedroom/bathroom premiums, distance to the subway, and zoning type). It operates in two main phases:

1. **Market Data Entry (Realtor Mode):** The user inputs data for known properties to establish a baseline. The system calculates the average market error (the difference between the theoretical formula price and the actual market price).
2. **Prediction (Customer Mode):** The user inputs the features of a target property. The tool applies the base formula and adjusts it using the previously calculated market error to predict the maximum realistic price.

### Key Features
- **Strict Data Validation:** Ensures all user inputs (area, rooms, subway distance, price) fall within realistic, predefined minimum and maximum bounds.
- **Formatted Tabular Output:** Displays all entered market data in a clean, easily readable CLI table before outputting the final prediction.