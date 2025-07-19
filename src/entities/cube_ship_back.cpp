#include <entities/cube_back.h>
#include <chrono>

CubeShipBack::CubeShipBack() :
        IEntity(EntityIdentificator::CUBE_SHIP_BACK, EntityType::ENEMY, CubeShipBackStateIdentificator::CUBE_SHIP_BACK_MAX_STATES) {
}

CubeShipBack::CubeShipBack(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void CubeShipBack::PrintName() const {
        std::cout << "Cube Ship Back." << std::endl;
}

bool CubeShipBack::Update(uint8_t pressedKeys_) {
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

void CubeShipBack::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(CubeShipBackAnimation::CUBE_SHIP_BACK_QUIET);
}

IEntity* CubeShipBack::Create() {
        return new CubeShipBack();
}

void CubeShipBack::STATE_Quiet()
{
        LoadAnimationWithId(CubeShipBackAnimation::CUBE_SHIP_BACK_QUIET);
}
