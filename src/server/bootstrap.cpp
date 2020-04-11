#include <QTextStream>
#include <QQueue>
#include <QDebug>

#include "../utils/factory.h"
#include "../core/command.h"
#include "../core/damageable.h"
#include "../core/serializer.h"
#include "strategies/movestrategy.h"

#include "engine.h"
#include "server.h"

#include "controllers/controller.h"
#include "controllers/databundle.h"

void registerGameObjects() {
    // unit
    //utils::Factory::registerSerializer("unit", );
}

void registerStrategies() {
    utils::Factory::registerStrategy("moveStrategy",
                                     [](core::Object* object) {
                                         return static_cast<server::Strategy*>(new server::MoveStrategy(
                                                 object));
                                     });
}

void registerAttributes() {
    utils::Factory::registerAttribute(core::Damageable::attributeName,
                                      core::Serializer::damageableSerializer,
                                      core::Serializer::damageableDeserializer);
}

int main(int argc, char** argv) {
    registerGameObjects();
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
