#ifndef TOPBAR_H_
#define TOPBAR_H_

#include <ncurses.h>

#define SCORE_SPACE_SIZE 25

enum class eScoreType {
    food = 10,
    fruit = 50,
};

class cTopBar {

public:
    cTopBar();

    ~cTopBar();

    bool initialize();

    void renderScore();

    void renderRecord();

    void increaseScore(const eScoreType oeScoreType, 
                       const unsigned int iSpeed);

private:
    unsigned int m_uliRecord;
    unsigned int m_uliScore;

};

#endif // TOPBAR_H_