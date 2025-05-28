#include "Player.h"
#include "../globals.h"
#include <FL/Fl.H>
#include <FL/fl_utf8.h>

Player::Player(int x, int y, int w, int h) 
    : Fl_Box(x, y, w, h), 
      m_originalX(x), m_originalY(y),
      m_xVelocity(0), m_yVelocity(0),
      m_gravity(GRAVITY), 
      m_airResistance(AIR_RESISTANCE),
      m_friction(FRICTION),
      m_appliedXV(PLAYER_MOVE_SPEED),
      m_keys(0), m_neededKeys(0),
      m_canJump(true) {
    
    box(FL_NO_BOX);
    std::string spritePath = ASSETS_DIR + "tomatoboy.png";
    m_sprite = new Fl_PNG_Image(spritePath.c_str());
    image(m_sprite->copy(w, h));
    
    m_states = {{'N', false}, {'E', false}, {'S', false}, {'W', false}};
}

Player::~Player() {
    if (m_sprite) {
        delete m_sprite;
    }
}

void Player::move(bool leftPressed, bool rightPressed, bool jumpPressed) {
    bool frictionFlag = false;
    
    if (leftPressed) {
        m_xVelocity = std::max(-4.0, m_xVelocity - m_appliedXV);
    } else if (rightPressed) {
        m_xVelocity = std::min(4.0, m_xVelocity + m_appliedXV);
    } else {
        // Apply air resistance
        if (m_xVelocity != 0) {
            m_xVelocity -= (m_xVelocity / std::abs(m_xVelocity)) * 
                          std::min(m_airResistance, std::abs(m_xVelocity));
        }
        if (isOnGround()) {
            frictionFlag = true;
        }
    }
    
    if (!isOnGround()) {
        m_yVelocity = std::min(m_yVelocity + m_gravity, MAX_FALL_SPEED);
    } else {
        m_yVelocity = 1.0;
    }
    
    if (jumpPressed && m_canJump) {
        if (isOnGround()) {
            m_yVelocity = PLAYER_JUMP_FORCE;
            m_canJump = false;
        } else if (isOnLeftWall()) {
            m_yVelocity = PLAYER_JUMP_FORCE;
            m_xVelocity = 6.0;
            m_canJump = false;
            m_appliedXV = 0;
            Fl::add_timeout(0.1, enableInputCallback, this);
        } else if (isOnRightWall()) {
            m_yVelocity = PLAYER_JUMP_FORCE;
            m_xVelocity = -6.0;
            m_canJump = false;
            m_appliedXV = 0;
            Fl::add_timeout(0.2, enableInputCallback, this);
        }
    }
    
    position(x() + static_cast<int>(m_xVelocity), y() + static_cast<int>(m_yVelocity));
    
    if (frictionFlag) {
        if (m_xVelocity != 0) {
            m_xVelocity -= (m_xVelocity / std::abs(m_xVelocity)) * 
                          std::min(m_friction, std::abs(m_xVelocity));
        }
    }
    
    // Reset collision states
    m_states['N'] = false;
    m_states['S'] = false;
    if (static_cast<int>(m_xVelocity) != 0) {
        m_states['E'] = false;
        m_states['W'] = false;
    }
}

void Player::reset() {
    position(m_originalX, m_originalY);
    m_xVelocity = 0;
    m_yVelocity = 0;
    m_keys = 0;
    m_canJump = true;
    
    for (auto& state : m_states) {
        state.second = false;
    }
}

void Player::setPosition(int x, int y) {
    position(x, y);
}

void Player::enableInput() {
    m_appliedXV = PLAYER_MOVE_SPEED;
}

void Player::enableInputCallback(void* data) {
    Player* player = static_cast<Player*>(data);
    player->enableInput();
}