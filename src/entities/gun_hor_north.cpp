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

void GunHorizontalNorth::Hit(bool propelToRight) {
        //TODO: Implement RemoveFromSpacePartitionObjectsTree();
        Explode();
}

void GunHorizontalNorth::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(GunHorizontalNorthAnimation::GUN_HORIZONTAL_NORTH_QUIET);
}

IEntity* GunHorizontalNorth::Create() {
        return new GunHorizontalNorth();
}

void GunHorizontalNorth::Explode()
{
        BEGIN_TRANSITION_MAP                            // - Current State -
                TRANSITION_MAP_ENTRY (STATE_EXPLODING)  // STATE_Quiet
                TRANSITION_MAP_ENTRY (EVENT_IGNORED)    // STATE_Exploding
        END_TRANSITION_MAP(NULL)
}

void GunHorizontalNorth::STATE_Quiet()
{
        LoadAnimationWithId(GunHorizontalNorthAnimation::GUN_HORIZONTAL_NORTH_QUIET);
}

void GunHorizontalNorth::STATE_Exploding()
{
        LoadAnimationWithId(GunHorizontalNorthAnimation::GUN_HORIZONTAL_NORTH_EXPLODING);
}
