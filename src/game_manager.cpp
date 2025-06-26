#include <game_manager.h>
#include <entity_factory.h>
#include <entity.h>
#include <fstream>
#include <sstream>

GameManager::GameManager(EntityDataManager* _textureManager, SpriteRectDoubleBuffer* _spriteRectDoubleBuffer, uint32_t _maxObjects) {
        textureManager = _textureManager;
        spriteRectDoubleBuffer = _spriteRectDoubleBuffer;
        maxObjects = _maxObjects;
}

void GameManager::LoadLevel() {
  LoadLevelFromFile(LEVEL_FILENAME);
}

void GameManager::LoadLevelFromFile(const std::string& filename) {
    std::ifstream file(filename);
    assert(file.is_open() && "Error: Unable to open file with level data.");

    std::string segmentData;
    int segmentNumber = 0;

    while (std::getline(file, segmentData)) {
        auto colonPos = segmentData.find(':');
        if (colonPos == std::string::npos) continue;

        std::string segmentName = segmentData.substr(0, colonPos);
        std::cout << "Loading segment: " << segmentName << std::endl;

        std::string entitiesStr = segmentData.substr(colonPos + 1);
        std::stringstream entitiesStream(entitiesStr);
        std::string entityData;

        while (std::getline(entitiesStream, entityData, '|')) {
            std::stringstream ssEntity(entityData);
            std::string entityId, entityX, entityY;
            std::getline(ssEntity, entityId, ',');
            std::getline(ssEntity, entityX, ',');
            std::getline(ssEntity, entityY);

            if (!entityId.empty() && !entityX.empty() && !entityY.empty()) {
                CreateEntityWithId(
                    static_cast<EntityIdentificator>(std::stoi(entityId)),
                    std::stoi(entityX),
                    std::stoi(entityY),
                    segmentNumber * SEGMENT_LENGTH
                );
            }
        }
        ++segmentNumber;
    }

    file.close();
}

std::optional<IEntity *> GameManager::CreateEntityWithId(EntityIdentificator entity_id, int x, int y, int z) {
  std::optional<IEntity *> entity_ptr = EntityFactory::Get(this, textureManager)->CreateEntity(entity_id);

  if(entity_ptr.has_value()) {
    if (entity_id == EntityIdentificator::SHIP) {
      ship = static_cast<Ship*>(*entity_ptr);
    }
  }

  return entity_ptr;
}

std::optional<Position *> GameManager::GetPlayerPosition() const {
  if (ship == nullptr) {
    return std::nullopt;
  }

  return &(ship->position);
}

UpdateInfo GameManager::Update(uint8_t pressedKeys) {
  updateMobileObjects(pressedKeys);
  updateStaticObjects();
  updateSpriteRectBuffers();
  deleteUneededObjects();

  UpdateInfo info;
  return info;
}

void GameManager::updateSpriteRectBuffers() {
  /*
  int i = 0;
  std::vector<aabb::AABBIntersection<IEntity*>> objectIntersections = spacePartitionObjectsTree->query(player->GetLowerBound(), player->GetUpperBound());

  for (auto const& x : staticObjects) {
    IEntity* entity_ptr = x.second;
    Rectangle src = { entity_ptr->currentSprite.u1, entity_ptr->currentSprite.v1, entity_ptr->currentSprite.u2, entity_ptr->currentSprite.v2 };
    Vector2 pos = { entity_ptr->position.GetX(), entity_ptr->position.GetY() };
    Boundaries boundaries = entity_ptr->GetAbsoluteBoundaries();
    Boundaries attackBoundaries = entity_ptr->GetAbsoluteAttackBoundaries().value_or(Boundaries{0,0,0,0});
    Color tint = WHITE;

    if (DEBUG) {
      // Tint in RED those objects that are candidates to collide with the ship object.
      auto it = std::find_if(objectIntersections.begin(), objectIntersections.end(),
                            [entity_ptr](const aabb::AABBIntersection<IEntity*>& intersection) {
                                return intersection.particle == entity_ptr;
                            });

      if (it != objectIntersections.end()) {
        tint = RED;
      }
    }

    spriteRectDoubleBuffer->producer_buffer[i++] = SpriteRect(src, pos, boundaries, attackBoundaries, tint);
  }

  for (auto const& x : mobileObjects) {
    IEntity* entity_ptr = x.second;
    Rectangle src = { entity_ptr->currentSprite.u1, entity_ptr->currentSprite.v1, entity_ptr->currentSprite.u2, entity_ptr->currentSprite.v2 };
    Vector2 pos = { entity_ptr->position.GetX(), entity_ptr->position.GetY() };
    Boundaries boundaries = entity_ptr->GetAbsoluteBoundaries();
    Boundaries attackBoundaries = entity_ptr->GetAbsoluteAttackBoundaries().value_or(Boundaries{0,0,0,0});
    spriteRectDoubleBuffer->producer_buffer[i] = SpriteRect(src, pos, boundaries, attackBoundaries, WHITE);
    i++;
  }

  spriteRectDoubleBuffer->producer_buffer_length = i;
  spriteRectDoubleBuffer->swapBuffers();
  */
}

void GameManager::updateEntities(std::map<uint32_t, IEntity*>& objects, std::optional<uint8_t> pressedKeys = std::nullopt) {
    for (auto const& x : objects) {
        IEntity* entity_ptr = x.second;

        if (entity_ptr->isMarkedToDelete) {
            objectsToDelete.push_back(entity_ptr);
            continue;
        }

        if (pressedKeys.has_value()) {
            entity_ptr->Update(pressedKeys.value());
        } else {
            entity_ptr->Update();
        }
    }
}

void GameManager::updateMobileObjects(uint8_t pressedKeys) {
    updateEntities(mobileObjects, pressedKeys);
}

void GameManager::updateStaticObjects() {
    updateEntities(staticObjects);
}

void GameManager::deleteUneededObjects() {
  for (auto entity_ptr : objectsToDelete) {
    staticObjects.erase(entity_ptr->uniqueId);
    mobileObjects.erase(entity_ptr->uniqueId);
    delete entity_ptr;
  }

  objectsToDelete.clear();
}

void GameManager::deleteAllObjects() {
  // Mark the Ship instance to delete.
  if (ship != nullptr) {
    ship->isMarkedToDelete = true;
    ship = nullptr;
  }

  // Delete all instances marked to delete.
  deleteUneededObjects();
  mobileObjects.clear();

  // Delete static object instances.
  for (auto& pair : staticObjects) {
    delete pair.second;
  }
  staticObjects.clear();
}

GameManager::~GameManager() {
  deleteAllObjects();
}
