#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QMap>
#include <QString>
#include <QChar>

namespace utils {

class KeyManager {
  public:
    explicit KeyManager(bool hash);

    static QString addKey(QString key);

    QString getHash(QString key) const;

    QString getKey(QString hash) const;

    static void registerKeys();

  private:
    static QString hash;
    bool hashing;
    static QMap<QString, QString> keyToHash;
    static QMap<QString, QString> hashToKey;
};

}  // namespace utils

#endif //KEYMANAGER_H
