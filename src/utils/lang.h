#ifndef LANG_H
#define LANG_H

#include <QString>

namespace utils {

class Lang {
  public:
    static void load(const QString& lang, const QString& baseLang);

    static QStringList getLanguages();

    static const QString& get(const QString& key);

    static QString getTitle(const QString& lang);

  private:
    static QHash<QString, QString> langMap;

    static void loadEntry(QString path, const QJsonObject& object);
};

}

#endif //LANG_H
