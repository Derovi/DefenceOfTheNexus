#ifndef SPRITEDESCRIPTION_H
#define SPRITEDESCRIPTION_H

#include <QString>

class SpriteDescription {
  public:
    SpriteDescription(const QString& resourceName, int width, int height);

    const QString& getResourceName() const;

    void setResourceName(const QString& resourceName);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

  private:
    QString resourceName;

    int width;

    int height;
};


#endif //SPRITEDESCRIPTION_H
