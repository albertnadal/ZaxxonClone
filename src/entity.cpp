#include <cassert>
#include <entity.h>
#include <collision/collision.h>
#include <MersenneTwister/MersenneTwister.h>

static MersenneTwister rng;

IEntity::IEntity() {
  id = EntityIdentificator::NONE;
  uniqueId = rng.integer(0, UINT_MAX);
  boundingBox = solidBoundingBox = {0, 0, 0, 0};
  isMarkedToDelete = false;
}

IEntity::IEntity(EntityIdentificator _id, EntityType _type, unsigned char _maxStates) :
  StateMachine(_maxStates),
  id(_id),
  type(_type) {
  uniqueId = rng.integer(0, UINT_MAX);
  boundingBox = solidBoundingBox = {0, 0, 0, 0};
}

void IEntity::SetGameManager(GameManager *_gameManager) {
  gameManager = _gameManager;
}

void IEntity::SetSpacePartitionObjectsTree(aabb::Tree<IEntity*> *_spacePartitionObjectsTree) {
  spacePartitionObjectsTree = _spacePartitionObjectsTree;
}

void IEntity::PositionSetXYZ(float x, float y, float z) {
  position.SetXYZ(x, y, z);
}

void IEntity::PositionAddX(float x) {
  position.AddX(x);
}

void IEntity::PositionAddY(float y) {
  position.AddY(y);
}

std::vector<int> IEntity::GetLowerBound() const {
  Vector3 coord = position.GetCoordinates();
  return {static_cast<int>(coord.x) + boundingBox.lX, static_cast<int>(coord.y) + boundingBox.lY, static_cast<int>(coord.z) + boundingBox.lZ};
}

std::vector<int> IEntity::GetUpperBound() const {
  Vector3 coord = position.GetCoordinates();
  return {static_cast<int>(coord.x) + boundingBox.lX + boundingBox.uX, static_cast<int>(coord.y) + boundingBox.lY + boundingBox.uY, static_cast<int>(coord.z) + boundingBox.lZ + boundingBox.uZ};
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
  if (spriteData.beginNewLoop && !ShouldBeginAnimationLoopAgain()) {
      return;
  }

  if (spriteData.beginNewLoop) {
      spriteData = NextSpriteData();
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
  boundingBox = {spriteData.lowerBoundX, spriteData.lowerBoundY, spriteData.lowerBoundZ, spriteData.upperBoundX, spriteData.upperBoundY, spriteData.upperBoundZ};
  firstSpriteOfCurrentAnimationIsLoaded = true;
}

SpriteData IEntity::NextSpriteData() {
    if (currentAnimationSpriteIterator == std::end(currentAnimationSprites)) {
        currentAnimationSpriteIterator = std::begin(currentAnimationSprites);
        (*currentAnimationSpriteIterator).beginNewLoop = true;
    }

    return *currentAnimationSpriteIterator++;
}

void IEntity::RemoveFromSpacePartitionObjectsTree() {
  spacePartitionObjectsTree->removeParticle(this);
}

inline bool IEntity::ReachedScreenEdge() const {
    return false;
}

bool IEntity::ShouldBeginAnimationLoopAgain()
{
    return false;
}

ProjectedBoundaries IEntity::GetProjectedBoundaries() const {
  Vector2 a = Position::AddAndGetProjectedCoordinate(position, boundingBox.lX, boundingBox.lY, boundingBox.lZ);
  Vector2 b = Position::AddAndGetProjectedCoordinate(position, boundingBox.lX, boundingBox.lY + boundingBox.uY, boundingBox.lZ);
  Vector2 c = Position::AddAndGetProjectedCoordinate(position, boundingBox.lX, boundingBox.lY + boundingBox.uY, boundingBox.lZ + boundingBox.uZ);
  Vector2 d = Position::AddAndGetProjectedCoordinate(position, boundingBox.lX, boundingBox.lY, boundingBox.lZ + boundingBox.uZ);
  Vector2 e = Position::AddAndGetProjectedCoordinate(position, boundingBox.lX + boundingBox.uX, boundingBox.lY, boundingBox.lZ);
  Vector2 f = Position::AddAndGetProjectedCoordinate(position, boundingBox.lX + boundingBox.uX, boundingBox.lY + boundingBox.uY, boundingBox.lZ);
  Vector2 g = Position::AddAndGetProjectedCoordinate(position, boundingBox.lX + boundingBox.uX, boundingBox.lY + boundingBox.uY, boundingBox.lZ + boundingBox.uZ);
  Vector2 h = Position::AddAndGetProjectedCoordinate(position, boundingBox.lX + boundingBox.uX, boundingBox.lY, boundingBox.lZ + boundingBox.uZ);
  return {a, b, c, d, e, f, g, h};
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

void IEntity::Hit() {
}
