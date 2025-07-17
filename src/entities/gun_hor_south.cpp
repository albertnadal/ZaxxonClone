#include <entities/gun_hor_south.h>
#include <chrono>

GunHorizontalSouth::GunHorizontalSouth() :
        IEntity(EntityIdentificator::GUN_HORIZONTAL_NORTH, EntityType::ENEMY, GunHorizontalSouthStateIdentificator::GUN_HORIZONTAL_SOUTH_MAX_STATES) {
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

void GunHorizontalSouth::Hit(bool propelToRight) {
        //TODO: Implement RemoveFromSpacePartitionObjectsTree();
        Explode();
}

void GunHorizontalSouth::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(GunHorizontalSouthAnimation::GUN_HORIZONTAL_SOUTH_QUIET);
}

IEntity* GunHorizontalSouth::Create() {
        return new GunHorizontalSouth();
}

void GunHorizontalSouth::Explode()
{
        BEGIN_TRANSITION_MAP                            // - Current State -
                TRANSITION_MAP_ENTRY (STATE_EXPLODING)  // STATE_Quiet
                TRANSITION_MAP_ENTRY (EVENT_IGNORED)    // STATE_Exploding
        END_TRANSITION_MAP(NULL)
}

void GunHorizontalSouth::STATE_Quiet()
{
        LoadAnimationWithId(GunHorizontalSouthAnimation::GUN_HORIZONTAL_SOUTH_QUIET);
}

void GunHorizontalSouth::STATE_Exploding()
{
        LoadAnimationWithId(GunHorizontalSouthAnimation::GUN_HORIZONTAL_SOUTH_EXPLODING);
}
