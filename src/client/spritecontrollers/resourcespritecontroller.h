#ifndef RESOURCESPRITECONTROLLER_H
#define RESOURCESPRITECONTROLLER_H

#include <memory>

#include "../../core/object.h"
#include "../spritecontroller.h"
#include "../sprite.h"

namespace client {

class ResourceSpriteController : public SpriteController {
  public:
    explicit ResourceSpriteController(const std::shared_ptr<core::Object>& object);

    QString getName() override;

    inline static const QString name = "resource";

  protected:
    void onUpdate(uint64_t timeDeltaMSec) override;

  private:
    std::shared_ptr<Sprite> miningSprite;

    std::shared_ptr<Sprite> defaultSprite;
};

}  // namespace client

#endif  // RESOURCESPRITECONTROLLER_H
