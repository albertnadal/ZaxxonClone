#ifndef CUBE_SHIP_FRONT_H
#define CUBE_SHIP_FRONT_H

#include <iostream>
#include <vector>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <position.h>
#include <defines.h>

using namespace std;

class CubeShipFront: public IEntity
{
public:
  CubeShipFront(EntityIdentificator, EntityType, unsigned char);
  CubeShipFront();
  virtual void InitWithSpriteSheet(EntitySpriteSheet*) override;
  virtual void PrintName() const override;
  bool Update(uint8_t) override;
  static IEntity* Create();

private:
  // state machine state functions
  virtual void STATE_Quiet();

  // state map to define state function order
  BEGIN_STATE_MAP
      STATE_MAP_ENTRY(&CubeShipFront::STATE_Quiet)
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum CubeShipFrontStateIdentificator {
      STATE_QUIET = 0, // Initial state
      CUBE_SHIP_FRONT_MAX_STATES
  };
};

#endif
