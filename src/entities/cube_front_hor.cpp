#include <entities/cube_front_hor.h>
#include <chrono>

CubeFrontHorizontal::CubeFrontHorizontal() :
        IEntity(EntityIdentificator::CUBE_FRONT_HORIZONTAL, EntityType::ENEMY, CubeFrontHorizontalStateIdentificator::CUBE_FRONT_HORIZONTAL_MAX_STATES) {
}

CubeFrontHorizontal::CubeFrontHorizontal(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void CubeFrontHorizontal::PrintName() const {
        std::cout << "Cube Front Horizontal." << std::endl;
}

bool CubeFrontHorizontal::Update(uint8_t pressedKeys_) {
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

void CubeFrontHorizontal::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(CubeFrontHorizontalAnimation::CUBE_FRONT_HORIZONTAL_QUIET);
}

IEntity* CubeFrontHorizontal::Create() {
        return new CubeFrontHorizontal();
}

void CubeFrontHorizontal::STATE_Quiet()
{
        LoadAnimationWithId(CubeFrontHorizontalAnimation::CUBE_FRONT_HORIZONTAL_QUIET);
}
