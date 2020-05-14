#include "smartserializer.h"
#include "factory.h"

utils::SmartSerializer::SmartSerializer(bool prettyPrinting) {
    utils::SmartSerializer::prettyPrinting = prettyPrinting;
}

QJsonObject utils::SmartSerializer::objectPartSerializer(
        const std::shared_ptr<core::Object>& beforeChanges,
        const std::shared_ptr<core::Object>& afterChanges,
        const utils::KeyManager& keyManager) {
    QJsonObject result;

}

void
utils::SmartSerializer::resourcePartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                 const QJsonObject& changes,
                                                 const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("resource");
    std::shared_ptr<core::Attribute> ptr = deserializer(changes).value();
    *dynamic_cast<core::Resource*>(resource.get()) = *dynamic_cast<core::Resource*>(ptr.get());
}

void
utils::SmartSerializer::damagingPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                 const QJsonObject& changes,
                                                 const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("damaging");
    std::shared_ptr<core::Attribute> ptr = deserializer(changes).value();
    *dynamic_cast<core::Damaging*>(resource.get()) = *dynamic_cast<core::Damaging*>(ptr.get());
}

void
utils::SmartSerializer::damageablePartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                   const QJsonObject& changes,
                                                   const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("damageable");
    std::shared_ptr<core::Attribute> ptr = deserializer(changes).value();
    *dynamic_cast<core::Damageable*>(resource.get()) = *dynamic_cast<core::Damageable*>(ptr.get());
}

void
utils::SmartSerializer::movingPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                               const QJsonObject& changes,
                                               const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("moving");
    std::shared_ptr<core::Attribute> ptr = deserializer(changes).value();
    *dynamic_cast<core::Moving*>(resource.get()) = *dynamic_cast<core::Moving*>(ptr.get());
}

void
utils::SmartSerializer::miningPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                               const QJsonObject& changes,
                                               const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("mining");
    std::shared_ptr<core::Attribute> ptr = deserializer(changes).value();
    *dynamic_cast<core::Mining*>(resource.get()) = *dynamic_cast<core::Mining*>(ptr.get());
}

void utils::SmartSerializer::wallPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                  const QJsonObject& changes,
                                                  const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("wall");
    std::shared_ptr<core::Attribute> ptr = deserializer(changes).value();
    *dynamic_cast<core::Wall*>(resource.get()) = *dynamic_cast<core::Wall*>(ptr.get());
}

void utils::SmartSerializer::costPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                  const QJsonObject& changes,
                                                  const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("cost");
    std::shared_ptr<core::Attribute> ptr = deserializer(changes).value();
    *dynamic_cast<core::Cost*>(resource.get()) = *dynamic_cast<core::Cost*>(ptr.get());

}

void
utils::SmartSerializer::builderPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                const QJsonObject& changes,
                                                const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("builder");
    std::shared_ptr<core::Attribute> ptr = deserializer(changes).value();
    *dynamic_cast<core::Builder*>(resource.get()) = *dynamic_cast<core::Builder*>(ptr.get());
}

QJsonObject utils::SmartSerializer::resourcePartSerializer(
        const std::shared_ptr<core::Attribute>& beforeChanges,
        const std::shared_ptr<core::Attribute>& afterChanges,
        const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Resource*>(beforeChanges.get())) ==
            (*dynamic_cast<core::Resource*>(afterChanges.get()))){
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("resource");
    return seriazlier(afterChanges).value();
}

QJsonObject utils::SmartSerializer::damagingPartSerializer(
        const std::shared_ptr<core::Attribute>& beforeChanges,
        const std::shared_ptr<core::Attribute>& afterChanges, const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Damaging*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Damaging*>(afterChanges.get()))){
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("damaging");
    return seriazlier(afterChanges).value();
}

QJsonObject utils::SmartSerializer::damageablePartSerializer(
        const std::shared_ptr<core::Attribute>& beforeChanges,
        const std::shared_ptr<core::Attribute>& afterChanges, const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Damageable*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Damageable*>(afterChanges.get()))){
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("damageable");
    return seriazlier(afterChanges).value();
}

QJsonObject
utils::SmartSerializer::movingPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                             const std::shared_ptr<core::Attribute>& afterChanges,
                                             const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Moving*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Moving*>(afterChanges.get()))){
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("moving");
    return seriazlier(afterChanges).value();
}

QJsonObject
utils::SmartSerializer::miningPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                             const std::shared_ptr<core::Attribute>& afterChanges,
                                             const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Mining*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Mining*>(afterChanges.get()))){
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("mining");
    return seriazlier(afterChanges).value();
}

QJsonObject
utils::SmartSerializer::wallPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                           const std::shared_ptr<core::Attribute>& afterChanges,
                                           const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Wall*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Wall*>(afterChanges.get()))){
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("wall");
    return seriazlier(afterChanges).value();
}

QJsonObject
utils::SmartSerializer::costPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                           const std::shared_ptr<core::Attribute>& afterChanges,
                                           const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Cost*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Cost*>(afterChanges.get()))){
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("cost");
    return seriazlier(afterChanges).value();
}

QJsonObject
utils::SmartSerializer::builderPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                              const std::shared_ptr<core::Attribute>& afterChanges,
                                              const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Builder*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Builder*>(afterChanges.get()))){
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("builder");
    return seriazlier(afterChanges).value();
}
