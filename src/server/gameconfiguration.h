#ifndef GAMECONFIGURATION_H
#define GAMECONFIGURATION_H

class GameConfiguration {
  public:
    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    int getTickPerSec() const;

    void setTickPerSec(int tickPerSec);

  private:
    int width = 1000;
    int height = 1000;
    int tickPerSec = 60;
};


#endif //GAMECONFIGURATION_H
