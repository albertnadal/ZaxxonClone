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

void FuelTank::Hit(bool propelToRight) {
        //TODO: Implement RemoveFromSpacePartitionObjectsTree();
        Explode();
}

void FuelTank::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(FuelTankAnimation::FUEL_TANK_QUIET);
}

IEntity* FuelTank::Create() {
        return new FuelTank();
}

void FuelTank::Explode()
{
        BEGIN_TRANSITION_MAP                            // - Current State -
                TRANSITION_MAP_ENTRY (STATE_EXPLODING)  // STATE_Quiet
                TRANSITION_MAP_ENTRY (EVENT_IGNORED)    // STATE_Exploding
        END_TRANSITION_MAP(NULL)
}

void FuelTank::STATE_Quiet()
{
        LoadAnimationWithId(FuelTankAnimation::FUEL_TANK_QUIET);
}

void FuelTank::STATE_Exploding()
{
        LoadAnimationWithId(FuelTankAnimation::FUEL_TANK_EXPLODING);
}
