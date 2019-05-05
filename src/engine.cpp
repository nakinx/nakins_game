#include "engine.h"

#include "nakins.h"
#include "log.h"
#include "map.h"
#include "snake.h"
#include "topbar.h"
#include "gameover.h"

#include <thread>
#include <chrono>

// @TODO - Implement operator to stringstream at log class and remove this include.
#include <sstream>

cEngine::cEngine() 
    : m_poMap(new cMap()),
      m_poSnake(new cSnake()),
      m_poTopBar(new cTopBar()),
      m_poGameOver(new cGameOver()),
      m_uiSpeed(1000) {
}

cEngine::~cEngine(){
    endwin();
}

void cEngine::initialize(){

    initscr();
    curs_set(0);
    //timeout(1); // Set the timeout of getch.
    noecho(); // Don't show characters on the screen when typed.
    cbreak(); // Take a input one at time;
    keypad(stdscr, true); // Enable arrow keys.
        
    m_poMap.get()->initialize(0);
    m_poSnake.get()->initialize(m_poMap.get()->getEmptySpaceSize());
    m_poTopBar.get()->initialize();
    m_poGameOver.get()->initialize();
}

void cEngine::loop(){
    //eNXKeyPressed oeNXKeyPressed;

    m_poMap.get()->render();    
    m_poMap.get()->renderSnakeFood();
    m_poTopBar.get()->renderRecord();

    m_poGameOver.get()->render();
   
    captureKey();

    // for (;;) {        
    //     m_poSnake.get()->render();                
    //     wrefresh(stdscr);
        
    //     std::this_thread::sleep_for(std::chrono::milliseconds(m_uiSpeed));

    //     oeNXKeyPressed = captureKey();

    //     m_poSnake.get()->move(oeNXKeyPressed);

    //     checkForCollisions();

    //     oeNXKeyPressed = eNXKeyPressed::undefined;        
    // }
}

eNXKeyPressed cEngine::captureKey() {

    const int iPressedKey = getch();

    std::stringstream oSsLog;

    oSsLog << "Key pressed: " << iPressedKey;

    cLog::getInstance().write(eServeriyLevel::Debug, oSsLog.str());

    switch(iPressedKey) {
        case KEY_LEFT:
            return (eNXKeyPressed::left);
        case KEY_RIGHT:
            return (eNXKeyPressed::right);
        case KEY_UP:
            return (eNXKeyPressed::up);
        case KEY_DOWN:
            return (eNXKeyPressed::down);
        case KEY_EXIT:
            return (eNXKeyPressed::escape);
        default: 
            return (eNXKeyPressed::undefined);
    }
}

bool cEngine::checkForCollisions() {
    if (checkSnakeFoodCollision() == true) {
        m_poTopBar.get()->renderScore();
        m_poMap.get()->renderSnakeFood(); 
    }              

    if (checkSnakeBodyCollision() == true) {
        return (false);
    }

    return (true);
}

bool cEngine::checkSnakeBodyCollision() {

    if (m_poSnake.get()->checkSnakeBodyCollision() == true) {


        return (true);
    }       

    return (false);
}

bool cEngine::checkSnakeFoodCollision() {
    STSnakeBody stSnakeBody = m_poSnake.get()->getHeadPosition();
    STSnakeFood stSnakeFood = m_poMap.get()->getSnakeFoodPosition();

    if (stSnakeBody.x == stSnakeFood.x &&
        stSnakeBody.y == stSnakeFood.y)
        {
        cLog::getInstance().write(eServeriyLevel::Verbose, "Snake collision with food detected.");

        m_poSnake.get()->increaseSize();  
        m_poTopBar.get()->increaseScore(eScoreType::food, m_uiSpeed);     

        return (true);
        }

    return (false);
}