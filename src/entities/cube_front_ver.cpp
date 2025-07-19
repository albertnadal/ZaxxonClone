#include <entities/cube_front_ver.h>
#include <chrono>

CubeFrontVertical::CubeFrontVertical() :
        IEntity(EntityIdentificator::CUBE_FRONT_VERTICAL, EntityType::ENEMY, CubeFrontVerticalStateIdentificator::CUBE_FRONT_VERTICAL_MAX_STATES) {
}

CubeFrontVertical::CubeFrontVertical(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void CubeFrontVertical::PrintName() const {
        std::cout << "Cube Front Vertical." << std::endl;
}

bool CubeFrontVertical::Update(uint8_t pressedKeys_) {
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

void CubeFrontVertical::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(CubeFrontVerticalAnimation::CUBE_FRONT_VERTICAL_QUIET);
}

IEntity* CubeFrontVertical::Create() {
        return new CubeFrontVertical();
}

void CubeFrontVertical::STATE_Quiet()
{
        LoadAnimationWithId(CubeFrontVerticalAnimation::CUBE_FRONT_VERTICAL_QUIET);
}
