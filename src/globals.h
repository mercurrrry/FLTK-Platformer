#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <FL/Fl.H>

const std::string ASSETS_DIR = "assets/";

// Game constants
const int TILE_SIZE = 32;
const double GRAVITY = 0.6;
const double PLAYER_JUMP_FORCE = -11.0;
const double MAX_FALL_SPEED = 10.0;
const double PLAYER_MOVE_SPEED = 0.6;
const double AIR_RESISTANCE = 0.15;
const double FRICTION = 0.8;

#endif // GLOBALS_H