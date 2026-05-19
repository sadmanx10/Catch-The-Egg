<div align="center">

# 🥚 Catch The Eggs Game 🐔

### A Fun 2D OpenGL GLUT Arcade Game

<img src="https://img.shields.io/badge/Language-C++-blue?style=for-the-badge"/>
<img src="https://img.shields.io/badge/OpenGL-GLUT-green?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Platform-Windows-orange?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Game-2D-yellow?style=for-the-badge"/>

---

🎮 Catch eggs using the basket while avoiding poop and collecting special powerups!  
🔥 Built using **C++, OpenGL, GLUT, and Windows Multimedia API**

</div>

---

# 📌 Features

✨ Smooth 2D Animation  
✨ Chicken Movement Animation  
✨ Multiple Egg Types  
✨ Sound Effects  
✨ Power-Up System  
✨ Increasing Difficulty  
✨ Mouse + Keyboard Controls  
✨ Game States (Menu, Help, Pause, Game Over)  
✨ Real-Time Score & Timer  
✨ Broken Egg Animation  

---

# 🎯 Gameplay

The chicken moves left and right on the bamboo stick and drops different objects.

The player controls a basket to catch eggs and avoid harmful objects.

---

# 🥚 Object Types

| Object | Effect |
|---|---|
| 🥚 Normal Egg | +1 Score |
| 🔵 Blue Egg | +5 Score |
| 🟡 Golden Egg | +10 Score |
| 💩 Poop | -10 Score |
| 🟪 Big Basket | Increases Basket Size |
| 🟦 Slow Speed | Slows Falling Speed |
| 🟩 Extra Time | Adds Extra Time |

---

# 🎮 Controls

| Key | Action |
|---|---|
| ⬅ Left Arrow | Move Basket Left |
| ➡ Right Arrow | Move Basket Right |
| 🖱 Mouse Move | Move Basket |
| ⏎ ENTER | Start / Restart Game |
| P | Pause / Resume |
| H | Help Menu |
| M | Back to Menu |
| ESC | Exit Game |

---

# 🛠 Technologies Used

- C++
- OpenGL
- GLUT
- Windows Multimedia API
- 2D Graphics Programming

---

# 🧠 Concepts Used

✔ Event Driven Programming  
✔ Collision Detection  
✔ Animation  
✔ Timers  
✔ Random Object Generation  
✔ Sound Integration  
✔ 2D Projection  
✔ OpenGL Primitives  

---

# 🏗 Game Architecture

```text
Main Loop
   │
   ├── Display Function
   ├── Update Function
   ├── Timer Functions
   ├── Keyboard Input
   ├── Mouse Input
   └── Collision Detection
```

---

# 🐔 How Chicken is Drawn

The chicken is built using OpenGL primitive shapes:

- 🔵 Circles → Body, Head, Eye
- 🔺 Triangles → Beak, Tail
- ➖ Lines → Legs

This technique is called:

## ✨ Primitive Based Modeling

---

# 🥚 How Egg Shape is Made

The egg is created using an ellipse formula:

```cpp
x = xc + a * cos(theta)
y = yc + b * sin(theta)
```

Where:

- `a` = horizontal radius
- `b` = vertical radius

Different radii create an oval egg shape.

---

# ⚡ Speed Control System

## Chicken Movement

```cpp
chickenX += chickenSpeed;
```

## Falling Speed

```cpp
obj.y -= currentSpeed;
```

## Difficulty Increase

Every 10 seconds:

```cpp
globalFallSpeed += 0.7;
```

---

# 🔊 Sound System

The game uses:

```cpp
PlaySound()
```

from the Windows Multimedia API.

### Sounds Included:
- Catch Sound
- Miss Sound

---

# 🖼 Screens

## 🏠 Main Menu
- Start Game
- Help Menu
- Exit

## 🎮 Gameplay
- Real-time Score
- Timer
- Falling Objects
- Powerups

## ⏸ Pause Screen
- Resume Option

## 💀 Game Over
- Final Score
- High Score

---

# 📂 Project Structure

```text
Catch-The-Eggs/
│
├── main.cpp
├── catch.wav
├── miss.wav
├── README.md
```

---

# ⚙ Installation & Run

## 🔹 Requirements

- CodeBlocks / Visual Studio
- OpenGL
- GLUT Library
- Windows OS

---

## 🔹 Compile

```bash
g++ main.cpp -o game -lopengl32 -lglu32 -lfreeglut -lwinmm
```

---

# 🚀 How To Run

1. Open project in CodeBlocks or Visual Studio
2. Add GLUT library
3. Compile the project
4. Run the executable

---

# 📸 Suggested Screenshots

Add screenshots here:

```md
![Menu](screenshots/menu.png)
![Gameplay](screenshots/gameplay.png)
![GameOver](screenshots/gameover.png)
```

---

# 🧑‍💻 Developer

## 👨‍💻 Sadman Sakib & Md. Tausif Uddin

CSE Student | OpenGL Enthusiast | Game Developer

---

# 🌟 Future Improvements

- 🔥 Multiple Levels
- 🎵 Background Music
- 👾 Enemy Birds
- 💥 Particle Effects
- 🏆 Online Leaderboard
- ❤️ Health System

---

# 📜 License

This project is made for educational and academic purposes.

---

<div align="center">

# ⭐ If you like this project, give it a Star ⭐

</div>
