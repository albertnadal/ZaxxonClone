#ifndef CUBE_BACK_H
#define CUBE_BACK_H

#include <iostream>
#include <vector>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <position.h>
#include <defines.h>

using namespace std;

class CubeBack: public IEntity
{
  bool isExploding = false;

public:
  CubeBack(EntityIdentificator, EntityType, unsigned char);
  CubeBack();
  virtual void InitWithSpriteSheet(EntitySpriteSheet*) override;
  virtual void PrintName() const override;
  bool Update(uint8_t) override;
  static IEntity* Create();

private:
  // state machine state functions
  virtual void STATE_Quiet();

  // state map to define state function order
  BEGIN_STATE_MAP
      STATE_MAP_ENTRY(&CubeBack::STATE_Quiet)
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum CubeBackStateIdentificator {
      STATE_QUIET = 0, // Initial state
      CUBE_BACK_MAX_STATES
  };
};

#endif
