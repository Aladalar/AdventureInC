# AdventureInC - Project Overview

A C++ point-and-click adventure game inspired by **Legend of Kyrandia** using **Raylib**.

**Target:** Windows & Linux | **Resolution:** 1920x1080 | **Purpose:** Learning C++

---

## Architecture
┌────────────────────────────────────────────────────────┐
│                       Main.cpp                         │
│  • Initialize Raylib window                            │
│  • Create Game instance                                │
│  • Run game loop                                       │
│  • Cleanup on exit                                     │
└────────────────────────────────────────────────────────┘
                              │
                              ▼
┌────────────────────────────────────────────────────────┐
│                       Game.cpp                         │
│  • Lifecycle coordinator                               │
│  • Owns all managers                                   │
│  • Orchestrates Update() and Draw() calls              │
│  • Handles scene transitions                           │
│  • Manages save/load operations                        │
└────────────────────────────────────────────────────────┘
                              │
        ┌─────────────────────┼─────────────────────┐
        ▼                     ▼                     ▼
┌──────────────┐    ┌──────────────┐      ┌──────────────┐
│  GameObject  │    │   Managers   │      │ SceneObject  │
│              │    │              │      │              │
│ Game State   │    │ 7 Systems    │      │ Scene Data   │
│ Save Data    │    │              │      │              │
└──────────────┘    └──────────────┘      └──────────────┘

┌─────────────────────────────────────┐
│ Game Loop (60 FPS)                  │
│                                     │
│  Update():                          │
│    • Check F1 for debug toggle      │
│    • InputManager.Update()          │
│    • NavigationManager.Update()     │
│    • PawnManager.Update()           │
│    • QuestManager.Update()          │
│    • DialogueManager.Update()       │
│                                     │
│  Draw():                            │
│    • ScreenManager.Draw()           │
│    • Draw debug overlays if enabled │
└─────────────────────────────────────┘

---

## Components

### Main.cpp
Entry point - Initialize window, create Game, run loop, cleanup

### Game.cpp
Lifecycle coordinator - owns managers, orchestrates Update()/Draw(), handles scene transitions, save/load

### GameObject
Pure data container - scene ID, player position, inventory[10], quest flags, story variables
- Binary save format with "KYRA" magic number and checksum

### ScreenManager
Rendering coordinator - draws layers (background → objects → pawns → UI → debug)
- F1 debug overlays: walkable areas, transitions, interactables, paths, hitboxes, FPS

### SceneObject
Scene data container
- Assets: background texture, RGB interaction map, navigation grid
- Data: interactables, transitions, NPC spawns, metadata

**RGB Interaction Map:**
- R=255 → Walkable areas
- G=255 → Transitions
- B=255 → Interactables
- Channels can overlap

### InputManager
Input → Action translation
- Detects clicks, checks RGB channels, determines type, triggers actions
- Priority: UI > Interactables > Transitions > Walkable

### NavigationManager
Pathfinding and movement
- 100px grid cells (19×11)
- Breadth-First Search pathfinding
- Returns waypoint vectors

### QuestManager
Quest logic and progression
- Tracks states: NOT_STARTED, ACTIVE, COMPLETED, FAILED
- Handles item usage, checks conditions, updates flags, gives rewards

### DialogueManager
Dialogue system
- Linear with flag-based branching
- Returns text based on GameObject flags
- Bottom-center dialogue box display

### PawnManager
Entity management
- Owns: player, NPCs, animated objects
- Spawns, updates, handles interactions

### Pawn
Animated entity base class
- Position & movement
- Animation
- Interaction callbacks

### Player (extends Pawn)
Player-controlled pawn
- Inventory access
- Keyboard input
- Persists across scenes

---

## Key Design Decisions

**RGB Map:** Single image for all interactions (R=nav, G=transition, B=interact)

**Saves:** Binary format (not easily editable)

**Inventory:** Kyrandia-style grid (10 slots)

**Dialogue:** Linear text-based

**Animation:** 4-way sprite sheets (64×64 frames, 10 FPS)

**Debug:** F1 toggle for overlays

**Managers:** Owned by Game (not singletons)

**Assets:** Per-scene loading with fade transitions

---

## Development Phases

1. **Foundation:** Empty manager structure, get compiling
2. **Scene Rendering:** Background loading and display
3. **Input & Navigation:** Click detection, RGB checking, pathfinding
4. **Player Movement:** Spawn player, movement along paths
5. **Animation:** Sprite sheets and frame logic
6. **Interactions:** Interactables, transitions, quests, dialogue

---

## File Formats

**.scene (binary):** Scene ID, asset paths, interactables, transitions, NPC spawns

**.dat (binary):** Magic "KYRA", version, timestamp, game state, checksum

**dialogues.txt:** Simple text format with NPC ID, line ID, flags, text