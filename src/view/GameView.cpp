#include "GameView.h"
#include "../controller/GameController.h"
#include "../globals.h"
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_utf8.h>
#include <FL/fl_ask.H>  // Добавлено для fl_alert()
#include <FL/Fl_Window.H>

GameView::GameView(int w, int h, const char* title) 
    : Fl_Double_Window(w, h, title), 
      m_controller(nullptr),
      m_model(nullptr) {
    
    begin();
    
    m_background = new Fl_Box(0, 0, w, h);
    
    m_titleBox = new Fl_Box(0, 0, w, 256);
    m_titleBox->hide();
    
    m_startButton = new GUIButton(190, 230, 128, 76, "PLAY");
    m_startButton->callback(startCallback, this);
    m_startButton->hide();
    
    m_aboutButton = new GUIButton(190, 315, 128, 76, "ABOUT");
    m_aboutButton->callback(aboutCallback, this);
    m_aboutButton->hide();
    
    m_exitButton = new GUIButton(190, 400, 128, 76, "EXIT");
    m_exitButton->callback(exitCallback, this);
    m_exitButton->hide();
    
    end();
    
    showMainMenu();
}

GameView::~GameView() {
    // Деструктор не должен удалять FLTK виджеты - они удаляются автоматически
}

void GameView::showWinScreen() {
    resize(x(), y(), 512, 512);
    
    std::string winPath = ASSETS_DIR + "winscreen.png";
    Fl_PNG_Image* png = new Fl_PNG_Image(winPath.c_str());
    if (png) {
        m_background->image(png->copy(w(), h()));
    }
    
    m_titleBox->hide();
    m_startButton->show();
    m_aboutButton->show();
    m_exitButton->show();
    
    redraw();
}

void GameView::showMainMenu() {
    resize(x(), y(), 512, 512);
    
    std::string bgPath = ASSETS_DIR + "background1.jpg";
    Fl_JPEG_Image* img = new Fl_JPEG_Image(bgPath.c_str());
    if (!img) {
        fl_alert("Failed to load background image: %s", bgPath.c_str());
        return;
    }
    m_background->image(img->copy(w(), h()));
    
    std::string titlePath = ASSETS_DIR + "title.png";
    Fl_PNG_Image* titleImg = new Fl_PNG_Image(titlePath.c_str());
    if (!titleImg) {
        fl_alert("Failed to load title image: %s", titlePath.c_str());
        return;
    }
    m_titleBox->image(titleImg);

    int window_width = 512;
    int window_height = 512;
    // Вычисляем размеры экрана
    int screenW = Fl::w();
    int screenH = Fl::h();
    int newX = (screenW - window_width) / 2;
    int newY = (screenH - window_height) / 2;
    
    resize(newX, newY, window_width, window_height);

    
    
    m_titleBox->show();
    m_startButton->show();
    m_aboutButton->show();
    m_exitButton->show();
    
    redraw();
}

// GameView.cpp - исправленный метод startGame()
void GameView::startGame(int levelWidth, int levelHeight) {
    // 1. Скрываем элементы меню
    m_titleBox->hide();
    m_startButton->hide();
    m_aboutButton->hide();
    m_exitButton->hide();

    // 2. Устанавливаем игровой размер окна
    size(800, 600);

    // 3. Очищаем и пересоздаем содержимое окна
    clear();
    begin();
    
    // 4. Создаем игровую сцену
    m_gameGroup = new Fl_Group(0, 0, w(), h());
    m_gameGroup->begin();
    
    // Фон
    m_background = new Fl_Box(0, 0, w(), h());
    Fl_JPEG_Image* bg = new Fl_JPEG_Image((ASSETS_DIR + "background1.jpg").c_str());
    if(bg) m_background->image(bg->copy(w(), h()));
    
    // 5. Добавляем игровые объекты из модели
    if(m_model) {
        for(auto obj : m_model->getObjects()) {
            obj->show(); // Делаем объекты видимыми
        }
        if(m_model->getPlayer()) {
            m_model->getPlayer()->show();
        }
    }
    
    m_gameGroup->end();
    end();
    
    // 6. Принудительная перерисовка
    redraw();
}

void GameView::showAbout() {
    fl_message("FLTK Platformer\nVersion 1.0\nCreated with FLTK");
    redraw();
}



void GameView::draw() {
    Fl_Double_Window::draw();
    
    // Фон рисуется автоматически через Fl_Box
    if(m_model && m_gameGroup) {
        // Обновляем позиции всех объектов
        for(auto obj : m_model->getObjects()) {
            obj->position(obj->x(), obj->y());
        }
        if(m_model->getPlayer()) {
            m_model->getPlayer()->position(
                m_model->getPlayer()->x(), 
                m_model->getPlayer()->y());
        }
        
        // Перерисовываем игровую группу
        m_gameGroup->redraw();
    }
}

void GameView::startCallback(Fl_Widget* w, void* data) {
    GameView* view = static_cast<GameView*>(data);
    if (view->m_controller) {
        view->m_controller->startGame();
    }
}

void GameView::aboutCallback(Fl_Widget* w, void* data) {
    GameView* view = static_cast<GameView*>(data);
    view->showAbout();
}

void GameView::exitCallback(Fl_Widget* w, void* data) {
    exit(0);
}

int GameView::handle(int event) {
    if (m_controller) {
        switch (event) {
            case FL_KEYDOWN:
                m_controller->handleInput(Fl::event_key(), true);
                return 1;
            case FL_KEYUP:
                m_controller->handleInput(Fl::event_key(), false);
                return 1;
        }
    }
    return Fl_Double_Window::handle(event);
}