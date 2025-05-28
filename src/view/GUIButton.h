#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <string>

class GUIButton : public Fl_Button {
public:
    GUIButton(int x, int y, int w, int h, const std::string& label = "");
    ~GUIButton();
    
    int handle(int event) override;
    
private:
    Fl_PNG_Image* m_upImage;
    Fl_PNG_Image* m_downImage;
    Fl_Box* m_labelBox;
    bool m_pressed;
    
    void updateAppearance();
};

#endif // GUIBUTTON_H