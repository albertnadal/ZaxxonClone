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

void RadarTower::Hit() {
        if(!isExploding) {
                RemoveFromSpacePartitionObjectsTree();
                isExploding = true;
                LoadAnimationWithId(RadarTowerAnimation::RADAR_TOWER_EXPLODING);  // The object will be marked to delete once the animation finishes
        }
}

bool RadarTower::ShouldBeginAnimationLoopAgain() {
    if (isExploding) {
        isMarkedToDelete = true;
    }

    return false;
}

void RadarTower::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(RadarTowerAnimation::RADAR_TOWER_QUIET);
}

IEntity* RadarTower::Create() {
        return new RadarTower();
}

RadarTower::~RadarTower() = default;