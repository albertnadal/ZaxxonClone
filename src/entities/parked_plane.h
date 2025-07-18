#ifndef PARKED_PLANE_H
#define PARKED_PLANE_H

#include <iostream>
#include <vector>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <position.h>
#include <defines.h>

using namespace std;

class ParkedPlane: public IEntity
{
  bool isExploding = false;

public:
  ParkedPlane(EntityIdentificator, EntityType, unsigned char);
  ParkedPlane();
  virtual void InitWithSpriteSheet(EntitySpriteSheet*) override;
  virtual void PrintName() const override;
  bool Update(uint8_t) override;
  void Hit(bool) override;
  static IEntity* Create();

  // state machine triggers
  void Explode();

private:
  // state machine state functions
  virtual void STATE_Quiet();
  virtual void STATE_Exploding();

  // state map to define state function order
  BEGIN_STATE_MAP
      STATE_MAP_ENTRY(&ParkedPlane::STATE_Quiet)
      STATE_MAP_ENTRY(&ParkedPlane::STATE_Exploding)
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum ParkedPlaneStateIdentificator {
      STATE_QUIET = 0, // Initial state
      STATE_EXPLODING,
      PARKED_PLANE_MAX_STATES
  };
};

#endif
