#include "GameController.h" 
#include <fstream>
#include <FL/Fl.H>
#include <algorithm>
#include <iostream>

GameController::GameController(GameModel* model, GameView* view) 
    : m_model(model), m_view(view), 
      m_currentLevel(0),
      m_leftPressed(false), 
      m_rightPressed(false),
      m_jumpPressed(false) {
    loadLevels();
}

GameController::~GameController() {}

void GameController::loadGame() {
    m_view->showMainMenu();
}

void GameController::startGame() {
    std::cout << "Starting game..." << std::endl;
    m_currentLevel = 0;
    if (!m_levels.empty()) {
        m_model->loadLevel(m_levels[m_currentLevel]);
        m_view->startGame(800, 600);
        
        // Принудительно обновляем игру сразу после старта
        updateGame();
    } else {
        std::cout << "No levels loaded!" << std::endl;
    }
}

// GameController.cpp
void GameController::updateGame() {
    if(!m_view->visible()) return; // Проверка видимости окна
    
    m_model->update(m_leftPressed, m_rightPressed, m_jumpPressed);
    m_jumpPressed = false;
    
    // Check collisions
    auto& objects = m_model->getObjects(); // Теперь получаем неконстантную ссылку
    Player* player = m_model->getPlayer();
    
    if (!player) return;
    
    // Создаем временный вектор для сортировки
    std::vector<GameObject*> sortedObjects(objects.begin(), objects.end());
    
    // Sort objects by distance to player
    std::sort(sortedObjects.begin(), sortedObjects.end(), [player](GameObject* a, GameObject* b) {
        auto aCenter = a->getCenter();
        auto bCenter = b->getCenter();
        int playerX = player->x() + (player->w() / 2);
        int playerY = player->y() + (player->h() / 2);
        
        auto distA = (aCenter.first - playerX) * (aCenter.first - playerX) + 
                    (aCenter.second - playerY) * (aCenter.second - playerY);
        auto distB = (bCenter.first - playerX) * (bCenter.first - playerX) + 
                    (bCenter.second - playerY) * (bCenter.second - playerY);
        
        return distA < distB;
    });
    
    // Check collisions with closest objects
    int counter = 0;
    for (size_t i = 0; i < objects.size() && counter < 12; i++) {
        GameObject* obj = objects[i];
        
        if (m_model->checkPlayerCollisionWith(obj)) {
            // Используем RTTI для правильной идентификации объектов
            if (dynamic_cast<Sawblade*>(obj)) {
                m_model->resetLevel();
                break;
            } else if (dynamic_cast<ExitPortal*>(obj)) {
                if (player->getKeys() >= player->getNeededKeys()) {
                    nextLevel();
                    return;
                }
            } else if (dynamic_cast<Key*>(obj)) {
                player->addKey();
                objects.erase(objects.begin() + i);
                delete obj;
                i--;
            }
        }
        counter++;
    }
    
    m_view->redraw();
    Fl::check(); 
}

void GameController::handleInput(int key, bool state) {
    switch (key) {
        case FL_Left: m_leftPressed = state; break;
        case FL_Right: m_rightPressed = state; break;
        case FL_Up: 
        case 'c': m_jumpPressed = state; break;
    }
}

void GameController::nextLevel() {
    m_currentLevel++;
    if (m_currentLevel < m_levels.size()) {
        m_model->loadLevel(m_levels[m_currentLevel]);
        m_view->startGame(m_model->getPlayer()->w(), m_model->getPlayer()->h());
    } else {
        m_view->showWinScreen();
    }
}

void GameController::returnToMenu() {
    m_view->showMainMenu();
}

void GameController::loadLevels() {
    std::ifstream file("levels.txt");
    if (!file.is_open()) return;
    
    std::string level;
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.empty()) {
            if (!level.empty()) {
                m_levels.push_back(level);
                level.clear();
            }
        } else {
            level += line + "\n";
        }
    }
    
    if (!level.empty()) {
        m_levels.push_back(level);
    }
}