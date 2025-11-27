# Implementation Plan

- [x] 1. Limpiar y organizar estructura del proyecto




  - Consolidar archivos duplicados (decidir entre raíz vs Minijuego/)
  - Crear estructura de carpetas src/, assets/, tests/
  - Mover archivos existentes a las ubicaciones correctas
  - Actualizar rutas en archivos de proyecto (.vcxproj)
  - _Requirements: 8.1, 8.2, 8.3, 8.4_

- [x] 2. Implementar estructuras de datos base





- [x] 2.1 Mejorar SkillList existente


  - Agregar método GetSkillAt(int index) para acceso por índice
  - Agregar validación de índices en todos los métodos
  - Mejorar mensajes de error para debugging
  - _Requirements: 4.2, 4.3, 4.4_

- [x] 2.2 Escribir property test para adición de skills


  - **Property 8: Skill addition increases count**
  - **Validates: Requirements 4.2**

- [x] 2.3 Escribir property test para integridad de lista


  - **Property 10: List integrity after removal**
  - **Validates: Requirements 4.4**

- [x] 2.4 Escribir property test para limpieza de memoria

  - **Property 14: SkillList memory cleanup**
  - **Validates: Requirements 7.1**

- [x] 2.5 Crear clases StoryNode y StoryOption


  - Implementar struct StoryOption con id, text, nextNodeId
  - Implementar clase StoryNode con todos los campos del JSON
  - Agregar método HasOptions() y GetOption()
  - _Requirements: 2.2, 2.3, 2.4_

- [x] 3. Implementar StoryManager para carga y navegación




- [x] 3.1 Implementar carga de JSON


  - Crear método LoadFromFile() usando nlohmann/json
  - Implementar ParseJSON() para convertir JSON a StoryNodes
  - Agregar validación de campos requeridos
  - Implementar manejo de errores (archivo no encontrado, JSON inválido)
  - _Requirements: 1.1, 1.2, 1.3, 1.5_

- [x] 3.2 Implementar navegación entre nodos

  - Crear método Start() para ir al nodo inicial
  - Implementar NavigateToNode() con validación
  - Implementar SelectOption() para navegar por opciones
  - Agregar GetCurrentNode() y IsAtEnding()
  - _Requirements: 2.1, 2.3, 2.4_

- [x] 3.3 Escribir property test para conteo de nodos


  - **Property 1: Node count consistency**
  - **Validates: Requirements 1.2**

- [x] 3.4 Escribir property test para UTF-8

  - **Property 2: UTF-8 round trip**
  - **Validates: Requirements 1.4**

- [x] 3.5 Escribir property test para nodo inicial

  - **Property 3: Start node identification**
  - **Validates: Requirements 1.5**

- [x] 3.6 Escribir property test para navegación

  - **Property 5: Navigation correctness**
  - **Validates: Requirements 2.3**

- [x] 3.7 Escribir property test para nodos finales

  - **Property 6: Ending node finality**
  - **Validates: Requirements 2.4**

- [x] 4. Corregir encoding del archivo story.json




  - Abrir story.json y corregir caracteres mal codificados (� → tildes correctas)
  - Guardar con encoding UTF-8
  - Verificar que todos los caracteres especiales se muestran correctamente
  - _Requirements: 1.4_

- [x] 5. Implementar InputManager




- [x] 5.1 Crear clase InputManager


  - Implementar ProcessEvents() para manejar eventos SFML
  - Agregar métodos ShouldClose(), WasLeftClicked(), WasEscapePressed()
  - Implementar GetMousePosition()
  - Agregar ResetFrameState() para limpiar estado del frame
  - _Requirements: 5.1, 5.2, 5.3, 5.4, 5.5_

- [x] 5.2 Escribir property test para procesamiento de eventos


  - **Property 11: Event queue exhaustion**
  - **Validates: Requirements 5.4**

- [x] 5.3 Escribir property test para orden de eventos


  - **Property 12: Event processing order**
  - **Validates: Requirements 5.5**

- [x] 6. Implementar RenderManager




- [x] 6.1 Crear clase RenderManager base


  - Implementar constructor que recibe sf::RenderWindow
  - Crear método Initialize() para cargar fuente
  - Implementar Clear() y Display()
  - Agregar manejo de errores si la fuente no se carga
  - _Requirements: 3.1, 3.2_

- [x] 6.2 Implementar renderizado de texto


  - Crear método DrawText() privado con posición, tamaño y color
  - Implementar WrapText() para dividir texto en líneas
  - Agregar DrawStoryNode() que renderiza título, texto y opciones
  - Calcular y almacenar bounds de opciones para detección de hover
  - _Requirements: 3.2, 3.3, 3.5_

- [x] 6.3 Implementar detección de hover


  - Crear método GetHoveredOption() que recibe posición del mouse
  - Comparar posición con bounds almacenados
  - Retornar índice de opción bajo el mouse o -1
  - _Requirements: 3.4, 5.1_

- [x] 6.4 Implementar renderizado de imágenes


  - Crear método DrawNodeImage() que carga y dibuja imagen
  - Implementar escalado proporcional para ajustar a área designada
  - Agregar manejo de errores si imagen no existe
  - Cachear textura actual para evitar recargas
  - _Requirements: 6.1, 6.2, 6.3, 6.4_

- [x] 6.5 Implementar renderizado de SkillList


  - Crear método DrawSkillList() que recibe const SkillList&
  - Iterar por la lista y dibujar cada skill con su índice
  - Posicionar en área lateral de la ventana
  - _Requirements: 4.3, 4.5_

