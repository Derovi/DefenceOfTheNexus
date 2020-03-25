#include <QTextStream>
#include <QQueue>

#include "../core/command.h"

#include "engine.h"
#include "server.h"

int main(int argc, char** argv) {
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
        engine->getCommandQueue()->push_back(core::Command::getCommand(line));
    }
}