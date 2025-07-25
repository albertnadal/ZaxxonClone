#include <entities/enemy_rune.h>
#include <chrono>

EnemyRune::EnemyRune() :
        IEntity(EntityIdentificator::ENEMY_RUNE, EntityType::RUNE, EnemyRuneStateIdentificator::ENEMY_RUNE_MAX_STATES) {
}

EnemyRune::EnemyRune(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void EnemyRune::PrintName() const {
        std::cout << "Enemy Rune." << std::endl;
}

bool EnemyRune::Update(uint8_t pressedKeys_) {
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

void EnemyRune::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(EnemyRuneAnimation::ENEMY_RUNE_QUIET);
}

IEntity* EnemyRune::Create() {
        return new EnemyRune();
}

EnemyRune::~EnemyRune() = default;
