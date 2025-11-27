# Interactive Story Game - La Torre del Mago

An interactive narrative game featuring Eldrin, an apprentice wizard, built with C++ and SFML.

## Project Structure

```
Minijuego/
├── src/                    # Source code files
│   ├── main.cpp           # Entry point
│   ├── Game.h/cpp         # Main game loop and coordination
│   ├── StoryManager.h/cpp # Story loading and navigation
│   ├── SkillList.h/cpp    # Linked list for skills
│   ├── Node.h/cpp         # Node structure for linked list
│   ├── RenderManager.h/cpp # Rendering management
│   └── json.hpp           # JSON parsing library
├── assets/                 # Game assets
│   ├── Roboto-Regular.ttf # Font file
│   ├── story.json         # Story content
│   └── *.png              # Image files
├── tests/                  # Test files (to be added)
├── SFML-3.0.2/            # SFML library
├── Minijuego.sln          # Visual Studio solution
└── Minijuego.vcxproj      # Visual Studio project file
```

## Building the Project

1. Open `Minijuego.sln` in Visual Studio
2. Ensure SFML 3.0.2 is properly configured
3. Build the solution (F7)
4. Run the game (F5)

## Requirements

- Visual Studio 2022 (or compatible)
- SFML 3.0.2
- C++17 or later

## Game Features

- Interactive narrative with branching paths
- Skill management system using linked lists
- Visual interface with SFML
- JSON-based story content
- Multiple endings based on player choices
- Dynamic image loading based on story nodes

## Image System

The game automatically loads images for each story node using the naming convention `assets/{nodeId}.png`. For example:
- Node "n1" displays `assets/n1.png`
- Node "n2" displays `assets/n2.png`

All 11 story nodes have corresponding images. See `IMAGE_MAPPING.md` for the complete mapping between nodes and images.

To add images for new nodes:
1. Create an image file named `{nodeId}.png`
2. Place it in the `assets/` folder
3. The game will automatically load it when that node is displayed
