#ifndef NETWORKSCREEN_H
#define NETWORKSCREEN_H
#include <QPushButton>

#include "../screen.h"
#include "../network/multiplayerinterface.h"
#include "../widgets/textedit.h"

namespace client {

class NetworkScreen : public Screen {
  public:
    NetworkScreen();

  private:
    void onPaused() override;

    void onResumed() override;

    void connectClicked();

    static bool matchesIpRegex(const QString& text);

    TextEdit* ipInput;
    TextEdit* portInput;

    std::shared_ptr<MultiplayerInterface> multiplayerInterface;
};

}

#endif //NETWORKSCREEN_H