- [x] 6.6 Escribir property test para wrapping de texto


  - **Property 7: Text wrapping bounds**
  - **Validates: Requirements 3.5**

- [x] 6.7 Escribir property test para escalado de imágenes

  - **Property 13: Image scaling bounds**
  - **Validates: Requirements 6.4**

- [x] 7. Implementar clase Game principal




- [x] 7.1 Crear estructura básica de Game


  - Crear constructor que inicializa ventana SFML
  - Instanciar StoryManager, RenderManager, InputManager, SkillList
  - Implementar método Initialize() que carga historia y recursos
  - _Requirements: 1.1, 3.1, 4.1_

- [x] 7.2 Implementar game loop


  - Crear método Run() con loop principal
  - Implementar HandleInput() para procesar eventos
  - Crear Update() para lógica de juego
  - Implementar Render() que coordina el renderizado
  - Agregar control de framerate (60 FPS)
  - _Requirements: 2.5, 5.1, 5.2, 5.3_

- [x] 7.3 Conectar input con navegación


  - En HandleInput(), detectar clicks en opciones
  - Obtener índice de opción con GetHoveredOption()
  - Llamar a StoryManager.SelectOption() con la opción clickeada
  - Manejar tecla Escape para cerrar juego
  - _Requirements: 5.1, 5.2_

- [x] 7.4 Implementar lógica de actualización


  - En Update(), verificar si se llegó a un final
  - Actualizar estado de habilidades si es necesario
  - Preparar datos para renderizado
  - _Requirements: 2.4_

- [x] 7.5 Coordinar renderizado completo


  - En Render(), llamar a Clear()
  - Dibujar imagen del nodo actual si existe
  - Dibujar nodo de historia con DrawStoryNode()
  - Dibujar lista de habilidades con DrawSkillList()
  - Llamar a Display()
  - _Requirements: 3.3, 4.5, 6.5_

- [x] 8. Actualizar main.cpp





  - Reemplazar código de prueba actual con instancia de Game
  - Llamar a game.Initialize() y verificar éxito
  - Llamar a game.Run() para iniciar el loop
  - Mantener try-catch para manejo de excepciones
  - Corregir typo en mensaje de error ("Errror eneljuego")
  - _Requirements: 7.3, 7.4_

- [x] 9. Agregar habilidades iniciales al juego





  - En Game::Initialize(), agregar 3-5 habilidades temáticas a la historia
  - Usar nombres relacionados con la narrativa del mago
  - Ejemplos: "Círculo de Luz", "Sello de Runas", "Absorción de Tormenta"
  - _Requirements: 4.1_

- [x] 10. Mapear imágenes a nodos de la historia





  - Crear convención de nombres: nodeId.png (ej: n1.png, n2.png)
  - Renombrar imágenes existentes según los nodos correspondientes
  - Actualizar RenderManager para cargar imagen basada en node.id
  - Verificar que todas las imágenes importantes tienen correspondencia
  - _Requirements: 6.1, 6.5_

- [x] 11. Checkpoint - Verificar que el juego funciona end-to-end





  - Compilar el proyecto sin errores
  - Ejecutar el juego y verificar que carga la historia
  - Navegar por al menos 3 nodos diferentes
  - Verificar que las imágenes se muestran correctamente
  - Verificar que las habilidades se muestran en pantalla
  - Llegar a un final y verificar que no se puede continuar
  - _Ensure all tests pass, ask the user if questions arise._

- [x] 12. Escribir unit tests para componentes individuales





  - Tests para SkillList (vacía, agregar, eliminar, reemplazar, clear)
  - Tests para StoryManager (cargar JSON válido/inválido, navegación)
  - Tests para RenderManager (inicialización, hover detection)
  - Tests para InputManager (procesamiento de eventos básicos)
  - _Requirements: 1.3, 2.3, 4.2, 4.4, 5.1_

- [x] 13. Escribir property tests restantes








- [x] 13.1 Property test para completitud de opciones


  - **Property 4: Option display completeness**
  - **Validates: Requirements 2.2**

- [x] 13.2 Property test para completitud de skills


  - **Property 9: Skill display completeness**
  - **Validates: Requirements 4.3**

- [x] 13.3 Property test para seguridad de excepciones


  - **Property 15: Exception safety**
  - **Validates: Requirements 7.4**

- [x] 13.4 Property test para eliminación inmediata de nodos


  - **Property 16: Immediate node deletion**
  - **Validates: Requirements 7.5**

- [x] 14. Pulir interfaz visual









  - Ajustar tamaños de fuente para mejor legibilidad
  - Agregar colores para diferenciar título, texto y opciones
  - Implementar highlight visual al hacer hover sobre opciones
  - Ajustar posicionamiento de elementos para mejor composición
  - Agregar fondo o color de ventana apropiado
  - _Requirements: 3.2, 3.3, 3.4_

- [x] 15. Optimizar y limpiar código





  - Revisar y eliminar includes innecesarios
  - Agregar comentarios en código complejo
  - Verificar que no hay warnings del compilador
  - Asegurar consistencia en estilo de código
  - Verificar que todos los recursos se liberan correctamente
  - _Requirements: 7.1, 7.2, 7.3, 8.1, 8.2, 8.3_

- [x] 16. Checkpoint final - Asegurar que todo funciona





  - Ejecutar todos los tests y verificar que pasan
  - Hacer playthrough completo del juego
  - Probar todos los caminos de la historia
  - Verificar que no hay memory leaks (usar herramienta de análisis)
  - Confirmar que el juego se cierra correctamente
  - _Ensure all tests pass, ask the user if questions arise._
