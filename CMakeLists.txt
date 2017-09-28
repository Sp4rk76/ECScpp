# CMake: version
cmake_minimum_required(VERSION 3.6.3)

# Project name (target)
project(ECScpp)

# CMake: output directories
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Standard modules directories
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

# Project directories
include_directories(src/)
include_directories(include/)

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# SDL2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# SDL2_ttf
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# GoogleTest & GoogleMock (Unit Testing)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

# Files to compile into an executable
set(SOURCE_FILES
        include/Scene.h
        include/utils/KeyPressSurfaces.h
        include/Game.h
        include/utils/ShapeBuilder.h
        include/utils/ShapeType.h
        include/display/Screen.h
        include/IGame.h
        include/systems/Updater.h
        include/components/Components.h
        include/systems/Renderer.h
        include/systems/SystemBase.h
        include/systems/SpriteRenderer.h
        include/components/Sprite.h
        include/systems/Physics2D.h
        include/texturing/TextureManager.h
        include/Timer.h
        include/EntityManagerOld.h
        include/components/Rigidbody2D.h
        include/systems/Collision.h
        include/components/Direction.h
        include/components/Vector2D.h
        include/components/BoxCollider2D.h
        include/components/Object2D.h
        include/components/Transform.h
        include/components/Collider2D.h
        include/components/Size.h
        include/components/CircleCollider2D.h
        include/utils/ComponentStoreArray.h
        include/Entity.h
        include/utils/NonAssignable.h
        include/utils/ComponentStore.h
        src/main.cpp
        src/Scene.cpp
        src/display/Screen.cpp
        src/Game.cpp
        src/systems/SystemBase.cpp
        src/systems/Collision.cpp
        src/Timer.cpp
        src/EntityManagerOld.cpp
        src/texturing/TextureManager.cpp
        src/systems/Updater.cpp
        src/systems/Physics2D.cpp
        src/systems/Renderer.cpp
        src/systems/SpriteRenderer.cpp
        examples/ComponentStoreExample.h
        examples/ExampleBase.h
        examples/ExampleBase.cpp
        examples/ComponentStoreExample.cpp
        examples/ComponentStoreArrayExemple.h
        examples/ComponentStoreArrayExample.cpp include/DebugNameComponentManager.h include/EntityManager.h include/ComponentManager.h include/Vector3.h include/InstanceData.h)

# Executable
add_executable(ECScpp ${SOURCE_FILES})

# Link libraries
target_link_libraries(ECScpp ${SDL2_LIBRARIES})
target_link_libraries(ECScpp ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(ECScpp ${SDL2_TTF_LIBRARIES})
target_link_libraries(ECScpp gtest gtest_main)

