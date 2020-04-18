#ifndef UNISPRITECONTROLLER_H
#define UNISPRITECONTROLLER_H

#include "../spritecontroller.h"
#include "../sprite.h"
#include "../../core/object.h"

namespace client {

class UnitSpriteController : public SpriteController {
  public:
    UnitSpriteController(const std::shared_ptr<core::Object>& object);

    const std::shared_ptr<Sprite>& getMoveSprite() const;

    void setMoveSprite(const std::shared_ptr<Sprite>& moveSprite);

  protected:

    void onUpdate(uint64_t timeDeltaMSec) override;

  private:
    std::shared_ptr<Sprite> moveSprite;

    std::shared_ptr<Sprite> standSprite;
};

}

#endif //UNISPRITECONTROLLER_H
