#include <entities/cube_back.h>
#include <chrono>

CubeBack::CubeBack() :
        IEntity(EntityIdentificator::CUBE_BACK, EntityType::ENEMY, CubeBackStateIdentificator::CUBE_BACK_MAX_STATES) {
}

CubeBack::CubeBack(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void CubeBack::PrintName() const {
        std::cout << "Cube Back." << std::endl;
}

bool CubeBack::Update(uint8_t pressedKeys_) {
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

void CubeBack::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(CubeBackAnimation::CUBE_BACK_QUIET);
}

IEntity* CubeBack::Create() {
        return new CubeBack();
}

void CubeBack::STATE_Quiet()
{
        LoadAnimationWithId(CubeBackAnimation::CUBE_BACK_QUIET);
}
