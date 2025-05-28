#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>
#include <string>
#include <memory>
#include "GameObject.h"
#include "Player.h"

class GameModel {
public:
    GameModel();
    ~GameModel();
    
    bool loadLevel(const std::string& levelData);
    void update(bool leftPressed, bool rightPressed, bool jumpPressed);
    
    Player* getPlayer() const { return m_player.get(); }
    std::vector<GameObject*>& getObjects() { return m_objects; } // 
    
    void resetLevel();
    bool checkPlayerCollisionWith(GameObject* obj) const;
    
private:
    std::unique_ptr<Player> m_player;
    std::vector<GameObject*> m_objects;
    std::vector<std::pair<int, int>> m_keyCoords;
    std::string m_currentLevel;
    std::string m_background;
};

#endif // GAMEMODEL_H