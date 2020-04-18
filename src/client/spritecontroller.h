#ifndef SPRITECONTROLLER_H
#define SPRITECONTROLLER_H

#include <memory>

#include <QSet>

#include "objectgraphicsdescription.h"
#include "../core/object.h"
#include "sprite.h"

namespace client {

class SpriteController {
  public:
    explicit SpriteController(const std::shared_ptr<core::Object>& object);

    virtual ~SpriteController() = default;

    const std::shared_ptr<core::Object>& getObject() const;

    void update(QPainter& painter, const QRect& target, uint64_t timeDeltaMSec);

  protected:
    virtual void onUpdate(uint64_t timeDeltaMSec) = 0;

    void addSprite(const std::shared_ptr<Sprite>& sprite);

    void removeSprite(const std::shared_ptr<Sprite>& sprite);

  private:
    std::shared_ptr<core::Object> object;

    QVector<std::shared_ptr<Sprite>> sprites;
};

}

#endif //SPRITECONTROLLER_H
