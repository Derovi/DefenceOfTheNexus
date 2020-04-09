#include <QTextStream>
#include <QQueue>
#include <QDebug>

#include "../utils/factory.h"
#include "../core/command.h"

#include "engine.h"
#include "server.h"


void registerGameObjects() {
    // unit
    utils::Factory::registerController("unit", [](core::Object* object) {
        return server::UnitController::create(object);
    });
    //utils::Factory::registerSerializer("unit", );
}

int main(int argc, char** argv) {
    registerGameObjects();
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

