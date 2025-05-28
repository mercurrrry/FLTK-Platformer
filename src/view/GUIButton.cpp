#include "GUIButton.h"
#include "../globals.h"
#include <FL/fl_utf8.h>
#include <FL/fl_ask.H>

GUIButton::GUIButton(int x, int y, int w, int h, const std::string& label) 
    : Fl_Button(x, y, w, h), m_pressed(false) {
    
    box(FL_NO_BOX);
    clear_visible_focus();
    
    std::string upPath = ASSETS_DIR + "upbutspr.png";
    std::string downPath = ASSETS_DIR + "downbutspr.png";
    
    m_upImage = new Fl_PNG_Image(upPath.c_str());
    m_downImage = new Fl_PNG_Image(downPath.c_str());
    
    image(m_upImage->copy(w, h));
    
    m_labelBox = new Fl_Box(x, y - 5, w, h);
    m_labelBox->copy_label(label.c_str());
    m_labelBox->labelsize(30);
    m_labelBox->labelfont(FL_COURIER_BOLD);
    m_labelBox->box(FL_NO_BOX);
    m_upImage = new Fl_PNG_Image(upPath.c_str());
    m_downImage = new Fl_PNG_Image(downPath.c_str());
    
    if (!m_upImage || !m_downImage) {
        fl_alert("Failed to load button images!");
        exit(1);
    }
}

GUIButton::~GUIButton() {
    delete m_upImage;
    delete m_downImage;
    delete m_labelBox;
}

int GUIButton::handle(int event) {
    int result = Fl_Button::handle(event);
    
    switch (event) {
        case FL_PUSH:
        case FL_DRAG:
            if (!m_pressed) {
                m_pressed = true;
                image(m_downImage->copy(w(), h()));
                m_labelBox->position(x(), m_labelBox->y() + 5);
                redraw();
            }
            break;
            
        case FL_RELEASE:
            if (m_pressed) {
                m_pressed = false;
                m_labelBox->position(x(), m_labelBox->y() - 5);
                image(m_upImage->copy(w(), h()));
                redraw();
            }
            break;
    }
    
    return result;
}