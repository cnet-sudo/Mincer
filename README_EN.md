# Mincer

[Русский](README.md) | **English**

![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus)
![SFML](https://img.shields.io/badge/SFML-2.6.x-8CC445)
![Genre](https://img.shields.io/badge/genre-top--down%20shooter-B22222)

A fast-paced top-down shooter built with SFML. Explore large planets, destroy
hordes of monsters, collect power-ups, and complete five increasingly
difficult levels.

## Features

- large procedurally populated play areas;
- eight-direction character movement;
- shooting toward the mouse cursor;
- a shop, reloading, and ammunition reserves;
- several monster types with different difficulty levels;
- health and ammunition pickups;
- camera zoom controlled with the mouse wheel;
- pause, help, music, and sound effects;
- score and high-score storage in `gamedata/scores.txt`;
- five levels followed by a harder new cycle after victory.

## Controls

| Key | Action |
|---|---|
| `W`, `A`, `S`, `D` | move in the four main directions |
| `Q`, `E`, `Z`, `C` | move diagonally |
| `X` | stop |
| Left mouse button | shoot toward the cursor |
| Right mouse button or `R` | reload |
| Mouse wheel | change camera zoom |
| `Pause` | pause |
| `Tab` | show or hide help |
| `M` | toggle music |
| `Space` | continue from level and result screens |
| `Esc` | save the high score and quit |

## Architecture

| Component | Responsibility |
|---|---|
| `GameEngine` | states, input, game loop, and object interaction |
| `Player` | movement, health, and character orientation |
| `Monster` | behavior of an individual enemy |
| `MonsterPlanet` | world and horde generation |
| `Bullet` | projectile pool and movement |
| `Pickup` | health and ammunition bonuses |
| `Levels` | title cards and level transitions |
| `GameText` | HUD, help, and result messages |
| `AssetManager`, `GameSound` | assets and audio |

## Building with CMake

CMake 3.21+, Git, and a C++20 compiler are required.

```powershell
cmake -S . -B build -DBUILD_SHARED_LIBS=OFF
cmake --build build --config Release
./build/Release/Mincer.exe
```

SFML 2.6.x is downloaded automatically. The `graphics`, `fonts`, `sound`, and
`gamedata` directories are copied next to the executable.

When building `Mincer.sln`, update the absolute SFML paths in the project
properties. The saved Visual Studio configuration refers to SFML 2.5.1.

## Status

Playable educational project. Possible improvements include continuous
movement while keys are held, configurable controls, saved settings, and
optimization for large enemy waves.
