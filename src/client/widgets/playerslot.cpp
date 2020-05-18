
#include "playerslot.h"

client::PlayerSlot::PlayerSlot(QPoint position, int height, int width, bool taken, int slotId):
        ImageButton(position, height, width) {
    this->taken = taken;
    this->slotId = slotId;
}

bool client::PlayerSlot::isTaken() const {
    return taken;
}

void client::PlayerSlot::setTaken(bool taken) {
    PlayerSlot::taken = taken;
}

int client::PlayerSlot::getSlotId() const {
    return slotId;
}

void client::PlayerSlot::setSlotId(int slotId) {
    PlayerSlot::slotId = slotId;
}

void client::PlayerSlot::paint(QPainter& painter) {
    if (taken && !hoverImage.isNull()) {
        painter.drawImage(boundsRect(), hoverImage);
    } else {
        painter.drawImage(boundsRect(), image);
    }
    if (textChildren != nullptr) {
        textChildren->setPosition(getPosition() + QPoint(
                getWidth() / 2.0 - textChildren->getTextWidth() / 2.0,
                getHeght() / 2.0 + textChildren->getTextHeight() / 2.0
        ));
        textChildren->draw();
    }
}

int client::PlayerSlot::getPlayerId() const {
    return playerId;
}
