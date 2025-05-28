#include "GameObject.h"
#include "../globals.h"
#include <FL/fl_utf8.h>

GameObject::GameObject(int x, int y, int w, int h, const std::string& spritePath) 
    : Fl_Box(x, y, w, h), m_spritePath(spritePath) {
    
    box(FL_NO_BOX);
    
    std::string fullPath = ASSETS_DIR + spritePath;
    if (spritePath.find(".png") != std::string::npos) {
        m_image = new Fl_PNG_Image(fullPath.c_str());
    } else if (spritePath.find(".jpg") != std::string::npos) {
        m_image = new Fl_JPEG_Image(fullPath.c_str());
    }
    
    if (m_image) {
        image(m_image->copy(w, h));
    }
}

GameObject::~GameObject() {
    if (m_image) {
        delete m_image;
    }
}

bool GameObject::checkCollision(int px, int py, int pw, int ph) const {
    int sx = x(), sy = y();
    int sx2 = sx + w(), sy2 = sy + h();
    
    return !(py + ph < sy || py >= sy2 || px + pw < sx || px >= sx2);
}

std::pair<int, int> GameObject::getCenter() const {
    return {x() + (w() / 2), y() + (h() / 2)};
}