#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QString>
#include <QJsonObject>

namespace client::properties {

extern QString baseLang;

extern QString lang;

extern bool fullscreen;

extern int width;

extern int height;

extern int frameRate;

QJsonObject serialize();

void load(QJsonObject json);

}  // namespace properies

#endif //PROPERTIES_H
