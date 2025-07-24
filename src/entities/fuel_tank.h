#ifndef FUEL_TANK_H
#define FUEL_TANK_H

#include <iostream>
#include <vector>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <position.h>
#include <defines.h>

using namespace std;

class FuelTank: public IEntity
{
  // Action states
  bool isExploding = false;            // The fuel tank is exploding

public:
  FuelTank(EntityIdentificator, EntityType, unsigned char);
  FuelTank();
  ~FuelTank() override;
  virtual void InitWithSpriteSheet(EntitySpriteSheet*) override;
  virtual void PrintName() const override;
  bool Update(uint8_t) override;
  void Hit() override;
  bool ShouldBeginAnimationLoopAgain() override;
  static IEntity* Create();

private:
  // state map to define state function order
  BEGIN_STATE_MAP
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum FuelTankStateIdentificator {
      FUEL_TANK_MAX_STATES
  };
};

#endif
