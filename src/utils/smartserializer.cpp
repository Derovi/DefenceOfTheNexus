#include "smartserializer.h"

utils::SmartSerializer::SmartSerializer(bool prettyPrinting) {
    utils::SmartSerializer::prettyPrinting = prettyPrinting;
}

QJsonObject utils::SmartSerializer::partObjectSerializer(
        const std::shared_ptr<const core::Object>& beforeChanges,
        const std::shared_ptr<const core::Object>& afterChanges,
        const utils::KeyManager& keyManager) {
    QJsonObject ans;

}
