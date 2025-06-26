#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <optional>
#include <entity_factory.h>
#include <entities/ship.h>
#include <entity_data_manager.h>
#include <sprite_rect_double_buffer.h>
#include <utils.h>

class Ship;

struct UpdateInfo { int lifeCounter; bool gameFinished; };

class GameManager
{
  std::map<uint32_t, IEntity*> mobileObjects;
  std::map<uint32_t, IEntity*> staticObjects;
  std::vector<IEntity*> objectsToDelete;
  Ship* ship = nullptr;
  int lifeCounter = 1; //MAX_PLAYER_LIFES;
  bool isGameFinished = false;
  bool isGameOver = false;
  EntityDataManager *textureManager;
  SpriteRectDoubleBuffer *spriteRectDoubleBuffer;
  uint32_t maxObjects;
  void LoadLevelFromFile(const std::string&);
  float newCameraVerticalPosition;
  float currentCameraVerticalPosition;
  std::vector<int> validAltitudes = {84, 78, 72, 66, 60}; // Altitudes of levels 4, 5, 6, 7 and 8. Are multiple of six.
  void deleteUneededObjects();
  void deleteAllObjects();
  void updateEntities(std::map<uint32_t, IEntity*>&, std::optional<uint8_t>);
  void updateMobileObjects(uint8_t);
  void updateStaticObjects();
  void updateSpriteRectBuffers();
public:
  GameManager(EntityDataManager*, SpriteRectDoubleBuffer*, uint32_t);
  ~GameManager();
  void LoadLevel();
  UpdateInfo Update(uint8_t);
  std::optional<IEntity *> CreateEntityWithId(EntityIdentificator, int, int, int);
  std::optional<Position *> GetPlayerPosition() const;
};

#endif
