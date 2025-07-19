#ifndef CUBE_FRONT_HOR_H
#define CUBE_FRONT_HOR_H

#include <iostream>
#include <vector>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <position.h>
#include <defines.h>

using namespace std;

class CubeFrontHorizontal: public IEntity
{
public:
  CubeFrontHorizontal(EntityIdentificator, EntityType, unsigned char);
  CubeFrontHorizontal();
  virtual void InitWithSpriteSheet(EntitySpriteSheet*) override;
  virtual void PrintName() const override;
  bool Update(uint8_t) override;
  static IEntity* Create();

private:
  // state machine state functions
  virtual void STATE_Quiet();

  // state map to define state function order
  BEGIN_STATE_MAP
      STATE_MAP_ENTRY(&CubeFrontHorizontal::STATE_Quiet)
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum CubeFrontHorizontalStateIdentificator {
      STATE_QUIET = 0, // Initial state
      CUBE_FRONT_HORIZONTAL_MAX_STATES
  };
};

#endif
