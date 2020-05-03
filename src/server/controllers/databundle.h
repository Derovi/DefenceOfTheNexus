#ifndef DATABUNDLE_H
#define DATABUNDLE_H

#include <memory>

#include <QDebug>
#include <QHash>
#include <QString>

namespace server {

class DataBundle {
  public:
    DataBundle() = default;

    template<class T>
    void registerVariable(const QString& name, std::shared_ptr<T> variable);

    // true if successfully assigned (variable in bundle not exists or has type T)
    template<class T>
    bool assign(const QString& name, std::shared_ptr<T>& variable);

  private:

    QHash<QString, std::shared_ptr<void>> data;
};

template<class T>
void DataBundle::registerVariable(const QString& name, std::shared_ptr<T> variable) {
    data.insert(name, variable);
}

template<class T>
bool DataBundle::assign(const QString& name, std::shared_ptr<T>& variable) {
    if (!data.contains(name)) {
        return false;
    }
    std::shared_ptr<T> foundVariable = std::static_pointer_cast<T>(data[name]);
    if (foundVariable == nullptr) {
        return false;
    }
    variable = foundVariable;
    return true;
}

}

#endif // DATABUNDLE_H
