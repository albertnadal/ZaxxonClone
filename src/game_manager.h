#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <optional>
#include <entity_factory.h>
#include <entities/ship.h>
#include <entity_data_manager.h>
#include <sprite_rect_buffer.h>
#include <aabbcc/AABB.h>
#include <utils.h>

class Ship;

struct UpdateInfo { Position cameraPosition; int lifeCounter; bool gameFinished; };
struct LevelInfo { Texture2D bgTexture; Rectangle bgSource; Position bgPosition; };

class GameManager
{
  aabb::Tree<IEntity*> *spacePartitionObjectsTree = nullptr;
  std::map<uint32_t, IEntity*> mobileObjects;
  std::map<uint32_t, IEntity*> staticObjects;
  std::vector<IEntity*> objectsToDelete;
  Ship* ship = nullptr;
  int lifeCounter = 1;
  bool isGameFinished = false;
  bool isGameOver = false;
  EntityDataManager *textureManager;
  SpriteRectBuffer *spriteRectBuffer;
  uint32_t maxObjects;
  Position cameraPosition;
  Position shipRespawnPosition;
  float currentLevelZPosition;
  LevelInfo LoadLevelFromFile(const std::string&);
  void resetLevelValues();
  void deleteUneededObjects();
  void deleteAllObjects();
  void updateEntities(std::map<uint32_t, IEntity*>&, std::optional<uint8_t>);
  void updateMobileObjects(uint8_t);
  void updateStaticObjects();
  void updateSpriteRectBuffers();
public:
  GameManager(EntityDataManager*, SpriteRectBuffer*, uint32_t);
  ~GameManager();
  LevelInfo LoadLevel();
  UpdateInfo Update(uint8_t);
  std::optional<IEntity *> CreateEntityWithId(EntityIdentificator, Position);
  std::optional<Position *> GetPlayerPosition() const; // TODO: To be removed
};

#endif
