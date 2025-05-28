cmake_minimum_required(VERSION 3.10)
project(FLTK_Platformer)

# Настройка компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск FLTK
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})

# Добавление исполняемого файла
add_executable(FLTK_Platformer
    src/main.cpp
    src/controller/GameController.cpp
    src/controller/GameController.h
    src/model/GameModel.cpp
    src/model/GameModel.h
    src/model/GameObject.cpp
    src/model/GameObject.h
    src/model/Player.cpp
    src/model/Player.h
    src/view/GameView.cpp
    src/view/GameView.h
    src/view/GUIButton.cpp
    src/view/GUIButton.h
    src/globals.h
)

# Подключение FLTK
target_link_libraries(FLTK_Platformer ${FLTK_LIBRARIES})

# Копирование ресурсов в папку сборки
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY levels.txt DESTINATION ${CMAKE_BINARY_DIR})

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})