#include <entities/cube_front.h>
#include <chrono>

CubeFront::CubeFront() :
        IEntity(EntityIdentificator::CUBE_FRONT, EntityType::ENEMY, CubeFrontStateIdentificator::CUBE_FRONT_MAX_STATES) {
}

CubeFront::CubeFront(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void CubeFront::PrintName() const {
        std::cout << "Cube Front." << std::endl;
}

bool CubeFront::Update(uint8_t pressedKeys_) {
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

void CubeFront::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(CubeFrontAnimation::CUBE_FRONT_QUIET);
}

IEntity* CubeFront::Create() {
        return new CubeFront();
}

void CubeFront::STATE_Quiet()
{
        LoadAnimationWithId(CubeFrontAnimation::CUBE_FRONT_QUIET);
}
