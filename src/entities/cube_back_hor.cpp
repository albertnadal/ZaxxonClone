#include <entities/cube_back_hor.h>
#include <chrono>

CubeBackHorizontal::CubeBackHorizontal() :
        IEntity(EntityIdentificator::CUBE_BACK_HORIZONTAL, EntityType::ENEMY, CubeBackHorizontalStateIdentificator::CUBE_BACK_HORIZONTAL_MAX_STATES) {
}

CubeBackHorizontal::CubeBackHorizontal(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void CubeBackHorizontal::PrintName() const {
        std::cout << "Cube Back Horizontal." << std::endl;
}

bool CubeBackHorizontal::Update(uint8_t pressedKeys_) {
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

void CubeBackHorizontal::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(CubeBackHorizontalAnimation::CUBE_BACK_HORIZONTAL_QUIET);
}

IEntity* CubeBackHorizontal::Create() {
        return new CubeBackHorizontal();
}

void CubeBackHorizontal::STATE_Quiet()
{
        LoadAnimationWithId(CubeBackHorizontalAnimation::CUBE_BACK_HORIZONTAL_QUIET);
}
