#include <QTextStream>
#include <QQueue>
#include <QDebug>
#include <QApplication>

#include "../client/spritecontrollers/unitspritecontroller.h"
#include "../client/spritecontrollers/defaultspritecontroller.h"
#include "../client/objectgraphicsdescription.h"
#include "../utils/serializer.h"
#include "../utils/factory.h"
#include "../utils/lang.h"
#include "../utils/keymanager.h"
#include "../server/strategies/movestrategy.h"
#include "../server/strategies/pathstrategy.h"
#include "../server/engine.h"
#include "../server/network/server.h"
#include "../client/app.h"
#include "../client/properties.h"
#include "../core/attributes/mining.h"
#include "../server/strategies/minestrategy.h"
#include "../client/spritecontrollers/resourcespritecontroller.h"
#include "../server/strategies/attackstrategy.h"
#include "../core/attributes/builder.h"
#include "../utils/smartserializer.h"

void registerStrategies() {
    utils::Factory::registerStrategy(server::MoveStrategy::name,
                                     [](std::shared_ptr<core::Object> object) {
                                         return std::shared_ptr<server::Strategy>(
                                             static_cast<server::Strategy*>(
                                                 new server::MoveStrategy(object)));
                                     });
    utils::Factory::registerStrategy(server::PathStrategy::name,
                                     [](std::shared_ptr<core::Object> object) {
                                         return std::shared_ptr<server::Strategy>(
                                             static_cast<server::Strategy*>(
                                                 new server::PathStrategy(object)));
                                     });
    utils::Factory::registerStrategy(server::MineStrategy::name,
                                     [](std::shared_ptr<core::Object> object) {
                                         return std::shared_ptr<server::Strategy>(
                                             static_cast<server::Strategy*>(
                                                 new server::MineStrategy(object)));
                                     });
    utils::Factory::registerStrategy(server::AttackStrategy::name,
                                     [](std::shared_ptr<core::Object> object) {
                                         return std::shared_ptr<server::Strategy>(
                                             static_cast<server::Strategy*>(
                                                 new server::AttackStrategy(object)));
                                     });
}

void registerAttributes() {
    utils::Factory::registerAttribute(core::Damageable::attributeName,
                                      utils::Serializer::damageableSerializer,
                                      utils::Serializer::damageableDeserializer,
                                      utils::SmartSerializer::damageablePartSerializer,
                                      utils::SmartSerializer::damageablePartDeserializer);

    utils::Factory::registerAttribute(core::Moving::attributeName,
                                      utils::Serializer::movingSerializer,
                                      utils::Serializer::movingDeserializer,
                                      utils::SmartSerializer::movingPartSerializer,
                                      utils::SmartSerializer::movingPartDeserializer);

    utils::Factory::registerAttribute(core::Damaging::attributeName,
                                      utils::Serializer::damagingSerializer,
                                      utils::Serializer::damagingDeserializer,
                                      utils::SmartSerializer::damagingPartSerializer,
                                      utils::SmartSerializer::damagingPartDeserializer);

    utils::Factory::registerAttribute(core::Resource::attributeName,
                                      utils::Serializer::resourceSerializer,
                                      utils::Serializer::resourceDeserializer,
                                      utils::SmartSerializer::resourcePartSerializer,
                                      utils::SmartSerializer::resourcePartDeserializer);

    utils::Factory::registerAttribute(core::Mining::attributeName,
                                      utils::Serializer::miningSerializer,
                                      utils::Serializer::miningDeserializer,
                                      utils::SmartSerializer::miningPartSerializer,
                                      utils::SmartSerializer::miningPartDeserializer);

    utils::Factory::registerAttribute(core::Wall::attributeName,
                                      utils::Serializer::wallSerializer,
                                      utils::Serializer::wallDeserializer,
                                      utils::SmartSerializer::wallPartSerializer,
                                      utils::SmartSerializer::wallPartDeserializer);

    utils::Factory::registerAttribute(core::Cost::attributeName,
                                      utils::Serializer::costSerializer,
                                      utils::Serializer::costDeserializer,
                                      utils::SmartSerializer::costPartSerializer,
                                      utils::SmartSerializer::costPartDeserializer);

    utils::Factory::registerAttribute(core::Builder::attributeName,
                                      utils::Serializer::builderSerializer,
                                      utils::Serializer::builderDeserializer,
                                      utils::SmartSerializer::builderPartSerializer,
                                      utils::SmartSerializer::builderPartDeserializer);
}

