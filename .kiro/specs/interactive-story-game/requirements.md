# Requirements Document

## Introduction

Este documento define los requisitos para un juego interactivo de narrativa basado en texto con interfaz gráfica usando SFML. El juego presenta la historia de Eldrin, un mago aprendiz, y permite al jugador tomar decisiones que afectan el desarrollo y desenlace de la historia. El sistema incluye gestión de habilidades mágicas mediante una lista enlazada, carga dinámica de contenido desde JSON, y renderizado visual de la interfaz.

## Glossary

- **StorySystem**: El sistema completo que gestiona la carga, navegación y presentación de la historia interactiva
- **StoryNode**: Un punto específico en la narrativa que contiene texto, título y opciones de decisión
- **SkillList**: Estructura de datos de lista enlazada que almacena y gestiona las habilidades del jugador
- **RenderManager**: Componente responsable de dibujar elementos visuales en la ventana del juego
- **GameWindow**: La ventana principal de SFML donde se renderiza toda la interfaz gráfica
- **Player**: El usuario que interactúa con el juego tomando decisiones
- **JSONParser**: Componente que lee y deserializa el archivo story.json

## Requirements

### Requirement 1

**User Story:** Como jugador, quiero que el juego cargue la historia desde un archivo JSON, para que el contenido narrativo sea fácil de modificar sin recompilar el código.

#### Acceptance Criteria

1. WHEN the StorySystem initializes THEN the system SHALL load and parse the story.json file from disk
2. WHEN the JSON file contains valid story data THEN the system SHALL create StoryNode objects for each node in the file
3. IF the JSON file is missing or malformed THEN the system SHALL display an error message and terminate gracefully
4. WHEN parsing JSON content THEN the system SHALL correctly handle UTF-8 encoded Spanish characters including tildes and special symbols
5. WHEN the story is loaded THEN the system SHALL identify and store the starting node based on the startNodeId field

### Requirement 2

**User Story:** Como jugador, quiero navegar por la historia tomando decisiones, para que pueda experimentar diferentes caminos narrativos.

#### Acceptance Criteria

1. WHEN the game starts THEN the StorySystem SHALL display the starting node's title and text
2. WHEN a StoryNode has options THEN the system SHALL display all available choices with their corresponding labels
3. WHEN the Player selects an option THEN the system SHALL transition to the StoryNode specified by that option's nextNodeId
4. WHEN a StoryNode has the ending flag set to true THEN the system SHALL display the ending text and prevent further navigation
5. WHEN transitioning between nodes THEN the system SHALL update the display within 100 milliseconds to maintain responsiveness

### Requirement 3

**User Story:** Como jugador, quiero ver la historia y las opciones en una interfaz gráfica clara, para que la experiencia sea visualmente agradable y fácil de leer.

#### Acceptance Criteria

1. WHEN the GameWindow opens THEN the system SHALL create a window of at least 800x600 pixels with the title "La Torre del Mago"
2. WHEN displaying story text THEN the RenderManager SHALL render the text using the Roboto-Regular.ttf font at a readable size
3. WHEN displaying options THEN the system SHALL show each option as a clickable button or text element with visual feedback
4. WHEN the Player hovers over an option THEN the system SHALL provide visual feedback by changing color or highlighting
5. WHEN rendering text THEN the system SHALL ensure proper line wrapping to fit within the window boundaries

### Requirement 4

**User Story:** Como jugador, quiero gestionar mis habilidades mágicas durante el juego, para que pueda ver qué poderes tengo disponibles.

#### Acceptance Criteria

1. WHEN the game initializes THEN the SkillList SHALL be empty or contain default starting skills
2. WHEN a skill is added to the SkillList THEN the system SHALL append it to the end of the list
3. WHEN displaying skills THEN the system SHALL show all skills in the SkillList with their index positions
4. WHEN a skill is removed from the SkillList THEN the system SHALL maintain the integrity of the linked list structure
5. WHEN the SkillList is modified THEN the system SHALL update the visual display to reflect the current state

### Requirement 5

**User Story:** Como jugador, quiero que el juego responda a mis interacciones con el mouse y teclado, para que pueda controlar el juego de manera intuitiva.

#### Acceptance Criteria

1. WHEN the Player clicks on an option button THEN the system SHALL register the selection and navigate to the corresponding node
2. WHEN the Player presses the Escape key THEN the system SHALL close the game window gracefully
3. WHEN the Player clicks the window close button THEN the system SHALL terminate the application without errors
4. WHEN processing input events THEN the system SHALL handle all events in the SFML event queue each frame
5. WHEN multiple input events occur THEN the system SHALL process them in the order they were received

### Requirement 6

**User Story:** Como jugador, quiero ver imágenes relacionadas con la historia, para que la experiencia sea más inmersiva.

#### Acceptance Criteria

1. WHEN a StoryNode is displayed THEN the system SHALL attempt to load an associated image file if one exists
2. WHEN an image file is found THEN the RenderManager SHALL display it in a designated area of the GameWindow
3. IF an image file is missing THEN the system SHALL continue displaying the story without crashing
4. WHEN displaying images THEN the system SHALL scale them appropriately to fit the designated display area
5. WHEN transitioning between nodes THEN the system SHALL update the displayed image to match the new node

### Requirement 7

**User Story:** Como desarrollador, quiero que el código gestione la memoria correctamente, para evitar memory leaks y crashes.

#### Acceptance Criteria

1. WHEN the SkillList is destroyed THEN the system SHALL deallocate all Node objects in the linked list
2. WHEN SFML resources are loaded THEN the system SHALL properly manage texture and font lifetimes
3. WHEN the game terminates THEN the system SHALL release all allocated memory before exiting
4. WHEN exceptions occur THEN the system SHALL catch them and clean up resources before terminating
5. WHEN nodes are removed from the SkillList THEN the system SHALL immediately delete the corresponding Node object

### Requirement 8

**User Story:** Como desarrollador, quiero separar las responsabilidades del código en componentes claros, para que el sistema sea mantenible y extensible.

#### Acceptance Criteria

1. WHEN implementing the story system THEN the code SHALL separate story logic from rendering logic
2. WHEN implementing data structures THEN the SkillList SHALL be independent of the story and rendering systems
3. WHEN implementing rendering THEN the RenderManager SHALL not contain game logic or story navigation code
4. WHEN implementing the main game loop THEN it SHALL coordinate between story, input, and rendering systems without implementing their internal logic
5. WHEN adding new features THEN the system SHALL allow modifications to one component without requiring changes to unrelated components
