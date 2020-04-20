#ifndef SPRITEDESCRIPTION_H
#define SPRITEDESCRIPTION_H

#include <QString>

class SpriteDescription {
  public:
    SpriteDescription() = default;

    SpriteDescription(const QString& resourceName, int rows, int columns);

    const QString& getResourceName() const;

    void setResourceName(const QString& resourceName);

    int getRows() const;

    void setRows(int rows);

    int getColumns() const;

    void setColumns(int columns);

  private:
    QString resourceName;

    int rows;

    int columns;
};


#endif //SPRITEDESCRIPTION_H
