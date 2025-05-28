#ifndef PLAYER_H
#define PLAYER_H

#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <map>
#include <string>

class Player : public Fl_Box {
public:
    Player(int x, int y, int w, int h);
    ~Player();
    
    void move(bool leftPressed, bool rightPressed, bool jumpPressed);
    void reset();
    void setPosition(int x, int y);
    
    double getXVelocity() const { return m_xVelocity; }
    double getYVelocity() const { return m_yVelocity; }
    int getKeys() const { return m_keys; }
    int getNeededKeys() const { return m_neededKeys; }
    void addKey() { m_keys++; }
    void setNeededKeys(int keys) { m_neededKeys = keys; }
    
    bool isOnGround() const { return m_states.at('S'); }
    bool isOnLeftWall() const { return m_states.at('W'); }
    bool isOnRightWall() const { return m_states.at('E'); }
    
private:
    void enableInput();
    static void enableInputCallback(void* data);
    
    Fl_PNG_Image* m_sprite;
    double m_xVelocity;
    double m_yVelocity;
    double m_gravity;
    double m_airResistance;
    double m_friction;
    double m_appliedXV;
    
    int m_originalX;
    int m_originalY;
    int m_keys;
    int m_neededKeys;
    
    std::map<char, bool> m_states;
    bool m_canJump;
};

#endif // PLAYER_H