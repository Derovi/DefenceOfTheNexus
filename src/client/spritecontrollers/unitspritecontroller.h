#ifndef UNITSPRITECONTROLLER_H
#define UNITSPRITECONTROLLER_H

#include "../spritecontroller.h"
#include "../sprite.h"
#include "../../core/object.h"

namespace client {

class UnitSpriteController : public SpriteController {
  public:
    explicit UnitSpriteController(const std::shared_ptr<core::Object>& object);

    std::shared_ptr<Sprite> getMoveSprite() const;

    std::shared_ptr<Sprite> getStandSprite() const;

    std::shared_ptr<Sprite> getAttackSprite() const;

    void setMoveSprite(const std::shared_ptr<Sprite>& moveSprite);

    void setStandSprite(const std::shared_ptr<Sprite>& standSprite);

    void setAttackSprite(const std::shared_ptr<Sprite>& attackSprite);

    QString getName() override;

    static QString name;

  protected:
    void onUpdate(uint64_t timeDeltaMSec) override;

  private:
    std::shared_ptr<Sprite> moveSprite;

    std::shared_ptr<Sprite> standSprite;

    std::shared_ptr<Sprite> attackSprite;
};

}

#endif //UNITSPRITECONTROLLER_H
