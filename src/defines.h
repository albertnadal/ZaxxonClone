#pragma once

#include <cstdint>
#include <raylib/raylib.h>

// Keyboard key codes
enum KeyboardKeyCode: uint8_t { Z_KEY_LEFT = 0x80, Z_KEY_UP = 0x40, Z_KEY_RIGHT = 0x20, Z_KEY_DOWN = 0x10, Z_KEY_ESCAPE = 0x08, Z_KEY_PAUSE = 0x04, Z_KEY_ENTER = 0x02, Z_KEY_SPACE = 0x01, Z_KEY_NONE = 0x00 };

// Object identificators
enum EntityIdentificator: uint16_t { NONE = 0, SHIP = 1, FUEL_TANK = 2, RADAR_TOWER = 3, GUN_VERTICAL= 4, GUN_HORIZONTAL_NORTH = 5, GUN_HORIZONTAL_SOUTH = 6 };

// Object type
enum EntityType: uint16_t { TERRAIN = 0, PLAYER = 1, ENEMY = 2 };

// Object movement direction
enum Direction: uint8_t { RIGHT = 0, LEFT = 1, UP = 2, DOWN = 3 };

// Object animation identificators
enum ShipAnimation: uint16_t { STRAIGHT_FLIGHT = 0, ASCENDING = 1, DESCENDING = 2 };
enum FuelTankAnimation: uint16_t { FUEL_TANK_QUIET = 3, FUEL_TANK_EXPLODING = 4 };
enum RadarTowerAnimation: uint16_t { RADAR_TOWER_QUIET = 5, RADAR_TOWER_EXPLODING = 6 };
enum GunVerticalAnimation: uint16_t { GUN_VERTICAL_QUIET = 7, GUN_VERTICAL_EXPLODING = 8 };
enum GunHorizontalNorthAnimation: uint16_t { GUN_HORIZONTAL_NORTH_QUIET = 9, GUN_HORIZONTAL_NORTH_EXPLODING = 10 };
enum GunHorizontalSouthAnimation: uint16_t { GUN_HORIZONTAL_SOUTH_QUIET = 11, GUN_HORIZONTAL_SOUTH_EXPLODING = 12 };

// Others
constexpr bool DEBUG = true;                                                     // Debug mode.
constexpr int MILLISECONDS_PER_TICK = 16;                                        // Game logic frequency in milliseconds. 16ms ≈ 60 ticks per second ≈ 60 frames per second.
constexpr float ZOOM = 3.0f;                                                     // Game display zoom.
constexpr const char *WINDOW_TITLE = "Zaxxon Clone";                             // Title to show in the application window bar.
constexpr const char *ENTITIES_DATA_FILENAME = "entities.dat";                   // The data file where entity animations and collision areas are defined.
constexpr int LEVEL_WIDTH = 100;                                                 // Width of the level.
constexpr int LEVEL_HEIGHT = 100;                                                // Height of the level.
constexpr int LEVEL_LENGTH = 10000;                                              // Length of the level.
constexpr int SEGMENT_LENGTH = 5;                                                // Space between segments in the level.
constexpr const char *LEVEL_FILENAME = "level.dat";                              // The file where the level is defined.
constexpr float ADVANCE_Z_DELTA = 0.7f;                                          // Delta to advance the level in the Z axis per frame.