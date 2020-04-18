cmake_minimum_required(VERSION 3.7)
project(defenceofnexus)

set(CMAKE_CXX_STANDARD 17)

if (APPLE)
    set(CMAKE_PREFIX_PATH "/Users/Shared/Qt5*/5*/clang_64")
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
        resources/images.qrc
        resources/sprites.qrc
        src/core/object.cpp
        src/core/attributes/damageable.cpp
        src/core/attributes/damaging.cpp
        src/core/attributes/moving.cpp
        src/core/attributes/resource.cpp
        src/core/gameworld.cpp
        src/server/controllers/gameworldcontroller.cpp
        src/server/controllers/controller.cpp
        src/core/command.cpp
        src/server/commandexecutor.cpp
        src/server/worldgenerator.cpp
        src/server/engine.cpp
        src/bootstrap/bootstrap.cpp
        src/server/gameconfiguration.cpp
        src/server/server.cpp
        src/utils/serializer.cpp
        src/utils/factory.cpp
        src/server/strategies/strategy.cpp
        src/server/strategies/movestrategy.cpp
        src/server/performers/movingperformer.cpp
        src/server/performers/damagingperformer.cpp
        src/server/performers/damageableperformer.cpp
        src/server/objectsignature.cpp
        src/client/windowmanager.cpp
        src/client/windowmanager.h
        src/client/widget.cpp
        src/client/widget.h
        src/client/mainwindow.cpp
        src/client/mainwindow.h
        src/client/properties.h
        src/client/screen.cpp
        src/client/screen.h
        src/client/screens/menuscreen.cpp
        src/client/screens/menuscreen.h
        src/client/widgets/imagebutton.cpp
        src/client/widgets/imagebutton.h
        src/client/properties.cpp src/client/screens/gamescreen.cpp src/client/screens/gamescreen.h src/client/widgets/gamemap.cpp src/client/widgets/gamemap.h src/utils/colors.h src/client/graphicsobject.cpp src/client/graphicsobject.h src/client/sprite.cpp src/client/sprite.h src/client/spritecontroller.cpp src/client/spritecontroller.h src/client/spritecontrollers/unispritecontroller.cpp src/client/spritecontrollers/unispritecontroller.h src/client/objectgraphicsdescription.cpp src/client/objectgraphicsdescription.h)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
