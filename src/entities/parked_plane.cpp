#include <entities/parked_plane.h>
#include <chrono>

ParkedPlane::ParkedPlane() :
        IEntity(EntityIdentificator::PARKED_PLANE, EntityType::ENEMY, ParkedPlaneStateIdentificator::PARKED_PLANE_MAX_STATES) {
}

ParkedPlane::ParkedPlane(EntityIdentificator _id, EntityType _type, unsigned char max_states) :
        IEntity(_id, _type, max_states) {
}

void ParkedPlane::PrintName() const {
        std::cout << "Parked Plane." << std::endl;
}

bool ParkedPlane::Update(uint8_t pressedKeys_) {
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

void ParkedPlane::Hit() {
        if(!isExploding) {
                RemoveFromSpacePartitionObjectsTree();
                isExploding = true;
                LoadAnimationWithId(ParkedPlaneAnimation::PARKED_PLANE_EXPLODING);  // The object will be marked to delete once the animation finishes
        }
}

bool ParkedPlane::ShouldBeginAnimationLoopAgain() {
    if (isExploding) {
        isMarkedToDelete = true;
    }

    return false;
}

void ParkedPlane::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
        spriteSheet = _spriteSheet;
        LoadAnimationWithId(ParkedPlaneAnimation::PARKED_PLANE_QUIET);
}

IEntity* ParkedPlane::Create() {
        return new ParkedPlane();
}

ParkedPlane::~ParkedPlane() = default;