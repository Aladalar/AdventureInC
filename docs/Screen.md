# Screen Management System

## Purpose
Handle all rendering and visual presentation. Coordinate what appears on screen based on current game state.

## Architecture Overview
ScreenManager
↓ renders
Scene (from Region)
↓ contains
Visual Assets (background, foreground, navMap)

## Components

### ScreenManager
Central rendering coordinator. Receives scene from Game and renders it each frame.

**Responsibilities:**
- Store reference to active scene
- Coordinate render layers (background → objects → pawns → UI → debug)
- Manage debug visualization toggle
- Handle UI state (menus, dialogue visibility)

**Does NOT:**
- Own scenes (Game owns them)
- Load assets (Scenes load their own)
- Handle game logic (pure rendering)

### Region
Geographic grouping of related scenes. Represents a game area (forest, caves, castle).

**Responsibilities:**
- Own and manage collection of scenes
- Load all scenes when region is loaded
- Provide scene lookup by name
- Unload all scenes when region is unloaded

**Lifecycle:**
- Created by Game
- Loaded once, stays in memory until explicitly unloaded
- All scenes pre-loaded for fast switching

### Scene
Individual room/screen within a region. Contains all visual and interactive data for one location.

**Responsibilities:**
- Load own assets (background, foreground, navMap)
- Provide asset access to ScreenManager
- Execute entry/exit logic (onEnter/onLeave)
- Store interaction data (objects, transitions, NPC spawns)

**Assets:**
- `background` (Texture): Main visual
- `foreground` (Texture): Optional overlay layer
- `navMap` (Image): RGB channel interaction map
  - R=255: Walkable areas
  - G=255: Transition zones
  - B=255: Interactable objects

**Lifecycle:**
- Created and loaded by parent Region
- Stays loaded while region is loaded
- onEnter() called when scene becomes active
- onLeave() called when switching away

## Data Flow

### Scene Loading
Game creates Region
→ Region.load()
→ Creates Scene instances
→ Calls scene.load() for each
→ Scenes load textures/images
→ Region added to Game's loadedRegions map

### Scene Rendering
Game.run() each frame
→ ScreenManager.draw()
→ drawBackground()
→ Renders activeScene->background
→ drawPawns() (future)
→ drawUI() (future)
→ drawDebug() (if enabled)

### Scene Switching
Player triggers scene change
→ Game.setScene(regionName, sceneName)
→ currentScene->onLeave()
→ Get new scene from region
→ Update currentScene pointer
→ currentScene->onEnter()
→ screenManager.setScene(currentScene)
→ Updates activeScene reference

## File Organization
include/world/
├── region.h              (base class)
├── scene.h               (base class)
└── regions/
    ├── <RegionName>/
    └── <regionName>.h
        └── scenes/
        └── <sceneName>.h
assets/regions/
└── <region-name>/
    └── <scene-name>/
        ├── background.png
        ├── foreground.png
        └── navmap.png

## Render Layers (Future)
1. Background
2. Scene objects/items
3. Pawns (NPCs, player)
4. Foreground overlay
5. UI (inventory, HUD)
6. Dialogue boxes
7. Menus
8. Debug overlays

## Debug Visualization (F1)
- Walkable areas (red tint)
- Transition zones (green circles)
- Interactable areas (blue circles)
- Pawn hitboxes
- Path visualization
- FPS counter
- Current scene/region name

## Design Notes
- ScreenManager is render-only, no game logic
- Scenes are pre-loaded with regions for performance
- RGB channel map allows overlapping interaction types
- onEnter/onLeave handle gameplay events, not visual transitions