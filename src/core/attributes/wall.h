#ifndef WALL_H
#define WALL_H

#include "../attribute.h"

namespace core {

enum class WallType {
    kWall,
    kColumn,
    kGate
};

class Wall : public Attribute {
  public:
    Wall() = delete;

    explicit Wall(WallType type);

    WallType getType() const;

    void setType(WallType newType);

    static QString attributeName;

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

    bool operator==(core::Wall wall);

  private:
    WallType type;
};

}  // namespace core

#endif //WALL_H
