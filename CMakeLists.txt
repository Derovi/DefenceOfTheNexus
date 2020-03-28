cmake_minimum_required(VERSION 3.7)
project(defenceofnexus)

set(CMAKE_CXX_STANDARD 17)

if (APPLE)
    set(CMAKE_PREFIX_PATH "/Users/Shared/Qt5.13/5.13.0/clang_64")
else (APPLE)
    # type here
endif (APPLE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Threads REQUIRED)

add_executable(defenceofnexus
        src/core/object.cpp
        src/core/damageable.cpp
        src/core/damaging.cpp
        src/core/moving.cpp
        src/core/resource.cpp
        src/core/resourcebundle.cpp
        src/core/unit.cpp
        src/core/building.cpp
        src/core/gameworld.cpp
        src/server/gameworldcontroller.cpp
        src/server/controller.cpp
        src/server/unitcontroller.cpp
        src/core/command.cpp
        src/server/commandexecutor.cpp
        src/server/worldgenerator.cpp
        src/server/engine.cpp
        src/server/bootstrap.cpp
        src/server/gameconfiguration.cpp
        src/server/server.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
