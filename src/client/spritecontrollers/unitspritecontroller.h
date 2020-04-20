#ifndef UNITSPRITECONTROLLER_H
#define UNITSPRITECONTROLLER_H

#include "../spritecontroller.h"
#include "../sprite.h"
#include "../../core/object.h"

namespace client {

class UnitSpriteController : public SpriteController {
  public:
    UnitSpriteController(const std::shared_ptr<core::Object>& object);

    const std::shared_ptr<Sprite>& getMoveSprite() const;

    void setMoveSprite(const std::shared_ptr<Sprite>& moveSprite);

    QString getName() override;

    static QString name;

  protected:
    void onUpdate(uint64_t timeDeltaMSec) override;

  private:
    std::shared_ptr<Sprite> moveSprite;

    std::shared_ptr<Sprite> standSprite;
};

}

#endif //UNITSPRITECONTROLLER_H
