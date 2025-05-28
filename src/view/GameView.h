#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <memory>
#include "GUIButton.h"

class GameController;
class GameModel;


class GameView : public Fl_Double_Window {
public:
    GameView(int w, int h, const char* title = nullptr);
    virtual ~GameView();  // Добавлено virtual
    int handle(int event) override;
    void showMainMenu();
    void startGame(int levelWidth, int levelHeight);
    void showWinScreen();  // Убедитесь, что объявлено
    void showAbout();
    
    void setController(GameController* controller) { m_controller = controller; }
    void setModel(GameModel* model) { m_model = model; }
    
    void draw() override;
    
private:
    GameController* m_controller;
    GameModel* m_model;
    Fl_Group* m_gameGroup;
    
    Fl_Box* m_background;
    Fl_Box* m_titleBox;
    GUIButton* m_startButton;
    GUIButton* m_aboutButton;
    GUIButton* m_exitButton;
    
    static void startCallback(Fl_Widget* w, void* data);
    static void aboutCallback(Fl_Widget* w, void* data);
    static void exitCallback(Fl_Widget* w, void* data);
};

#endif // GAMEVIEW_H