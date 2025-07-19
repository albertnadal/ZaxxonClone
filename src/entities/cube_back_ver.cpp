#include <entities/cube_back_ver.h>
#include <chrono>

CubeBackVertical::CubeBackVertical() :
        IEntity(EntityIdentificator::CUBE_BACK_VERTICAL, EntityType::ENEMY, CubeBackVerticalStateIdentificator::CUBE_BACK_VERTICAL_MAX_STATES) {
}

CubeBackVertical::CubeBackVertical(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void CubeBackVertical::PrintName() const {
        std::cout << "Cube Back Vertical." << std::endl;
}

bool CubeBackVertical::Update(uint8_t pressedKeys_) {
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

void CubeBackVertical::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(CubeBackVerticalAnimation::CUBE_BACK_VERTICAL_QUIET);
}

IEntity* CubeBackVertical::Create() {
        return new CubeBackVertical();
}

void CubeBackVertical::STATE_Quiet()
{
        LoadAnimationWithId(CubeBackVerticalAnimation::CUBE_BACK_VERTICAL_QUIET);
}
