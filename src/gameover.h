#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include <string>

const static std::string oGameOver("Game Over");

class cGameOver {

public: 

    cGameOver();

    ~cGameOver();

    bool initialize();

    void render();

};

#endif // GAMEOVER_H_