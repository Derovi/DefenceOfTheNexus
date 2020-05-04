#ifndef DEFAULTPRITECONTROLLER_H
#define DEFAULTPRITECONTROLLER_H

#include "../spritecontroller.h"
#include "../sprite.h"
#include "../../core/object.h"

namespace client {

class DefaultSpriteController : public SpriteController {
  public:
    explicit DefaultSpriteController(const std::shared_ptr<core::Object>& object);

    const std::shared_ptr<Sprite>& getDefaultSprite() const;

    void setDefaultSprite(const std::shared_ptr<Sprite>& sprite);

    QString getName() override;

    static QString name;

  protected:
    void onUpdate(uint64_t timeDeltaMSec) override;

  private:
    std::shared_ptr<Sprite> defaultSprite;
};

}

#endif //DEFAULTSPRITECONTROLLER_H
