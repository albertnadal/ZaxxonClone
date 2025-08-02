#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>
#include <optional>
#include <chrono>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <collision/collision.h>
#include <algorithm>
#include <defines.h>

using namespace std;

class Ship: public IEntity
{
  uint8_t prevPressedKeys = KeyboardKeyCode::Z_KEY_NONE;
  uint8_t pressedKeys = KeyboardKeyCode::Z_KEY_NONE;
  void ProcessPressedKeys(bool = true);
  void ProcessReleasedKeys();
  void LoadNextSprite();

  // Action states
  bool isExploding = false;
  bool isNotVisible = false;

  // Ship action update functions
  void UpdateCollisions();
  void MoveToXAxis(Direction);
  void MoveToYAxis(Direction, bool);
  void FireLaserBolt();

public:
  Ship();
  ~Ship() override;
  void InitWithSpriteSheet(EntitySpriteSheet*) override;
  void PrintName() const override;
  bool Update(uint8_t) override;
  bool ShouldBeginAnimationLoopAgain() override;
  static IEntity* Create();

  // state machine triggers
  void UpKeyPressed();
  void UpKeyReleased();
  void DownKeyPressed();
  void DownKeyReleased();
  void Explode();
  void MakeNotVisible();

private:
  // state machine state functions
  void STATE_Straight_Flight();
  void STATE_Ascending();
  void STATE_Descending();
  void STATE_Exploding();
  void STATE_Not_Visible();

  // state map to define state function order
  BEGIN_STATE_MAP
      STATE_MAP_ENTRY(&Ship::STATE_Straight_Flight)
      STATE_MAP_ENTRY(&Ship::STATE_Ascending)
      STATE_MAP_ENTRY(&Ship::STATE_Descending)
      STATE_MAP_ENTRY(&Ship::STATE_Exploding)
      STATE_MAP_ENTRY(&Ship::STATE_Not_Visible)
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum ShipStateIdentificator {
      STATE_STRAIGHT_FLIGHT = 0, // Initial state
      STATE_ASCENDING = 1,
      STATE_DESCENDING = 2,
      STATE_EXPLODING = 3,
      STATE_NOT_VISIBLE = 4,
      SHIP_MAX_STATES
  };
};

#endif
