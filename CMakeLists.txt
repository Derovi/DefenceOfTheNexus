cmake_minimum_required(VERSION 3.7)
project(defeceofnexus)

set(CMAKE_CXX_STANDARD 14)

if (APPLE)
 set(CMAKE_PREFIX_PATH "/Users/Shared/Qt5.13/5.13.0/clang_64")
else (APPLE)
 # type here
endif (APPLE)

find_package(Qt5Widgets REQUIRED)

add_executable(defenceofnexus ./src/main.cpp src/core/object.cpp src/core/object.h src/core/damageable.h src/core/damageable.cpp src/core/damaging.cpp src/core/damaging.h src/core/moving.cpp src/core/moving.h src/core/resource.cpp src/core/resource.h src/core/resourcebundle.cpp src/core/resourcebundle.h src/core/unit.cpp src/core/unit.h src/core/building.cpp src/core/building.h)

target_link_libraries(defenceofnexus Qt5::Widgets)
