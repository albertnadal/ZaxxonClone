#include <cassert>
#include <entity.h>
#include <collision/collision.h>

IEntity::IEntity() {
  id = EntityIdentificator::NONE;
  boundingBox = solidBoundingBox = {0, 0, 0, 0};
  isMarkedToDelete = false;
}

IEntity::IEntity(EntityIdentificator _id, EntityType _type, unsigned char _maxStates) :
  StateMachine(_maxStates),
  id(_id),
  type(_type) {
  boundingBox = solidBoundingBox = {0, 0, 0, 0};
  vectorDirection.x = 0;
  vectorDirection.y = 0;
}

void IEntity::SetGameManager(GameManager *_gameManager) {
  gameManager = _gameManager;
}

void IEntity::PositionSetXYZ(float x, float y, float z) {
  position.SetXYZ(x, y, z);
}

void IEntity::PositionAddX(float x) {
  position.AddX(x);
}

void IEntity::LoadAnimationWithId(uint16_t animationId) {
    std::optional<EntitySpriteSheetAnimation *> currentAnimation = spriteSheet->GetAnimationWithId(animationId);
    assert(currentAnimation != std::nullopt);
    currentAnimationSprites = (*currentAnimation)->GetSprites();
    animationHasOnlyOneSprite = (currentAnimationSprites.size() <= 1);
    currentAnimationSpriteIterator = std::begin(currentAnimationSprites);
    animationLoaded = true;
    firstSpriteOfCurrentAnimationIsLoaded = false;
    nextSpriteTime = std::chrono::system_clock::now();
}

void IEntity::LoadNextSprite()
{
  SpriteData spriteData = NextSpriteData();
  if(spriteData.beginNewLoop) {
          if(ShouldBeginAnimationLoopAgain()) {
            spriteData = NextSpriteData();
          }
  }

  nextSpriteTime = (chrono::system_clock::now() + std::chrono::milliseconds(spriteData.duration));

  currentSprite.width = spriteData.width;
  currentSprite.height = spriteData.height;
  currentSprite.xOffset = spriteData.xOffset;
  currentSprite.yOffset = spriteData.yOffset;
  currentSprite.u1 = spriteData.u1;
  currentSprite.v1 = spriteData.v1;
  currentSprite.u2 = spriteData.u2;
  currentSprite.v2 = spriteData.v2;
  boundingBox = { spriteData.lowerBoundX, spriteData.lowerBoundY, spriteData.upperBoundX, spriteData.upperBoundY };
  firstSpriteOfCurrentAnimationIsLoaded = true;
}

SpriteData IEntity::NextSpriteData() {
    if (currentAnimationSpriteIterator == std::end(currentAnimationSprites)) {
        currentAnimationSpriteIterator = std::begin(currentAnimationSprites);
        (*currentAnimationSpriteIterator).beginNewLoop = true;
    }

    return *currentAnimationSpriteIterator++;
}

inline bool IEntity::ReachedScreenEdge() const {
    return false;
}

bool IEntity::ShouldBeginAnimationLoopAgain()
{
    return false;
}

Boundaries IEntity::GetAbsoluteBoundaries() const {
  return {static_cast<int>(position.GetProjectedX()) + boundingBox.upperBoundX,
          static_cast<int>(position.GetProjectedY()) + boundingBox.upperBoundY,
          static_cast<int>(position.GetProjectedX()) + boundingBox.lowerBoundX,
          static_cast<int>(position.GetProjectedY()) + boundingBox.lowerBoundY};
}

EntityIdentificator IEntity::Id() const {
  return id;
}

EntityType IEntity::Type() const {
  return type;
}

inline int IEntity::Width() const {
  return currentSprite.width;
}

inline int IEntity::Height() const {
  return currentSprite.height;
}

void IEntity::PrintName() const {
  std::cout << "PrintName not overloaded for object." << std::endl;
}

void IEntity::UpdatePositionInSpacePartitionTree() {
    //std::vector<int> lowerBound = GetLowerBound();
    //std::vector<int> upperBound = GetUpperBound();
}

bool IEntity::Update() {
  return Update(KeyboardKeyCode::Z_KEY_NONE);
}

bool IEntity::Update(const uint8_t pressedKeys) {
  return false;
}

void IEntity::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
  spriteSheet = _spriteSheet;
}

void IEntity::Hit(bool) {
}
