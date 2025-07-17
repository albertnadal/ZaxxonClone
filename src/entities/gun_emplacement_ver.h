#ifndef GUN_EMPLACEMENT_VER_H
#define GUN_EMPLACEMENT_VER_H

#include <iostream>
#include <vector>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <position.h>
#include <defines.h>

using namespace std;

class GunEmplacementVertical: public IEntity
{
  bool isExploding = false;

public:
  GunEmplacementVertical(EntityIdentificator, EntityType, unsigned char);
  GunEmplacementVertical();
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
      STATE_MAP_ENTRY(&GunEmplacementVertical::STATE_Quiet)
      STATE_MAP_ENTRY(&GunEmplacementVertical::STATE_Exploding)
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum GunEmplacementVerticalStateIdentificator {
      STATE_QUIET = 0, // Initial state
      STATE_EXPLODING,
      GUN_EMPLACEMENT_VERTICAL_MAX_STATES
  };
};

#endif
