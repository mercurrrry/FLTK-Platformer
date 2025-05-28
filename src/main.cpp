#include "view/GameView.h"
#include "model/GameModel.h"
#include "controller/GameController.h"
#include <FL/Fl.H>
#include <FL/fl_ask.H>

int main(int argc, char **argv) {
    GameModel model;
    GameView view(512, 512, "FLTK Platformer");
    GameController controller(&model, &view);
    
    view.setController(&controller);
    view.setModel(&model);
    
    view.show();
    
    // Основной игровой цикл
    while(view.shown()) {
        Fl::wait(0.016); // ~60 FPS
        controller.updateGame();
    }
    
    return 0;
}