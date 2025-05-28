#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <string>

class GameObject : public Fl_Box {
public:
    GameObject(int x, int y, int w, int h, const std::string& spritePath);
    virtual ~GameObject();
    
    virtual bool checkCollision(int px, int py, int pw, int ph) const;
    std::pair<int, int> getCenter() const;
    
protected:
    Fl_Image* m_image;
    std::string m_spritePath;
};

// GameObject.h
class Sawblade : public GameObject {
    public:
        Sawblade(int x, int y, int w, int h) 
            : GameObject(x, y, w, h, "sawblade.png") {}
    };
    
    class ExitPortal : public GameObject {
    public:
        ExitPortal(int x, int y, int w, int h) 
            : GameObject(x, y, w, h, "treasurechest.png") {}
    };
    
    class Key : public GameObject {
    public:
        Key(int x, int y, int w, int h) 
            : GameObject(x, y, w, h, "key.png") {}
    };

#endif // GAMEOBJECT_H