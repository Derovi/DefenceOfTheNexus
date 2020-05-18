cmake_minimum_required(VERSION 3.7)
project(defenceofnexus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address -g")

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
find_package(Qt5Network REQUIRED)
find_package(Threads REQUIRED)

set(SOURCES src/bootstrap/bootstrap.cpp
        src/core/object.cpp
        src/core/gameworld.cpp
        src/core/command.cpp
        src/core/attributes/damageable.cpp
        src/core/attributes/damaging.cpp
        src/core/attributes/moving.cpp
        src/core/attributes/resource.cpp
        src/core/attributes/wall.cpp
        src/core/attributes/cost.cpp
        src/core/attributes/builder.cpp
        src/core/attributes/mining.cpp
        src/core/attributes/bullet.cpp
        src/server/controllers/gameworldcontroller.cpp
        src/server/controllers/controller.cpp
        src/server/commandexecutor.cpp
        src/server/worldgenerator.cpp
        src/server/engine.cpp
        src/server/gameconfiguration.cpp
        src/server/network/server.cpp
        src/server/objectsignature.cpp
        src/server/strategies/strategy.cpp
        src/server/strategies/movestrategy.cpp
        src/server/strategies/pathstrategy.cpp
        src/server/strategies/attackstrategy.cpp
        src/server/strategies/minestrategy.cpp
        src/server/strategies/bulletstrategy.cpp
        src/server/strategies/towerstrategy.cpp
        src/server/performers/movingperformer.cpp
        src/server/performers/damagingperformer.cpp
        src/server/performers/damageableperformer.cpp
        src/server/performers/miningperformer.cpp
        src/client/windowmanager.cpp
        src/client/widget.cpp
        src/client/app.cpp
        src/client/screen.cpp
        src/client/screens/menuscreen.cpp
        src/client/widgets/imagebutton.cpp
        src/client/properties.cpp
        src/client/screens/gamescreen.cpp
        src/client/screens/connectionscreen.cpp
        src/client/widgets/gamemap.cpp
        src/client/graphicsobject.cpp
        src/client/sprite.cpp
        src/client/spritecontroller.cpp
        src/client/spritecontrollers/unitspritecontroller.cpp
        src/client/objectgraphicsdescription.cpp
        src/client/spritedescription.cpp
        src/client/spritecontrollers/resourcespritecontroller.cpp
        src/client/spritecontrollers/defaultspritecontroller.cpp
        src/client/screens/pausescreen.cpp
        src/client/screens/optionsscreen.cpp
        src/client/widgets/textview.cpp
        src/client/widgets/chooser.cpp
        src/client/widgets/gameinterface.cpp
        src/client/widgets/uniticon.cpp
        src/client/widgets/healthbar.cpp
        src/client/widgets/buildslot.cpp
        src/client/mapinput.cpp
        src/utils/serializer.cpp
        src/utils/keymanager.cpp
        src/utils/factory.cpp
        src/utils/smartserializer.cpp
        src/utils/lang.cpp
        src/client/network/multiplayerinterface.cpp
        src/utils/network.cpp
        src/server/network/connectedplayer.cpp
        src/core/event.cpp src/server/aiplayer.cpp
        src/server/ai/simpleai.cpp)


qt5_add_big_resources(SOURCES resources/sprites.qrc
        resources/lang.qrc
        resources/data.qrc
        resources/images.qrc
        resources/other.qrc
        resources/interface.qrc)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Network)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
