#include <entities/gun_hor_south.h>
#include <chrono>

GunHorizontalSouth::GunHorizontalSouth() :
        IEntity(EntityIdentificator::GUN_HORIZONTAL_SOUTH, EntityType::ENEMY, GunHorizontalSouthStateIdentificator::GUN_HORIZONTAL_SOUTH_MAX_STATES) {
}

GunHorizontalSouth::GunHorizontalSouth(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void GunHorizontalSouth::PrintName() const {
        std::cout << "Gun Horizontal South." << std::endl;
}

bool GunHorizontalSouth::Update(uint8_t pressedKeys_) {
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

void GunHorizontalSouth::Hit() {
        if(!isExploding) {
                RemoveFromSpacePartitionObjectsTree();
                isExploding = true;
                LoadAnimationWithId(GunHorizontalSouthAnimation::GUN_HORIZONTAL_SOUTH_EXPLODING);  // The object will be marked to delete once the animation finishes
        }
}

bool GunHorizontalSouth::ShouldBeginAnimationLoopAgain() {
    if (isExploding) {
        isMarkedToDelete = true;
        CreateRune();
    }

    return false;
}

void GunHorizontalSouth::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(GunHorizontalSouthAnimation::GUN_HORIZONTAL_SOUTH_QUIET);
}

IEntity* GunHorizontalSouth::Create() {
        return new GunHorizontalSouth();
}

GunHorizontalSouth::~GunHorizontalSouth() = default;