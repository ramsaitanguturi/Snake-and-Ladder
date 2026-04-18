# 🐍 Snakes and Ladders (C Terminal Game)

A fully interactive **Snakes and Ladders** game implemented in C with colorful terminal UI, dice animations, and two-player gameplay.

---

## 📌 Project Overview

This project simulates the classic board game **Snakes and Ladders** in the terminal. It supports:

* Two-player gameplay
* Dice rolling with animation
* Snakes and ladders mechanics
* Colorful board rendering
* Start menu and rules display

Source code: 

---

## 🎮 Features

* 🎲 Animated dice roll
* 🧑‍🤝‍🧑 Two-player turn-based gameplay
* 🐍 Snakes that pull players down
* 🪜 Ladders that lift players up
* 🎨 Colored board rendering using ANSI escape codes
* 📜 Interactive menu (Start / Rules / Exit)
* ⏳ Loading animation screen

---

## 🛠️ Technologies Used

* **C Programming Language**
* Standard libraries:

  * `stdio.h`, `stdlib.h`, `time.h`
* Platform-specific:

  * `windows.h` (for `Sleep`)
  * `unistd.h`
  * `conio.h`
* ANSI escape codes for colors and UI

---

## 📂 Project Structure

```
snakes_and_ladders.c   # Main source code
README.md              # Project documentation
```

---

## ▶️ How to Run

### Step 1: Compile

Using GCC:

```bash
gcc snakes_and_ladders.c -o game
```

### Step 2: Run

```bash
./game
```

---

## 🎯 Game Rules

* Players take turns rolling a dice.
* A player must roll **6** to start moving.
* Rolling **6** gives an extra turn.
* Landing on:

  * 🪜 Ladder → climb up
  * 🐍 Snake → slide down
* First player to reach **100** wins.

---

## 🧠 Game Logic Summary

### 1. Board Representation

* 10x10 grid (`char arr[10][10]`)
* Numbers arranged in zig-zag pattern

### 2. Dice System

* Random number between 1–6
* Animated dice display

### 3. Player Movement

* Validates movement (cannot exceed 100)
* Applies snake/ladder logic using arrays:

  ```c
  snakeHead[] / snakeTail[]
  ladderBottom[] / ladderTop[]
  ```

### 4. Turn Handling

* Alternates between Player 1 and Player 2
* Extra turn on rolling 6

---

## 🎨 UI Highlights

* Colored terminal output using ANSI codes
* Board with alternating colored tiles
* Player indicators:

  * `P1` → Player 1
  * `P2` → Player 2

---

## ⚠️ Platform Notes

* Works best on **Windows terminal**
* Uses:

  * `Sleep()` → Windows-specific
  * ANSI colors → may require compatible terminal

---

## 🚀 Possible Improvements

* Single-player mode vs computer
* GUI version (using SDL/OpenGL)
* Save/load game state
* Custom board sizes
* Sound effects

---

## 👥 Authors

* T Ram Sai
* Ayush Gatla
* Pankaj Maulekhi
* Abhilash Kumar

---

## 📜 License

This project is for educational purposes. Modify and use freely.

---
