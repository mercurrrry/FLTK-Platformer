#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../model/GameModel.h"
#include "../view/GameView.h"
#include <vector>
#include <string>

class GameController {
public:
    GameController(GameModel* model, GameView* view);
    ~GameController();
    
    void loadGame();
    void startGame();
    void updateGame();
    void handleInput(int key, bool state);
    void nextLevel();
    void returnToMenu();
    
private:
    GameModel* m_model;
    GameView* m_view;
    std::vector<std::string> m_levels;
    int m_currentLevel;
    
    bool m_leftPressed;
    bool m_rightPressed;
    bool m_jumpPressed;
    
    void loadLevels();
};

#endif // GAMECONTROLLER_H