#ifndef SHIP_SHADOW_H
#define SHIP_SHADOW_H

#include <iostream>
#include <vector>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <position.h>
#include <defines.h>

using namespace std;

class ShipShadow: public IEntity
{
public:
  ShipShadow(EntityIdentificator, EntityType, unsigned char);
  ShipShadow();
  ~ShipShadow() override;
  virtual void InitWithSpriteSheet(EntitySpriteSheet*) override;
  virtual void PrintName() const override;
  bool Update(uint8_t) override;
  static IEntity* Create();

private:
  // state map to define state function order
  BEGIN_STATE_MAP
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum ShipShadowStateIdentificator {
      SHIP_SHADOW_MAX_STATES
  };
};

#endif
