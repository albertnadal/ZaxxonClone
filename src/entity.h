#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <chrono>
#include <position.h>
#include <defines.h>
#include <entity_sprite_sheet.h>
#include <sprite.h>
#include <state_machine.h>
#include <aabbcc/AABB.h>

using namespace std;

class IEntity;
class GameManager;

struct Boundaries { int lX, lY, lZ, uX, uY, uZ; };
struct ProjectedBoundaries { Vector2 a, b, c, d, e, f, g, h; };
struct ObjectCollision { IEntity* object; int horizontalCorrection; int verticalCorrection; };

class IEntity : public StateMachine
{
protected:
  GameManager *gameManager = nullptr;
  aabb::Tree<IEntity*> *spacePartitionObjectsTree = nullptr;
  std::vector<SpriteData> currentAnimationSprites;
  std::vector<SpriteData>::iterator currentAnimationSpriteIterator;
  EntitySpriteSheet *spriteSheet = nullptr;
  chrono::system_clock::time_point nextSpriteTime;
  bool animationLoaded = false;
  bool firstSpriteOfCurrentAnimationIsLoaded = false;
  bool animationHasOnlyOneSprite = false;
  void LoadAnimationWithId(uint16_t);
  void LoadNextSprite();
  SpriteData NextSpriteData();
  void CreateRune() const;
public:
  IEntity();
  IEntity(EntityIdentificator, EntityType, unsigned char);
  EntityIdentificator id;
  EntityType type;
  Sprite currentSprite;
  Position position;
  Boundaries boundingBox;
  Boundaries solidBoundingBox;
  uint32_t uniqueId;
  bool isMarkedToDelete = false;
  void SetGameManager(GameManager*);
  void SetSpacePartitionObjectsTree(aabb::Tree<IEntity*>*);
  void PositionSetXYZ(float, float, float);
  void PositionSetX(float);
  void PositionSetY(float);
  void PositionAddX(float);
  void PositionAddY(float);
  void RemoveFromSpacePartitionObjectsTree();
  std::vector<int> GetLowerBound() const;
  std::vector<int> GetUpperBound() const;
  ProjectedBoundaries GetProjectedBoundaries() const;
  Vector2 GetRightmostProjectedCoordinate() const;
  EntityIdentificator Id() const;
  EntityType Type() const;
  int Width() const;
  int Height() const;
  virtual void InitWithSpriteSheet(EntitySpriteSheet*);
  virtual void PrintName() const;
  virtual bool Update();
  virtual bool Update(const uint8_t);
  virtual void UpdatePositionInSpacePartitionTree();
  virtual void Hit();
  virtual bool ShouldBeginAnimationLoopAgain();
};

typedef IEntity* (*CreateEntityFn)(void);

#endif