void registerSpriteControllers() {
    utils::Factory::registerSpriteController(client::UnitSpriteController::name,
                                             [](std::shared_ptr<core::Object> object) {
                                                 return std::shared_ptr<client::SpriteController>(
                                                     new client::UnitSpriteController(object));
                                             });
    utils::Factory::registerSpriteController(client::ResourceSpriteController::name,
                                             [](std::shared_ptr<core::Object> object) {
                                                 return std::shared_ptr<client::SpriteController>(
                                                     new client::ResourceSpriteController(object));
                                             });
    utils::Factory::registerSpriteController(client::DefaultSpriteController::name,
                                             [](std::shared_ptr<core::Object> object) {
                                                 return std::shared_ptr<client::SpriteController>(
                                                         new client::DefaultSpriteController(object));
                                             });
}

void registerObjectSignatures() {
    QFile file(":/data/objects");
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    utils::Serializer serializer;
    std::optional<QJsonObject> signatures = serializer.stringToJsonObject(
        QString(file.readAll()));
    if (!signatures) {
        return;
    }

    for (auto iter = signatures.value().begin(); iter != signatures.value().end(); ++iter) {
        if (!iter->isObject()) {
            continue;
        }
        QJsonObject object = iter->toObject();
        object.insert("typeName", iter.key());
        auto signature = serializer.objectSignatureDeserializer(object);
        if (signature == std::nullopt) {
            continue;
        }
        utils::Factory::registerObjectSignature(iter.key(), signature.value());
    }
}

void registerGraphicsDescriptions() {
    QFile file(":/data/graphics");
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    utils::Serializer serializer;
    std::optional<QJsonObject> descriptions = serializer.stringToJsonObject(
        QString(file.readAll()));
    if (!descriptions) {
        return;
    }
    for (auto iter = descriptions.value().begin(); iter != descriptions.value().end(); ++iter) {
        auto valueRef = iter.value();
        if (!valueRef.isObject()) {
            continue;
        }
        QJsonObject json = valueRef.toObject();
        client::ObjectGraphicsDescription description;
        if (!json.contains("spriteControllers") || !json.contains("spriteDescriptions")) {
            continue;
        }
        if (json.contains("width") && json.contains("height")) {
            description.setWidth(json.value("width").toInt(50));
            description.setHeight(json.value("height").toInt(50));
        }
        for (const auto& entry : json.value("spriteControllers").toArray(QJsonArray())) {
            if (!entry.isString()) {
                continue;
            }
            description.getSpriteControllers().push_back(entry.toString());
        }
        for (const QString& spriteName : json.value("spriteDescriptions").toObject().keys()) {
            QJsonObject spriteJson = json.value("spriteDescriptions")[spriteName].toObject();
            description.getSpriteDescriptions().insert(spriteName, SpriteDescription(
                spriteJson["resource"].toString(), spriteJson["rows"].toInt(),
                spriteJson["columns"].toInt()));
        }
        utils::Factory::registerObjectGraphicsDescription(iter.key(), description);
    }
}

void registerKeys(){
    utils::KeyManager::registerKeys();
}

int main(int argc, char** argv) {
    registerAttributes();
    registerStrategies();
    registerSpriteControllers();
    registerObjectSignatures();
    registerGraphicsDescriptions();
    registerKeys();
    QApplication a(argc, argv);
    client::App w;
    w.show();

    return a.exec();

    GameConfiguration gameConfiguration;
    auto* engine = new server::Engine(gameConfiguration);
    auto* server = new server::Server();
    // register command queue
    server->registerCommandQueue(engine->getCommandQueue());
    engine->start();
    server->start();
    while (true) {
        QTextStream textStream(stdin);
        QString line = textStream.readLine();
        if (line == "exit") {
            engine->finish();
            server->finish();
            break;
        }
        core::Command command = core::Command::fromCommandLine(line);
        engine->getCommandQueue()->push(core::Command::fromCommandLine(line));
    }
    delete engine;
    delete server;
}
