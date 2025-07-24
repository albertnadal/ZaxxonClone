#ifndef LASER_BOLT_GREEN_H
#define LASER_BOLT_GREEN_H

#include <iostream>
#include <vector>
#include <entity.h>
#include <game_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <position.h>
#include <defines.h>

using namespace std;

class LaserBoltGreen: public IEntity
{
public:
  LaserBoltGreen(EntityIdentificator, EntityType, unsigned char);
  LaserBoltGreen();
  ~LaserBoltGreen() override;
  virtual void InitWithSpriteSheet(EntitySpriteSheet*) override;
  virtual void PrintName() const override;
  bool Update(uint8_t) override;
  static IEntity* Create();

  // Laser bold action update functions
  void UpdateCollisions();

private:
  // state map to define state function order
  BEGIN_STATE_MAP
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum LaserBoltGreenStateIdentificator {
      LASER_BOLT_GREEN_MAX_STATES
  };
};

#endif
