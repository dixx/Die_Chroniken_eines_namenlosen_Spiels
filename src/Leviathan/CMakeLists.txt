cmake_minimum_required(VERSION 3.31.0)
project(leviathan DESCRIPTION "The Leviathan game engine." VERSION 0.5.1 LANGUAGES CXX)
include_directories("${IRRLICHT_INCLUDE_DIRS}" "${YAML_INCLUDE_DIRS}" "${PUBLIC_INTERFACES}")
add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME}
  PRIVATE
    characters/hero.cpp
    characters/heroes.cpp
    core/Configuration.cpp
    core/GameStateManager.cpp
    core/Logger.cpp
    core/Randomizer.cpp
    core/TimeControl.cpp
    core/Timer.cpp
    gui/Menu.cpp
    gui/MenuControl.cpp
    gui/MousePointerControl.cpp
    input/ActionMapping.cpp
    input/Actions.cpp
    input/EventReceiver.cpp
    input/EventToActionConverter.cpp
    input/GUIEventActions.cpp
    input/Input.cpp
    input/KeyboardEventActions.cpp
    input/MouseEventActions.cpp
    video/Camera.cpp
    video/GraphicEngine.cpp
    video/MeshHelper.cpp
    video/Textures.cpp
    video/Vector3D.cpp
    video/Vector3DCompatible.cpp
    world/Character.cpp
    world/Collider.cpp
    world/Ground.cpp
    world/GroundTile.cpp
    world/NodeManager.cpp
    LeviathanDevice.cpp
    leviathan.cpp
    ${PUBLIC_HEADER_FILES}
)
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PUBLIC_INTERFACES}
  PUBLIC
    $<BUILD_INTERFACE:${PUBLIC_INTERFACES}>
)
target_link_libraries(${PROJECT_NAME}
  "${IRRLICHT_LIBRARY}"
  "${YAML_LIBRARY}"
)
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    LIBRARY_OUTPUT_NAME ${PROJECT_NAME}
    PREFIX ""
)
set(LEVIATHAN_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${PUBLIC_INTERFACES} PARENT_SCOPE)
cotire(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
install(FILES "${IRRLICHT_BINARY_LIBRARY}" DESTINATION .)
