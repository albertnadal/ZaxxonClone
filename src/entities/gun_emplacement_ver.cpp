#include <entities/gun_emplacement_ver.h>
#include <chrono>

GunEmplacementVertical::GunEmplacementVertical() :
        IEntity(EntityIdentificator::GUN_EMPLACEMENT_VERTICAL, EntityType::ENEMY, GunEmplacementVerticalStateIdentificator::GUN_EMPLACEMENT_VERTICAL_MAX_STATES) {
}

GunEmplacementVertical::GunEmplacementVertical(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void GunEmplacementVertical::PrintName() const {
        std::cout << "Gun Emplacement Vertical." << std::endl;
}

bool GunEmplacementVertical::Update(uint8_t pressedKeys_) {
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

void GunEmplacementVertical::Hit(bool propelToRight) {
        //TODO: Implement RemoveFromSpacePartitionObjectsTree();
        Explode();
}

void GunEmplacementVertical::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(GunEmplacementVerticalAnimation::GUN_EMPLACEMENT_VERTICAL_QUIET);
}

IEntity* GunEmplacementVertical::Create() {
        return new GunEmplacementVertical();
}

void GunEmplacementVertical::Explode()
{
        BEGIN_TRANSITION_MAP                            // - Current State -
                TRANSITION_MAP_ENTRY (STATE_EXPLODING)  // STATE_Quiet
                TRANSITION_MAP_ENTRY (EVENT_IGNORED)    // STATE_Exploding
        END_TRANSITION_MAP(NULL)
}

void GunEmplacementVertical::STATE_Quiet()
{
        LoadAnimationWithId(GunEmplacementVerticalAnimation::GUN_EMPLACEMENT_VERTICAL_QUIET);
}

void GunEmplacementVertical::STATE_Exploding()
{
        LoadAnimationWithId(GunEmplacementVerticalAnimation::GUN_EMPLACEMENT_VERTICAL_EXPLODING);
}
