#ifndef SMARTSERIALIZER_H
#define SMARTSERIALIZER_H

#include <QString>
#include <QJsonObject>
#include <QtCore>
#include <QtGlobal>
#include <QJsonDocument>

#include "../core/gameworld.h"
#include "keymanager.h"

namespace utils {

class SmartSerializer {
  public:
    explicit SmartSerializer(bool prettyPrinting = true);

    QString getChanges(const std::shared_ptr<const core::GameWorld>& beforeChanges,
                       const std::shared_ptr<const core::GameWorld>& afterChanges);

    void applyChanges(const std::shared_ptr<core::GameWorld>& gameWorld, QString changes);

    QJsonObject partGameWorldSerializer(const std::shared_ptr<const core::GameWorld>& beforeChanges,
                                        const std::shared_ptr<const core::GameWorld>& afterChanges,
                                        const utils::KeyManager& keyManager);

    void partGameWorldDeserializer(const std::shared_ptr<core::GameWorld>& gameWorld,
                                   QJsonObject changes,
                                   const utils::KeyManager& keyManager);

    QJsonObject partObjectSerializer(const std::shared_ptr<const core::Object>& beforeChanges,
                                     const std::shared_ptr<const core::Object>& afterChanges,
                                     const utils::KeyManager& keyManager);

    void partObjectDerializer(const std::shared_ptr<core::Object>& object, QJsonObject changes,
                              const utils::KeyManager& keyManager);


  private:

    bool prettyPrinting;
};

}  // namespace utils

#endif //SMARTSERIALIZER_H
