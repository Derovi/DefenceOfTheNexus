#ifndef UNI1SPRITECONTROLLER_H
#define UNI1SPRITECONTROLLER_H

#include "../spritecontroller.h"
#include "../sprite.h"
#include "../../core/object.h"

namespace client {

class Uni1SpriteController : public SpriteController {
  public:
    Uni1SpriteController(const std::shared_ptr<core::Object>& object);

  protected:

    void onUpdate(uint64_t timeDeltaMSec) override;

  private:
    std::shared_ptr<Sprite> moveSprite;
};

}

#endif //UNI1SPRITECONTROLLER_H
