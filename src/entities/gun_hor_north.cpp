#include <entities/gun_hor_north.h>
#include <chrono>

GunHorizontalNorth::GunHorizontalNorth() :
        IEntity(EntityIdentificator::GUN_HORIZONTAL_NORTH, EntityType::ENEMY, GunHorizontalNorthStateIdentificator::GUN_HORIZONTAL_NORTH_MAX_STATES) {
}

GunHorizontalNorth::GunHorizontalNorth(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void GunHorizontalNorth::PrintName() const {
        std::cout << "Gun Horizontal North." << std::endl;
}

bool GunHorizontalNorth::Update(uint8_t pressedKeys_) {
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

void GunHorizontalNorth::Hit() {
        if(!isExploding) {
                RemoveFromSpacePartitionObjectsTree();
                isExploding = true;
                LoadAnimationWithId(GunHorizontalNorthAnimation::GUN_HORIZONTAL_NORTH_EXPLODING);  // The object will be marked to delete once the animation finishes
        }
}

bool GunHorizontalNorth::ShouldBeginAnimationLoopAgain() {
    if (isExploding) {
        isMarkedToDelete = true;
    }

    return false;
}

void GunHorizontalNorth::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(GunHorizontalNorthAnimation::GUN_HORIZONTAL_NORTH_QUIET);
}

IEntity* GunHorizontalNorth::Create() {
        return new GunHorizontalNorth();
}

GunHorizontalNorth::~GunHorizontalNorth() = default;