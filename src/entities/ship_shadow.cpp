#include <entities/enemy_rune.h>
#include <chrono>

ShipShadow::ShipShadow() :
        IEntity(EntityIdentificator::SHIP_SHADOW, EntityType::SHADOW, ShipShadowStateIdentificator::SHIP_SHADOW_MAX_STATES) {
}

ShipShadow::ShipShadow(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void ShipShadow::PrintName() const {
        std::cout << "Ship Shadow." << std::endl;
}

bool ShipShadow::Update(uint8_t pressedKeys_) {
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

void ShipShadow::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(ShipShadowAnimation::SHIP_SHADOW_QUIET);
}

IEntity* ShipShadow::Create() {
        return new ShipShadow();
}

ShipShadow::~ShipShadow() = default;
