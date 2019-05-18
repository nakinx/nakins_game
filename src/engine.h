#ifndef ENGINE_H_
#define ENGINE_H_

#include "nakins.h"

#include <memory>

class cMap;
class cSnake;
class cTopBar;
class cGameOver;

class cEngine {

public:
    cEngine();

    ~cEngine();

    void initialize();

    void loop();

private:
    std::unique_ptr<cMap> m_poMap;
    std::unique_ptr<cSnake> m_poSnake;
    std::unique_ptr<cTopBar> m_poTopBar;
    std::unique_ptr<cGameOver> m_poGameOver;
    unsigned int m_uiSpeed;
    unsigned int m_uiUISpeed;

    bool checkForCollisions();

    bool checkSnakeBodyCollision();

    bool checkSnakeFoodCollision();

    eNXKeyPressed captureKey();
};

#endif // ENGINE_H_