#include <QTextStream>
#include <QQueue>
#include <QDebug>

#include "../utils/factory.h"
#include "../core/command.h"
#include "../core/attributes/damageable.h"
#include "../utils/serializer.h"
#include "../server/strategies/movestrategy.h"

#include "../server/engine.h"
#include "../server/server.h"

#include "../server/controllers/controller.h"
#include "../server/controllers/databundle.h"

void registerStrategies() {
    utils::Factory::registerStrategy("moveStrategy",
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

int main(int argc, char** argv) {
    registerAttributes();
    registerStrategies();
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
