#include "GameModel.h"
#include "../globals.h"
#include <algorithm>
#include <fstream>
#include <sstream>

GameModel::GameModel() {}

GameModel::~GameModel() {
    for (auto obj : m_objects) {
        delete obj;
    }
    m_objects.clear();
}

bool GameModel::loadLevel(const std::string& levelData) {
    // Clear previous level
    for (auto obj : m_objects) {
        delete obj;
    }
    m_objects.clear();
    m_keyCoords.clear();
    
    std::istringstream iss(levelData);
    std::string line;
    std::vector<std::string> rows;
    
    while (std::getline(iss, line)) {
        rows.push_back(line);
    }
    
    if (rows.empty()) return false;
    
    int r = rows.size();
    int c = rows[0].size();
    m_background = "background1.jpg";
    
    int keys = 0;
    
    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            char id = rows[row][col];
            
            if (id == '@') {
                m_player = std::make_unique<Player>((col * TILE_SIZE) - TILE_SIZE, 
                                                   (row * TILE_SIZE) - TILE_SIZE, 
                                                   16, 32);
            } else if (id == 'k') {
                keys++;
                m_objects.push_back(new Key(col * TILE_SIZE - TILE_SIZE, 
                                        row * TILE_SIZE - TILE_SIZE, 
                                        TILE_SIZE, TILE_SIZE));
                m_keyCoords.emplace_back(col * TILE_SIZE - TILE_SIZE, 
                            row * TILE_SIZE - TILE_SIZE);
            } else if (id == 'X') {
                m_objects.push_back(new GameObject((col * TILE_SIZE) - TILE_SIZE, 
                                                 (row * TILE_SIZE) - TILE_SIZE, 
                                                 TILE_SIZE, TILE_SIZE, 
                                                 "platformblock.png"));
            } else if (id == '^') {
                m_objects.push_back(new GameObject((col * TILE_SIZE) - TILE_SIZE + 1, 
                                                 (row * TILE_SIZE) - TILE_SIZE + 1, 
                                                 TILE_SIZE - 2, TILE_SIZE - 2, 
                                                 "sawblade.png"));
            } else if (id == '*') {
                m_objects.push_back(new GameObject((col * TILE_SIZE) - TILE_SIZE, 
                                                 (row * TILE_SIZE) - TILE_SIZE, 
                                                 TILE_SIZE, TILE_SIZE, 
                                                 "treasurechest.png"));
            } else if (id == '=') {
                m_objects.push_back(new GameObject((col * TILE_SIZE) - TILE_SIZE, 
                                                 (row * TILE_SIZE) - TILE_SIZE + (TILE_SIZE / 2), 
                                                 TILE_SIZE, TILE_SIZE / 2, 
                                                 "jumppad.png"));
            }

        }
    }
    
    if (m_player) {
        m_player->setNeededKeys(keys);
    }
    
    return true;
}

void GameModel::update(bool leftPressed, bool rightPressed, bool jumpPressed) {
    if (m_player) {
        m_player->move(leftPressed, rightPressed, jumpPressed);
    }
}

// GameModel.cpp
void GameModel::resetLevel() {
    if (m_player) {
        m_player->reset();
        
        // Remove all keys
        m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), 
            [](GameObject* obj) { 
                return dynamic_cast<Key*>(obj) != nullptr; 
            }), m_objects.end());
        
        // Add keys back
        for (const auto& coords : m_keyCoords) {
            m_objects.push_back(new Key(coords.first, coords.second, 
                                      TILE_SIZE, TILE_SIZE));
        }
    }
}

bool GameModel::checkPlayerCollisionWith(GameObject* obj) const {
    if (!m_player || !obj) return false;
    
    return obj->checkCollision(m_player->x(), m_player->y(), 
                             m_player->w(), m_player->h());
}