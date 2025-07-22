#include <entities/laser_bolt_green.h>
#include <chrono>

LaserBoltGreen::LaserBoltGreen() :
        IEntity(EntityIdentificator::LASER_BOLT_GREEN, EntityType::ENEMY, LaserBoltGreenStateIdentificator::LASER_BOLT_GREEN_MAX_STATES) {
}

LaserBoltGreen::LaserBoltGreen(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void LaserBoltGreen::PrintName() const {
        std::cout << "Laser Bolt Green." << std::endl;
}

bool LaserBoltGreen::Update(uint8_t pressedKeys_) {
        if (isMarkedToDelete) {
                return false;
        }

        position.AddZ(LASER_BOLT_GREEN_Z_DELTA); // Advance the laser bolt in the Z axis.

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

void LaserBoltGreen::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(LaserBoltGreenAnimation::LASER_BOLT_GREEN_QUIET);
}

IEntity* LaserBoltGreen::Create() {
        return new LaserBoltGreen();
}

void LaserBoltGreen::STATE_Quiet()
{
        LoadAnimationWithId(LaserBoltGreenAnimation::LASER_BOLT_GREEN_QUIET);
}