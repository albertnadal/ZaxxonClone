#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <map>
#include <optional>
#include <entity.h>
#include <game_manager.h>
#include <entity_data_manager.h>
#include <entities/ship.h>
#include <entities/fuel_tank.h>
#include <entities/radar_tower.h>
#include <entities/gun_emplacement_ver.h>

class GameManager;

class EntityFactory
{
private:
  EntityFactory(GameManager*, EntityDataManager*);
  EntityFactory &operator=(const EntityFactory &);
  void RegisterEntities();
  typedef std::map<EntityIdentificator, CreateEntityFn> EntityFactoryMap;
  EntityFactoryMap entityFactoryMap;
  GameManager *gameManager = nullptr;
  EntityDataManager *textureManager = nullptr;
public:
	~EntityFactory();
	static EntityFactory *Get(GameManager*, EntityDataManager*);
	void Register(const EntityIdentificator, CreateEntityFn);
	std::optional<IEntity*> CreateEntity(const EntityIdentificator) const;
};

#endif
