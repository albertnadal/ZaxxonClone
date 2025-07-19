#include <entities/cube_ship_front.h>
#include <chrono>

CubeShipFront::CubeShipFront() :
        IEntity(EntityIdentificator::CUBE_SHIP_FRONT, EntityType::ENEMY, CubeShipFrontStateIdentificator::CUBE_SHIP_FRONT_MAX_STATES) {
}

CubeShipFront::CubeShipFront(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void CubeShipFront::PrintName() const {
        std::cout << "Cube Ship Front." << std::endl;
}

bool CubeShipFront::Update(uint8_t pressedKeys_) {
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

void CubeShipFront::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(CubeShipFrontAnimation::CUBE_SHIP_FRONT_QUIET);
}

IEntity* CubeShipFront::Create() {
        return new CubeShipFront();
}

void CubeShipFront::STATE_Quiet()
{
        LoadAnimationWithId(CubeShipFrontAnimation::CUBE_SHIP_FRONT_QUIET);
}
