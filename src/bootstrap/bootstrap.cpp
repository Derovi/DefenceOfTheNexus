#include <QTextStream>
#include <QQueue>
#include <QDebug>
#include <QApplication>

#include "../client/spritecontrollers/unitspritecontroller.h"
#include "../client/objectgraphicsdescription.h"
#include "../utils/serializer.h"
#include "../utils/factory.h"
#include "../utils/lang.h"
#include "../server/strategies/movestrategy.h"
#include "../server/engine.h"
#include "../server/server.h"
#include "../client/mainwindow.h"
#include "../client/properties.h"

void registerStrategies() {
    utils::Factory::registerStrategy(server::MoveStrategy::name,
                                     [](std::shared_ptr<core::Object> object) {
                                         return std::shared_ptr<server::Strategy>(
                                                 static_cast<server::Strategy*>(
                                                         new server::MoveStrategy(object)));
                                     });
}

void registerAttributes() {
    utils::Factory::registerAttribute(core::Damageable::attributeName,
                                      utils::Serializer::damageableSerializer,
                                      utils::Serializer::damageableDeserializer);

    utils::Factory::registerAttribute(core::Moving::attributeName,
                                      utils::Serializer::movingSerializer,
                                      utils::Serializer::movingDeserializer);

    utils::Factory::registerAttribute(core::Damaging::attributeName,
                                      utils::Serializer::damagingSerializer,
                                      utils::Serializer::damagingDeserializer);

    utils::Factory::registerAttribute(core::Resource::attributeName,
                                      utils::Serializer::resourceSerializer,
                                      utils::Serializer::resourceDeserializer);
}

void registerSpriteControllers() {
    utils::Factory::registerSpriteController(client::UnitSpriteController::name,
                                             [](std::shared_ptr<core::Object> object) {
                                                 return std::shared_ptr<client::SpriteController>(
                                                         new client::UnitSpriteController(object));
                                             });
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
    for (auto iter = descriptions.value().begin();
         iter != descriptions.value().end();
         ++iter) {
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

int main(int argc, char** argv) {
    registerAttributes();
    registerStrategies();
    registerSpriteControllers();
    registerGraphicsDescriptions();
    utils::Lang::load(client::properties::lang, client::properties::baseLang);

    QApplication a(argc, argv);
    client::MainWindow w;
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
        engine->getCommandQueue()->push_back(core::Command::fromCommandLine(line));
    }
    delete engine;
    delete server;
}
