#include "properties.h"

QString client::properties::baseLang = "en";

QString client::properties::lang = "by";

int client::properties::width = 1200;

int client::properties::height = 675;

int client::properties::frameRate = 60;

bool client::properties::fullscreen = false;

QJsonObject client::properties::serialize() {
    QJsonObject json;
    json["baseLang"] = properties::baseLang;
    json["lang"] = properties::lang;
    json["width"] = properties::width;
    json["height"] = properties::height;
    json["frameRate"] = properties::frameRate;
    json["fullscreen"] = properties::fullscreen;
    return json;
}

void client::properties::load(QJsonObject json) {
    properties::baseLang = json["baseLang"].toString();
    properties::lang = json["lang"].toString();
    properties::width = json["width"].toDouble();
    properties::height = json["height"].toDouble();
    properties::frameRate = json["frameRate"].toDouble();
    properties::fullscreen = json["fullscreen"].toDouble();
}


