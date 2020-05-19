#ifndef GAMECONFIGURATION_H
#define GAMECONFIGURATION_H

#include <QString>

class GameConfiguration {
  public:
    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    int getTickPerSec() const;

    void setTickPerSec(int tickPerSec);

    int getPlayerCount() const;

    void setPlayerCount(int count);

    double getResourceDensity() const;

    void setResourceDensity(double density);

    uint64_t getSeed() const;

    void setSeed(uint64_t seed);

    QString getExplorerType() const;

    void setExplorerType(QString explorer);

  private:
    int width = 7000;
    int height = 7000;
    int tickPerSec = 60;
    int playerCount = 1;
    double resourceDensity = 0.0007;
    uint64_t seed = 1337;
    QString explorerType = "player";
};

#endif  // GAMECONFIGURATION_H
