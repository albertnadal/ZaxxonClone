#include <entities/gun_emplacement_hor.h>
#include <chrono>

GunEmplacementHorizontal::GunEmplacementHorizontal() :
        IEntity(EntityIdentificator::GUN_EMPLACEMENT_HORIZONTAL, EntityType::ENEMY, GunEmplacementHorizontalStateIdentificator::GUN_EMPLACEMENT_HORIZONTAL_MAX_STATES) {
}

GunEmplacementHorizontal::GunEmplacementHorizontal(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void GunEmplacementHorizontal::PrintName() const {
        std::cout << "Gun Emplacement Horizontal." << std::endl;
}

bool GunEmplacementHorizontal::Update(uint8_t pressedKeys_) {
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

void GunEmplacementHorizontal::Hit(bool propelToRight) {
        //TODO: Implement RemoveFromSpacePartitionObjectsTree();
        Explode();
}

void GunEmplacementHorizontal::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(GunEmplacementHorizontalAnimation::GUN_EMPLACEMENT_HORIZONTAL_QUIET);
}

IEntity* GunEmplacementHorizontal::Create() {
        return new GunEmplacementHorizontal();
}

void GunEmplacementHorizontal::Explode()
{
        BEGIN_TRANSITION_MAP                            // - Current State -
                TRANSITION_MAP_ENTRY (STATE_EXPLODING)  // STATE_Quiet
                TRANSITION_MAP_ENTRY (EVENT_IGNORED)    // STATE_Exploding
        END_TRANSITION_MAP(NULL)
}

void GunEmplacementHorizontal::STATE_Quiet()
{
        LoadAnimationWithId(GunEmplacementHorizontalAnimation::GUN_EMPLACEMENT_HORIZONTAL_QUIET);
}

void GunEmplacementHorizontal::STATE_Exploding()
{
        LoadAnimationWithId(GunEmplacementHorizontalAnimation::GUN_EMPLACEMENT_HORIZONTAL_EXPLODING);
}
