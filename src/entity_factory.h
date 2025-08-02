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
#include <entities/gun_ver.h>
#include <entities/gun_hor_north.h>
#include <entities/gun_hor_south.h>
#include <entities/parked_plane.h>
#include <entities/laser_bolt_green.h>
#include <entities/enemy_rune.h>
#include <entities/ship_shadow.h>
#include <aabbcc/AABB.h>

class GameManager;

class EntityFactory
{
private:
  EntityFactory(GameManager*, EntityDataManager*, aabb::Tree<IEntity*>*);
  EntityFactory &operator=(const EntityFactory &);
  void RegisterEntities();
  typedef std::map<EntityIdentificator, CreateEntityFn> EntityFactoryMap;
  EntityFactoryMap entityFactoryMap;
  GameManager *gameManager = nullptr;
  EntityDataManager *textureManager = nullptr;
  aabb::Tree<IEntity*> *spacePartitionObjectsTree = nullptr;
public:
	~EntityFactory();
	static EntityFactory *Get(GameManager*, EntityDataManager*, aabb::Tree<IEntity*>*);
	void Register(const EntityIdentificator, CreateEntityFn);
	std::optional<IEntity*> CreateEntity(const EntityIdentificator) const;
};

#endif
