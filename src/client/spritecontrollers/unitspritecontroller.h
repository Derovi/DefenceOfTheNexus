#ifndef UNITSPRITECONTROLLER_H
#define UNITSPRITECONTROLLER_H

#include "../spritecontroller.h"
#include "../sprite.h"
#include "../../core/object.h"

namespace client {

class UnitSpriteController : public SpriteController {
  public:
    explicit UnitSpriteController(const std::shared_ptr<core::Object>& object);

    const std::shared_ptr<Sprite>& getRunSprite() const;

    void setRunSprite(const std::shared_ptr<Sprite>& runSprite);

    const std::shared_ptr<Sprite>& getIdleSprite() const;

    void setIdleSprite(const std::shared_ptr<Sprite>& idleSprite);

    const std::shared_ptr<Sprite>& getAttackSprite() const;

    void setAttackSprite(const std::shared_ptr<Sprite>& attackSprite);

    QString getName() override;

    static QString name;

  protected:
    void onUpdate(uint64_t timeDeltaMSec) override;

  private:
    std::shared_ptr<Sprite> runSprite;

    std::shared_ptr<Sprite> idleSprite;

    std::shared_ptr<Sprite> attackSprite;
};

}

#endif //UNITSPRITECONTROLLER_H
