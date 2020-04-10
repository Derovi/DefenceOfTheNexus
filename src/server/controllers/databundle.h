#ifndef DATABUNDLE_H
#define DATABUNDLE_H

#include <QHash>
#include <QString>

namespace server {

class DataBundle {
  public:
    DataBundle() = default;

    template<class T>
    void registerVariable(const QString& name, T* variable);

    // true if successfully assigned (variable in bundle not exists or has type T)
    template<class T>
    bool assign(const QString& name, T*& variable);

  private:

    QHash<QString, void*> data;
};

template<class T>
void DataBundle::registerVariable(const QString& name, T* variable) {
    data.insert(name, variable);
}

template<class T>
bool DataBundle::assign(const QString& name, T*& variable) {
    if (!data.contains(name)) {
        registerVariable(name, variable);
        return true;
    }
    T* foundVariable = reinterpret_cast<T*>(data[name]);
    variable = foundVariable;
    return true;
}

}

#endif //DATABUNDLE_H
