#ifndef PLAYER_H
#define PLAYER_H

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
  void UpdatePreviousDirection();
  void GetSolidCollisions(std::vector<ObjectCollision>&, bool&);

  // Ship action update functions
  void UpdateCollisions();
  void MoveTo(Direction);

public:
  Ship();
  ~Ship() override;
  void InitWithSpriteSheet(EntitySpriteSheet*) override;
  void PrintName() const override;
  bool Update(uint8_t) override;
  bool ShouldBeginAnimationLoopAgain() override;
  static IEntity* Create();

  // state machine triggers
  void RightKeyPressed();
  void RightKeyReleased();
  void LeftKeyPressed();
  void LeftKeyReleased();

private:
  // state machine state functions
  void STATE_Straight_Flight();

  // state map to define state function order
  BEGIN_STATE_MAP
      STATE_MAP_ENTRY(&Ship::STATE_Straight_Flight)
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum ShipStateIdentificator {
      STATE_STRAIGHT_FLIGHT = 0, // Initial state
      SHIP_MAX_STATES
  };
};

#endif
