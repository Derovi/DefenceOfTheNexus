#include <QHash>
#include <QFile>
#include <QDirIterator>
#include <QDebug>

#include "lang.h"
#include "serializer.h"

const QString utils::Lang::get(const QString& key) {
    if (!langMap.contains(key)) {
        return "";
    }
    return langMap[key];
}

void utils::Lang::load(const QString& lang, const QString& baseLang) {
    QDir directory(":/lang/");

    QFile langFile(":/lang/" + lang);
    QFile baseLangFile(":/lang/" + baseLang);

    if (!langFile.open(QIODevice::ReadOnly) ||
        !baseLangFile.open(QIODevice::ReadOnly)) {
        return;
    }

    Serializer serializer;
    auto langJson = serializer.stringToJsonObject(QString(langFile.readAll()));
    auto baseLangJson = serializer.stringToJsonObject(QString(baseLangFile.readAll()));

    loadEntry("", baseLangJson.value());
    loadEntry("", langJson.value());
}

void utils::Lang::loadEntry(QString path, const QJsonObject& jsonObject) {
    if (!path.isEmpty()) {
        path += '.';
    }
    for (QString valueName : jsonObject.keys()) {
        QJsonValue value = jsonObject[valueName];
        if (value.isObject()) {
            loadEntry(path + valueName, value.toObject());
        } else {
            langMap.insert(path + valueName, value.toString());
        }
    }
}

QHash<QString, QString> utils::Lang::langMap;
