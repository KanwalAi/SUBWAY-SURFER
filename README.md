# Subway Surfers 2D

A 2D endless runner inspired by Subway Surfers, developed in C++ using SFML.

The project focuses on implementing Object-Oriented Programming concepts in a complete game environment, including inheritance, polymorphism, abstraction, collision detection, state-machine gameplay logic, and STL-based object management.

Players navigate through a three-lane track, avoid dynamically generated obstacles, collect coins, activate power-ups, and survive as the game progressively increases in speed and difficulty.

---

## Gameplay Demo

[Gameplay Video](https://drive.google.com/file/d/1Fsim-kxk77eHOSV-zZBL4D9sjmNyX2EX/view?usp=drive_link)

---

## Gameplay Overview

The player continuously moves forward through a three-lane track while avoiding obstacles, collecting coins, and activating temporary power-ups.

As gameplay progresses:

- Player speed increases
- Obstacles spawn more frequently
- Reaction timing becomes more demanding

The game uses a strict state-based player system to prevent conflicting actions such as jumping while sliding.

### Player States

```cpp
RUNNING
JUMPING
SLIDING
```

---

## Core Features

### Three-Lane Movement System

The player can switch between:

- Left Lane (200px)
- Middle Lane (400px)
- Right Lane (600px)

Movement is restricted to these lanes to replicate classic endless-runner mechanics.

---

### Dynamic Difficulty Scaling

Difficulty increases automatically over time through:

- Increased player movement speed
- Faster obstacle spawning
- Reduced reaction windows

This creates progressively challenging gameplay.

---

## Object-Oriented Architecture

### Polymorphic Obstacle System

All obstacles inherit from an abstract base class:

```cpp
class Obstacle
```

Each obstacle implements its own collision behavior using a pure virtual function:

```cpp
virtual bool checkCollision() = 0;
```

| Obstacle | Gameplay Behavior |
|---|---|
| Train | Requires sliding underneath |
| Barrier | Must be jumped over |
| Cone | Can be avoided by jumping or sliding |
| Fence | Requires accurate jump timing |

This architecture allows new obstacle types to be added without modifying existing gameplay systems.

---

### OOP Concepts Implemented

#### Encapsulation

Gameplay variables and player attributes are kept private/protected and accessed through controlled interfaces.

---

#### Inheritance & Polymorphism

A single:

```cpp
std::vector<Obstacle*>
```

stores all active obstacle types while dynamically executing obstacle-specific collision logic at runtime.

---

#### Abstraction

Physics systems such as gravity, jumping mechanics, and movement calculations are hidden behind simplified public methods.

---

#### Composition

The `GameEngine` coordinates multiple subsystems including:

- Player
- TrackManager
- ObstacleManager
- ScoreManager

---

## STL & Template Usage

The project uses the Standard Template Library extensively for:

- Dynamic object management
- Runtime flexibility
- Memory-safe collections

Examples include:

```cpp
std::vector
```

for:
- Obstacle management
- Coin containers
- Runtime object tracking

---

## Power-Up System

The game includes an abstract `PowerUp` base class with specialized derived classes:

- Magnet
- Jetpack
- Shield
- DoubleCoin

Each power-up temporarily modifies gameplay behavior through polymorphic runtime logic.

---

## Scoring System

| Action | Points |
|---|---|
| Survival | +10 points/sec |
| Coin Collection | +50 points |

High scores and player names are automatically stored using external file handling.

---

## Controls

| Key | Action |
|---|---|
| A / Left Arrow | Move Left |
| D / Right Arrow | Move Right |
| W / Up Arrow / Space | Jump |
| S / Down Arrow | Slide |

---

## Technologies Used

- C++
- SFML
- Object-Oriented Programming
- STL
- Collision Detection
- File Handling
- State Machine Logic

---

## Project Structure

```text
Subway-Surfers-2D/
│
├── Assets/
│   ├── Fonts/
│   ├── Sprites/
│   └── Sounds/
│
├── Screenshots/
│   ├── main-menu.png
│   ├── gameplay.png
│   ├── jump.png
│   ├── slide.png
│   ├── obstacles.png
│   ├── powerups.png
│   └── score.png
│
├── Player/
├── Obstacles/
├── PowerUps/
├── Engine/
├── Managers/
│
├── main.cpp
├── README.md
└── scoreboard.txt
```

---

## Setup & Installation

### Requirements

- C++11 or higher
- SFML 2.5+
- Visual Studio / VS Code / Code::Blocks

---

### Installation Steps

1. Clone the repository

```bash
git clone https://github.com/yourusername/Subway-Surfers-2D.git
```

2. Open the project in your IDE

3. Configure SFML dependencies

4. Ensure all `.cpp` and `.h` files are included in the build

5. Place required assets inside the Assets folder

6. Build and run the project

---

## File Handling

The game stores:
- High scores
- Player names
- Score history

using external text-file persistence.

---

## Future Improvements

Potential future enhancements include:

- Animated character system
- Additional maps and environments
- Mobile support
- More obstacle types
- Online leaderboard
- Save/load progression system
- Advanced particle effects
- Background music controls

---

## Team

- Faria Javed
- Kanwal Fatima
- Ayesha Faryal

Course: Object Oriented Programming
