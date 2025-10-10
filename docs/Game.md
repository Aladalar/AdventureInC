# Game - Core Coordinator

## Purpose
Central game loop controller and system coordinator. Manages game lifecycle, owns all managers, and orchestrates high-level game flow.

## Responsibilities
- **Lifecycle Management**: Three-phase initialization (preInit, initialize, postInit)
- **Region Management**: Load/unload regions, maintain loaded region cache
- **Scene Management**: Switch between scenes, coordinate scene transitions
- **Manager Coordination**: Own and update all game managers each frame
- **Main Loop**: Run game loop, coordinate Update() and Draw() calls

## Key Concepts

### Three-Phase Initialization
1. **preInit()**: Window creation, basic Raylib setup, logger initialization
2. **initialize()**: Create and initialize all managers
3. **postInit()**: Load initial region/scene, final setup before game starts

### Region Caching
Regions stay loaded in memory map (`loadedRegions`) until explicitly unloaded. Allows fast scene switching within loaded regions without reloading assets.

### Scene Lifecycle
When changing scenes:
1. Call `currentScene->onLeave()` - Trigger exit events/animations
2. Switch `currentScene` pointer to new scene
3. Call `currentScene->onEnter()` - Trigger entry events/cutscenes
4. Update ScreenManager with new scene

## Public Methods
- `preInit()` - Window and basic setup
- `initialize()` - Manager creation
- `postInit()` - Initial game state setup
- `run()` - Main game loop
- `quit()` - Cleanup and shutdown
- `loadRegion(Region*)` - Add region to cache and load its scenes
- `unloadRegion(Region*)` - Remove region from memory
- `setScene(regionName, sceneName)` - Switch to different scene

## Game Loop Structure
while running:
- Process input
- Update managers
- Draw via ScreenManager

## Owned Systems
- GameObject (game state)
- ScreenManager (rendering)
- All other managers (input, navigation, pawns, quests, dialogue)
- Current region/scene references

## Design Notes
- Game is NOT a singleton - owned by main()
- Managers are direct members, not pointers (simpler memory management)
- Region/Scene are pointers (polymorphic, heap-allocated)