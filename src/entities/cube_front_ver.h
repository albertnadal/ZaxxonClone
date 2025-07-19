#ifndef CUBE_FRONT_VER_H
#define CUBE_FRONT_VER_H

#include <iostream>
#include <vector>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <position.h>
#include <defines.h>

using namespace std;

class CubeFrontVertical: public IEntity
{
public:
  CubeFrontVertical(EntityIdentificator, EntityType, unsigned char);
  CubeFrontVertical();
  virtual void InitWithSpriteSheet(EntitySpriteSheet*) override;
  virtual void PrintName() const override;
  bool Update(uint8_t) override;
  static IEntity* Create();

private:
  // state machine state functions
  virtual void STATE_Quiet();

  // state map to define state function order
  BEGIN_STATE_MAP
      STATE_MAP_ENTRY(&CubeFrontVertical::STATE_Quiet)
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum CubeFrontVerticalStateIdentificator {
      STATE_QUIET = 0, // Initial state
      CUBE_FRONT_VERTICAL_MAX_STATES
  };
};

#endif
