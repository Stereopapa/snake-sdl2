# Snake 2 - SDL2 2D Engine

A low-level implementation of the classic Snake game developed in **C++** using the **SDL2** (Simple DirectMedia Layer v2.32.10) library. The project demonstrates direct hardware-accelerated rendering, manual memory management, and a custom delta-time based game loop.


---

## Tech Stack
* **Language:** C++17
* **Graphics API:** SDL2 (2D Rendering Context)
* **Architecture:** State Machine (`PLAYING`, `LOOSE`, `QUIT`), Decoupled Game Loop
* **Platform:** Windows (Visual Studio)

---

## Core Mechanics & Engineering Logic

### 1. Custom Game Loop & Timing
The engine separates rendering from the game logic state:
* **Delta Time Tracking:** The `Timer` class calculates `dTime` to decouple the game logic from the frame rate, ensuring consistent movement speed regardless of hardware.
* **Dynamic Difficulty:** The snake's speed dynamically scales over time using `mulitplySnakeTimeToMove()`, increasing the challenge as the session progresses.
* **Performance Metrics:** Integrated real-time FPS counter and world timer.

### 2. Memory & Entity Management
The snake's body is managed using a custom **Doubly Linked List** (`Node<SDL_Rect>`) instead of standard vectors. This guarantees $O(1)$ complexity for tail removal and head insertion during movement and growth, optimizing memory operations.

### 3. Collision & Item System
* **AABB Collision:** Precise Axis-Aligned Bounding Box intersection logic to detect self-collisions and boundary hits.
* **Standard Item (Blue Dot):** Triggers standard growth and increments the score.
* **Dynamic Event Item (Red Dot):** A time-limited entity managed by a visual `ProgressBar`. Consuming it triggers a randomized event:
  * *Penalty:* Removes 3 segments from the snake's tail (`SNAKE_REDDOT_REMOVE_AMOUNT`).
  * *Buff:* Drastically slows down the snake's movement speed (`SNAKE_REDDOT_SLOWDOWN_AMOUNT`), allowing for tactical repositioning.

### 4. Bitmap Typography
Instead of relying on heavy TTF libraries, the UI (`Info.cpp`) implements a custom rendering pipeline. It reads a bitmap sprite sheet (`charset.bmp`) and dynamically blits specific `8x8` pixel areas based on ASCII character calculations.

---

## Installation & Execution

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Stereopapa/snake-sdl2.git
   cd snake-sdl2

   ## Build the Solution

2. **Build the Solution:**
* **Open the solution** (`.sln`) in Visual Studio 2022.
* **Set the build configuration** to **Release** and platform to **x64**.
* **Link SDL2 libraries**: Ensure that SDL2 include and library paths are properly configured in the project properties.
* **Build the solution**: Press `Ctrl+Shift+B` or select *Build > Build Solution*.

---

3. **Run the Game**

    Launch the executable from the output directory using the terminal or by double-clicking the file:

    ```bash
    ./x64/Release/Snake_C.exe
### Controls

* **Arrow Keys**: Change snake movement direction.
* **N**: Start a New Game (available on the game over screen).
* **ESC**: Exit the application.