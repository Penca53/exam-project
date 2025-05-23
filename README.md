# exam-project

This repository contains a C++ project built with [SFML](https://www.sfml-dev.org/) and a custom game engine, [jp-engine](https://github.com/Penca53/jp-engine). It's an "exam project" and showcases various game development concepts, including tilemaps, character movement, enemy AI, and UI management.

This repository is structured into 10 distinct code checkpoints, each building upon the previous one to gradually develop the complete game. This approach allows for a clear understanding of the project's evolution and the integration of each feature.

## Project Overview

The game features a player navigating a tile-based environment, battling different types of enemies, and managing health. The core gameplay loop involves:

* **Player Movement and Combat:** The player can move around the map and engage with enemies using a pistol.
* **Enemy AI:** Different enemy types (Ghosts, Shooting Ghosts, and a Goblin boss) have unique behaviors and attack patterns, including melee and ranged attacks.
* **Tilemap:** The game world is constructed using a tilemap for ground and wall elements, influencing character movement and projectile collisions.
* **Physics and Collision:** Basic collision detection is implemented for characters, projectiles, and pickups.
* **UI Management:** Displays critical game information such as health and score, and presents win/lose screens.
* **Resource Management:** Handles loading of textures, fonts, and sounds for in-game assets.
* **Pickups:** Players can find health pickups to restore health and large bullet pickups to temporarily enhance their pistol.

## Prerequisites

To build and run this project, you will need:
- **CMake**: A cross-platform open-source build system.
- **C++ 23 Compatible Compiler**: A compiler that supports the C++23 standard. The project has been developed and tested with **Clang 17**.

## Summary of Source Files

Below is a glimpse into some of the key C++ source files that make up this project:

* `default_scene`: Initializes the game world, including tilemaps, player, enemies, and UI elements.
* `enemy_spawner`: Manages the spawning of different enemy types based on game state.
* `follow_player`: A component that makes the camera follow the player.
* `game_manager`: Controls the overall game state, including win/lose conditions and scene transitions.
* `ghost_bullet`: Implements the behavior of projectiles fired by shooting ghosts.
* `ghost`: Defines the common ghost enemy, including movement, damage, and death.
* `goblin_pistol_bullet`: Implements the behavior of projectiles fired by the goblin boss.
* `goblin_pistol`: Represents the goblin's weapon, handling its firing mechanism and visual representation.
* `goblin_pistol_holder`: Manages the goblin's weapon, including aiming and flipping.
* `goblin`: Implements the boss enemy, with more complex movement, attacks, and health.
* `health_pickup`: Defines a health-restoring item that can be picked up by the player.
* `large_bullet_pickup`: Defines a power-up item for larger bullets.
* `lose_canvas`: Manages the "Game Over" screen.
* `main`: The entry point of the application, responsible for setting up the SFML window and loading the initial scene.
* `pistol_bullet`: Implements the behavior of projectiles fired by the player's pistol.
* `pistol`: Defines the player's primary weapon, including its shooting mechanics and visual representation.
* `player_weapon_holder`: Manages the player's weapon, handling aiming based on mouse position and weapon flipping.
* `player`: Implements the main player character, including movement, health management, score tracking, and interaction with pickups.
* `shooting_ghost`: Defines a variant of the ghost enemy that can shoot projectiles.
* `tile_id`: An enumeration defining the different types of tiles used in the game's tilemaps.
* `ui_manager`: Handles the display and updates of in-game UI elements like score and health.
* `win_canvas`: Manages the "You Won" screen.