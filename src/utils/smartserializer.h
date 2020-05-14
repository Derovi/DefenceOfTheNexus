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

    static QJsonObject
    gamePartWorldSerializer(const std::shared_ptr<const core::GameWorld>& beforeChanges,
                            const std::shared_ptr<const core::GameWorld>& afterChanges,
                            const utils::KeyManager& keyManager);

    static QJsonObject
    objectPartSerializer(const std::shared_ptr<const core::Object>& beforeChanges,
                         const std::shared_ptr<const core::Object>& afterChanges,
                         const utils::KeyManager& keyManager);

    static QJsonObject
    resourcePartSerializer(const std::shared_ptr<const core::Attribute>& beforeChanges,
                           const std::shared_ptr<const core::Attribute>& afterChanges,
                           const utils::KeyManager& keyManager);

    static QJsonObject
    damagingPartSerializer(const std::shared_ptr<const core::Attribute>& beforeChanges,
                           const std::shared_ptr<const core::Attribute>& afterChanges,
                           const utils::KeyManager& keyManager);

    static QJsonObject
    damageablePartSerializer(const std::shared_ptr<const core::Attribute>& beforeChanges,
                             const std::shared_ptr<const core::Attribute>& afterChanges,
                             const utils::KeyManager& keyManager);

    static QJsonObject
    movingPartSerializer(const std::shared_ptr<const core::Attribute>& beforeChanges,
                         const std::shared_ptr<const core::Attribute>& afterChanges,
                         const utils::KeyManager& keyManager);

    static QJsonObject
    miningPartSerializer(const std::shared_ptr<const core::Attribute>& beforeChanges,
                         const std::shared_ptr<const core::Attribute>& afterChanges,
                         const utils::KeyManager& keyManager);

    static QJsonObject
    wallPartSerializer(const std::shared_ptr<const core::Attribute>& beforeChanges,
                       const std::shared_ptr<const core::Attribute>& afterChanges,
                       const utils::KeyManager& keyManager);

    static QJsonObject
    costPartSerializer(const std::shared_ptr<const core::Attribute>& beforeChanges,
                       const std::shared_ptr<const core::Attribute>& afterChanges,
                       const utils::KeyManager& keyManager);

    static QJsonObject
    builderPartSerializer(const std::shared_ptr<const core::Attribute>& beforeChanges,
                          const std::shared_ptr<const core::Attribute>& afterChanges,
                          const utils::KeyManager& keyManager);

    static void partGameWorldDeserializer(const std::shared_ptr<core::GameWorld>& gameWorld,
                                          const QJsonObject& changes,
                                          const utils::KeyManager& keyManager);

    static void
    partObjectDeserializer(const std::shared_ptr<core::Object>& object,
                           const QJsonObject& changes,
                           const utils::KeyManager& keyManager);

    static void resourcePartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                         const QJsonObject& changes,
                                         const utils::KeyManager& keyManager);

    static void damagingPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                         const QJsonObject& changes,
                                         const utils::KeyManager& keyManager);

    static void damageablePartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                           const QJsonObject& changes,
                                           const utils::KeyManager& keyManager);

    static void movingPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                       const QJsonObject& changes,
                                       const utils::KeyManager& keyManager);

    static void miningPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                       const QJsonObject& changes,
                                       const utils::KeyManager& keyManager);

    static void wallPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                     const QJsonObject& changes,
                                     const utils::KeyManager& keyManager);

    static void costPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                     const QJsonObject& changes,
                                     const utils::KeyManager& keyManager);

    static void builderPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                        const QJsonObject& changes,
                                        const utils::KeyManager& keyManager);

  private:

    bool prettyPrinting;
};

}  // namespace utils

#endif //SMARTSERIALIZER_H
