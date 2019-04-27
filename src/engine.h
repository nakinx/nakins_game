#ifndef ENGINE_H_
#define ENGINE_H_

class cMap;
class cSnake;

#include <memory>

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

    bool checkSnakeFoodCollision();

    eNXKeyPressed captureKey();

};

#endif // ENGINE_H_