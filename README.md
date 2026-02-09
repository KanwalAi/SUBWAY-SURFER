# Subway Surfers 2D: Object-Oriented Implementation

A high-fidelity, three-lane infinite runner developed in **C++** using the **SFML (Simple FastMedia Library)**. This project serves as a comprehensive demonstration of advanced Object-Oriented Programming (OOP) principles including polymorphism, state-machine logic, and template-based resource management.

## ## 🕹️ Core Gameplay Logic

* **Automatic Movement:** The player moves forward automatically, with game difficulty scaling dynamically as speed and spawn rates increase over time.
* **Three-Lane System:** Restricted movement between Left (200px), Middle (400px), and Right (600px) lanes.
* **State Machine:** To prevent conflicting actions (like jumping while sliding), the player exists in a strict state-based system: `RUNNING`, `JUMPING`, or `SLIDING`.

## ## 🚀 Technical Features

### ### 1. Polymorphic Obstacle System

The game utilizes a deep inheritance hierarchy for obstacles. All obstacles inherit from an abstract base class `Obstacle`, which enforces a pure virtual `checkCollision` function.

| Obstacle | Behavior Logic |
| --- | --- |
| **Train** | Very tall; must be avoided by sliding underneath. |
| **Barrier** | Short; must be jumped over. |
| **Cone** | Small; can be avoided by both jumping or sliding. |
| **Fence** | Medium height; requires a high-precision jump to clear. |

### ### 2. OOP Implementation Details

* **Encapsulation:** All attributes are strictly private or protected, accessible only through defined methods.
* **Inheritance & Polymorphism:** A single `std::vector<Obstacle*>` manages all active obstacles, executing type-specific collision logic at runtime.
* **Abstraction:** Physics calculations like gravity () and parabolic jump arcs are hidden behind simple public interfaces.
* **Composition:** The `GameEngine` class acts as the central manager, controlling the lifecycle of the `Player`, `TrackManager`, and `ScoreManager`.

### ### 3. Template Usage

As required by the project mandate , templates are applied via the **Standard Template Library (STL)**. The engine utilizes `std::vector` for:

* **Type Safety:** Ensuring `Coin` and `Obstacle` pointers are never mixed.
* **Dynamic Resizing:** Managing active game objects without fixed array limitations.

## ## ⌨️ Controls

| Key | Action |
| --- | --- |
| **A / Left Arrow** | Move Left 

 |
| **D / Right Arrow** | Move Right 

 |
| **W / Up / Space** | Jump (triggers upward velocity) 

 |
| **S / Down Arrow** | Slide (0.5-second duration) 

 |

## ## ⚙️ Scoring & Power-Ups

* **Survival:** 10 points per second.
* **Collection:** 50 points per coin.
* **Power-Ups:** Abstract `PowerUp` class with derived types: `Magnet`, `Jetpack`, `Shield`, and `DoubleCoin`.
* **File Handling:** Highest scores and player names are automatically updated and persisted in an external file.

---

## ## 🛠️ Setup & Installation

1. **Dependencies:** Install **SFML 2.5+**.
2. **Architecture:** Ensure all `.h` and `.cpp` files are included in your build environment.
3. **Assets:** Place required sprites and fonts in the designated project folder for the UI to load correctly.

---

### ### Project Team

* **Faria Javed** (I242035)
* **Kanwal Fatima** (I243128)
* **Ayesha Faryal** (I240019)
* **Course:** Object Oriented Programming
