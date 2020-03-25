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
        src/core/gameworld.h
        src/server/gameworldcontroller.cpp
        src/server/gameworldcontroller.h
        src/server/controller.h
        src/server/controller.cpp
        src/server/unitcontroller.cpp
        src/server/unitcontroller.h
        src/server/movingperformer.h
        src/server/test.cpp src/core/command.cpp src/core/command.h src/server/commandexecutor.cpp src/server/commandexecutor.h src/server/worldgenerator.cpp src/server/worldgenerator.h src/server/engine.cpp src/server/engine.h src/server/bootstrap.cpp src/server/gameconfiguration.cpp src/server/gameconfiguration.h src/server/server.cpp src/server/server.h)

target_link_libraries(defenceofnexus Qt5::Widgets)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)