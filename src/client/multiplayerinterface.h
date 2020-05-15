#ifndef MULTIPLAYERINTERFACE_H
#define MULTIPLAYERINTERFACE_H

#include <QtCore/QObject>
#include <QtNetwork/QUdpSocket>
#include <memory>

class MultiplayerInterface : public QObject {
  Q_OBJECT
  public:
    MultiplayerInterface();

    void start();

  private:
    std::shared_ptr<QUdpSocket> socket = nullptr;

  private slots:
            void onReadyRead();
};

#endif  //MULTIPLAYERINTERFACE_H
