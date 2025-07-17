#include <entities/radar_tower.h>
#include <chrono>

RadarTower::RadarTower() :
        IEntity(EntityIdentificator::RADAR_TOWER, EntityType::ENEMY, RadarTowerStateIdentificator::RADAR_TOWER_MAX_STATES) {
}

RadarTower::RadarTower(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void RadarTower::PrintName() const {
        std::cout << "Radar Tower." << std::endl;
}

bool RadarTower::Update(uint8_t pressedKeys_) {
        if (isMarkedToDelete) {
                return false;
        }

        bool needRedraw = false;

        if(!animationLoaded) {
                return false;
        }

        if(animationHasOnlyOneSprite && firstSpriteOfCurrentAnimationIsLoaded) {
                return false;
        }

        if(chrono::system_clock::now() >= nextSpriteTime) {
                // Load next sprite of the current animation
                LoadNextSprite();
                return true;
        }

        return needRedraw;
}

void RadarTower::Hit(bool propelToRight) {
        //TODO: Implement RemoveFromSpacePartitionObjectsTree();
        Explode();
}

void RadarTower::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(RadarTowerAnimation::RADAR_TOWER_QUIET);
}

IEntity* RadarTower::Create() {
        return new RadarTower();
}

void RadarTower::Explode()
{
        BEGIN_TRANSITION_MAP                            // - Current State -
                TRANSITION_MAP_ENTRY (STATE_EXPLODING)  // STATE_Quiet
                TRANSITION_MAP_ENTRY (EVENT_IGNORED)    // STATE_Exploding
        END_TRANSITION_MAP(NULL)
}

void RadarTower::STATE_Quiet()
{
        LoadAnimationWithId(RadarTowerAnimation::RADAR_TOWER_QUIET);
}

void RadarTower::STATE_Exploding()
{
        LoadAnimationWithId(RadarTowerAnimation::RADAR_TOWER_EXPLODING);
}
