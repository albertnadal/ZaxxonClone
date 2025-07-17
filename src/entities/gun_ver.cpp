#include <entities/gun_ver.h>
#include <chrono>

GunVertical::GunVertical() :
        IEntity(EntityIdentificator::GUN_VERTICAL, EntityType::ENEMY, GunVerticalStateIdentificator::GUN_VERTICAL_NORTH_MAX_STATES) {
}

GunVertical::GunVertical(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void GunVertical::PrintName() const {
        std::cout << "Gun Vertical." << std::endl;
}

bool GunVertical::Update(uint8_t pressedKeys_) {
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

void GunVertical::Hit(bool propelToRight) {
        //TODO: Implement RemoveFromSpacePartitionObjectsTree();
        Explode();
}

void GunVertical::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(GunVerticalAnimation::GUN_VERTICAL_QUIET);
}

IEntity* GunVertical::Create() {
        return new GunVertical();
}

void GunVertical::Explode()
{
        BEGIN_TRANSITION_MAP                            // - Current State -
                TRANSITION_MAP_ENTRY (STATE_EXPLODING)  // STATE_Quiet
                TRANSITION_MAP_ENTRY (EVENT_IGNORED)    // STATE_Exploding
        END_TRANSITION_MAP(NULL)
}

void GunVertical::STATE_Quiet()
{
        LoadAnimationWithId(GunVerticalAnimation::GUN_VERTICAL_QUIET);
}

void GunVertical::STATE_Exploding()
{
        LoadAnimationWithId(GunVerticalAnimation::GUN_VERTICAL_EXPLODING);
}
