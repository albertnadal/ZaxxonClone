#include <entities/fuel_tank.h>
#include <chrono>

FuelTank::FuelTank() :
        IEntity(EntityIdentificator::FUEL_TANK, EntityType::ENEMY, FuelTankStateIdentificator::FUEL_TANK_MAX_STATES) {
}

FuelTank::FuelTank(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void FuelTank::PrintName() const {
        std::cout << "Fuel Tank." << std::endl;
}

bool FuelTank::Update(uint8_t pressedKeys_) {
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

void FuelTank::Hit() {
        if(!isExploding) {
                RemoveFromSpacePartitionObjectsTree();
                isExploding = true;
                LoadAnimationWithId(FuelTankAnimation::FUEL_TANK_EXPLODING);  // The object will be marked to delete once the animation finishes
        }
}

bool FuelTank::ShouldBeginAnimationLoopAgain() {
    if (isExploding) {
        isMarkedToDelete = true;
        CreateRune();
    }

    return false;
}

void FuelTank::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(FuelTankAnimation::FUEL_TANK_QUIET);
}

IEntity* FuelTank::Create() {
        return new FuelTank();
}

FuelTank::~FuelTank() = default;
