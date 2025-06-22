#pragma once

#include <cstdint>
#include <raylib/raylib.h>

// Keyboard key codes
enum KeyboardKeyCode: uint8_t { Z_KEY_LEFT = 0x80, Z_KEY_UP = 0x40, Z_KEY_RIGHT = 0x20, Z_KEY_DOWN = 0x10, Z_KEY_ESCAPE = 0x08, Z_KEY_PAUSE = 0x04, Z_KEY_ENTER = 0x02, Z_KEY_SPACE = 0x01, Z_KEY_NONE = 0x00 };

// Object identificators
enum EntityIdentificator: uint16_t { NONE = 0, SHIP = 1 };

// Object type
enum EntityType: uint16_t { TERRAIN = 0, PLAYER = 1, ENEMY = 2 };

// Object movement direction
enum Direction: uint8_t { RIGHT = 0, LEFT = 1 };

// Object animation identificators
enum ShipAnimation: uint16_t { STRAIGHT_FLIGHT = 0, TURNING_LEFT = 1, TURNING_RIGHT = 2, ASCENDING = 3, DESCENDING = 4 };

// Others
constexpr bool DEBUG = true;                                                     // Debug mode.
constexpr int FPS = 30;                                                          // Frames per second.
constexpr int MILLISECONDS_PER_TICK = 16;                                        // Game logic frequency in milliseconds. 16ms ≈ 60 ticks per second.
constexpr float ZOOM = 2.0f;                                                     // Game display zoom.
constexpr const char *WINDOW_TITLE = "Zaxxon";                                   // Title to show in the application window bar.
constexpr const char *ENTITIES_DATA_FILENAME = "entities.dat";                   // The data file where entity animations and collision areas are defined.