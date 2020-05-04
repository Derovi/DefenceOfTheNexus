#include "gameinterface.h"

#include <utility>

client::GameInterface::GameInterface(QPoint position,
                                     std::shared_ptr<core::GameWorld> gameWorld,
                                     int selectedUnitId):
        Widget(position), gameWorld(std::move(gameWorld)), selectedUnitId(selectedUnitId) {

}
