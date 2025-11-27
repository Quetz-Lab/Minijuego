# Image Mapping for Story Nodes

This document describes the mapping between story nodes and their corresponding images.

## Convention

All node images follow the naming convention: `assets/{nodeId}.png`

For example:
- Node "n1" → `assets/n1.png`
- Node "n2" → `assets/n2.png`
- etc.

## Image Mappings

| Node ID | Node Title | Original Image | Description |
|---------|-----------|----------------|-------------|
| n1 | La torre del mago | imagen1.png | The wizard's tower at the start |
| n2 | La tormenta viviente | AdiosTormenta.png | The lightning dragon storm |
| n3 | La biblioteca silenciosa | Biblioteca.png | The silent library with floating books |
| n4 | Pacto con el relámpago | CiruloDeLuz.png | Light circle spell with the dragon |
| n5 | El grimorio del maestro | LibroMalo.png | The forbidden grimoire |
| n6 | El tiempo se rompe | Biblioteca.png | Library when time breaks (reused) |
| n7 | Heraldo de la tormenta (Good Ending) | MagoChispa.png | Wizard with storm powers |
| n8 | El sello perfecto (Neutral Ending) | UnesPoder.png | Perfect seal containing the storm |
| n9 | El mago que quiso más | OjosBrillan.png | Eyes glowing with corruption |
| n10 | Señor de las ruinas (Bad Ending) | FinalObscuropng.png | Dark ending - lord of ruins |
| n11 | El sacrificio de la torre (Bittersweet Ending) | torreExplota.png | Tower exploding in sacrifice |

## Implementation

The game automatically loads images based on the current node's ID:

```cpp
// In Game.cpp Render() method
std::string imagePath = "assets/" + currentNode->id + ".png";
m_renderManager.DrawNodeImage(imagePath);
```

The RenderManager handles:
- Loading images from the assets folder
- Caching to avoid reloading the same image
- Scaling images proportionally to fit the display area (250x250 max)
- Graceful handling if an image is missing (logs warning, continues without crash)

## Adding New Images

To add images for new story nodes:

1. Name the image file as `{nodeId}.png` (e.g., `n12.png`)
2. Place it in the `assets/` folder
3. The game will automatically load it when that node is displayed

No code changes are required to add new node images.
