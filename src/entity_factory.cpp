#include <entity_factory.h>
#include <entity_sprite_sheet.h>
#include <map>

EntityFactory::EntityFactory(GameManager* _gameManager, EntityDataManager* _textureManager) {
	gameManager = _gameManager;
	textureManager = _textureManager;
	RegisterEntities();
}

void EntityFactory::RegisterEntities() {
	Register(EntityIdentificator::SHIP, &Ship::Create);
	Register(EntityIdentificator::FUEL_TANK, &FuelTank::Create);
	Register(EntityIdentificator::RADAR_TOWER, &RadarTower::Create);
	Register(EntityIdentificator::GUN_VERTICAL, &GunVertical::Create);
	Register(EntityIdentificator::GUN_HORIZONTAL_NORTH, &GunHorizontalNorth::Create);
	Register(EntityIdentificator::GUN_HORIZONTAL_SOUTH, &GunHorizontalSouth::Create);
	Register(EntityIdentificator::PARKED_PLANE, &ParkedPlane::Create);
	Register(EntityIdentificator::CUBE_BACK, &CubeBack::Create);
	Register(EntityIdentificator::CUBE_FRONT, &CubeFront::Create);
	Register(EntityIdentificator::CUBE_BACK_VERTICAL, &CubeBackVertical::Create);
	Register(EntityIdentificator::CUBE_FRONT_VERTICAL, &CubeFrontVertical::Create);
	Register(EntityIdentificator::CUBE_BACK_HORIZONTAL, &CubeBackHorizontal::Create);
	Register(EntityIdentificator::CUBE_FRONT_HORIZONTAL, &CubeFrontHorizontal::Create);
	Register(EntityIdentificator::CUBE_SHIP_BACK, &CubeShipBack::Create);
	Register(EntityIdentificator::CUBE_SHIP_FRONT, &CubeShipFront::Create);
}

EntityFactory &EntityFactory::operator=(const EntityFactory &) {
	return *this;
}

EntityFactory::~EntityFactory() {
	entityFactoryMap.clear();
}

void EntityFactory::Register(const EntityIdentificator entityId, const CreateEntityFn pfnCreate)
{
	entityFactoryMap[entityId] = pfnCreate;
}

std::optional<IEntity*> EntityFactory::CreateEntity(const EntityIdentificator entityId) const
{
	EntityFactoryMap::const_iterator it = entityFactoryMap.find(entityId);
	if( it != entityFactoryMap.end() ) {
		IEntity *entity = it->second();
		std::optional<EntitySpriteSheet *> entitySpriteSheet = textureManager->GetSpriteSheetByEntityIdentificator(entity->Id());
		assert(entitySpriteSheet != std::nullopt);
		entity->SetGameManager(gameManager);
		entity->InitWithSpriteSheet(*entitySpriteSheet);
		return entity;
	}

	return std::nullopt;
}

EntityFactory *EntityFactory::Get(GameManager* _gameManager, EntityDataManager* _textureManager)
{
	static EntityFactory instance(_gameManager, _textureManager);
	return &instance;
}
