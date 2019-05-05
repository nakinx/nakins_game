#ifndef ENGINE_H_
#define ENGINE_H_

class cMap;
class cSnake;
class cTopBar;
class cGameOver;

#include <memory>

#define NX_MIN_X 90
#define NX_MIN_Y 22

enum class eNXKeyPressed {
    up = 1,
    down = 2,
    left = 4,
    right = 8,
    escape = 16,
    undefined = 2048,
};

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

    bool checkForCollisions();

    bool checkSnakeBodyCollision();

    bool checkSnakeFoodCollision();

    eNXKeyPressed captureKey();
};

#endif // ENGINE_H_