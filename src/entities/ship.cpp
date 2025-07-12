#include <entities/ship.h>
#include <chrono>

Ship::Ship() :
        IEntity(EntityIdentificator::SHIP, EntityType::PLAYER, ShipStateIdentificator::SHIP_MAX_STATES) {
}

void Ship::PrintName() const {
    std::cout << "Ship." << std::endl;
}

bool Ship::Update(const uint8_t pressedKeys_) {
    bool needRedraw = false;
    pressedKeys = pressedKeys_;

    if (pressedKeys != KeyboardKeyCode::Z_KEY_NONE) {
        ProcessPressedKeys();
    } else if (pressedKeys != prevPressedKeys) {
        ProcessReleasedKeys();
    }

    // Check for collisions
    UpdateCollisions();

    if (!animationLoaded) {
        return false;
    }

    if (animationHasOnlyOneSprite && firstSpriteOfCurrentAnimationIsLoaded) {
        return false;
    }

    if (chrono::system_clock::now() >= nextSpriteTime) {
        // Load next sprite of the current animation
        LoadNextSprite();

        // Check for possible collisions with the solid areas of the currrent sprite
        UpdateCollisions();
        return true;
    }

    return needRedraw;
}

void Ship::GetSolidCollisions(std::vector<ObjectCollision> &collisions, bool& playerIsSuspendedInTheAir) {

}

void Ship::UpdateCollisions() {

}

void Ship::UpdatePreviousDirection() {

}

void Ship::ProcessPressedKeys(bool checkPreviousPressedKeys) {
    bool shipIsMovingInXAxis = true;
    if ((pressedKeys & KeyboardKeyCode::Z_KEY_RIGHT) == KeyboardKeyCode::Z_KEY_RIGHT) {
        MoveToXAxis(Direction::RIGHT);
    } else if ((pressedKeys & KeyboardKeyCode::Z_KEY_LEFT) == KeyboardKeyCode::Z_KEY_LEFT) {
        MoveToXAxis(Direction::LEFT);
    } else {
        shipIsMovingInXAxis = false;
    }

    if ((pressedKeys & KeyboardKeyCode::Z_KEY_UP) == KeyboardKeyCode::Z_KEY_UP) {
        if ((!checkPreviousPressedKeys) || ((checkPreviousPressedKeys) && ((prevPressedKeys & KeyboardKeyCode::Z_KEY_UP) != KeyboardKeyCode::Z_KEY_UP))) {
            UpKeyPressed();
        }
        MoveToYAxis(Direction::UP, shipIsMovingInXAxis);
    } else if ((prevPressedKeys & KeyboardKeyCode::Z_KEY_UP) == KeyboardKeyCode::Z_KEY_UP) {
        UpKeyReleased();
    } else if ((pressedKeys & KeyboardKeyCode::Z_KEY_DOWN) == KeyboardKeyCode::Z_KEY_DOWN) {
        if ((!checkPreviousPressedKeys) || ((checkPreviousPressedKeys) && ((prevPressedKeys & KeyboardKeyCode::Z_KEY_DOWN) != KeyboardKeyCode::Z_KEY_DOWN))) {
            DownKeyPressed();
        }
        MoveToYAxis(Direction::DOWN, shipIsMovingInXAxis);
    } else if ((prevPressedKeys & KeyboardKeyCode::Z_KEY_DOWN) == KeyboardKeyCode::Z_KEY_DOWN) {
        DownKeyReleased();
    }

    prevPressedKeys = pressedKeys;
}

void Ship::ProcessReleasedKeys() {
    if ((prevPressedKeys & KeyboardKeyCode::Z_KEY_UP) == KeyboardKeyCode::Z_KEY_UP) {
        UpKeyReleased();
    }

    if ((prevPressedKeys & KeyboardKeyCode::Z_KEY_DOWN) == KeyboardKeyCode::Z_KEY_DOWN) {
        DownKeyReleased();
    }

    prevPressedKeys = KeyboardKeyCode::Z_KEY_NONE;
}

void Ship::MoveToXAxis(Direction direction) {
    // Update the player position.
    PositionAddX(direction == Direction::RIGHT ? 2.0f : -2.0f);
}

void Ship::MoveToYAxis(Direction direction, bool flySlow) {
    // Update the player position.
    float verticalVelocity = flySlow ? 1.5f : 2.0f;
    PositionAddY(direction == Direction::DOWN ? verticalVelocity : -1 * verticalVelocity);
}

void Ship::InitWithSpriteSheet(EntitySpriteSheet *_spriteSheet) {
    spriteSheet = _spriteSheet;
    LoadAnimationWithId(ShipAnimation::STRAIGHT_FLIGHT);
}

void Ship::LoadNextSprite() {
    SpriteData spriteData = NextSpriteData();

    if (spriteData.beginNewLoop) {
        if (ShouldBeginAnimationLoopAgain()) {
            spriteData = NextSpriteData();
        }
    }

    nextSpriteTime = (chrono::system_clock::now() + chrono::milliseconds(spriteData.duration));

    currentSprite.width = spriteData.width;
    currentSprite.height = spriteData.height;
    currentSprite.xOffset = spriteData.xOffset;
    currentSprite.yOffset = spriteData.yOffset;
    currentSprite.u1 = spriteData.u1;
    currentSprite.v1 = spriteData.v1;
    currentSprite.u2 = spriteData.u2;
    currentSprite.v2 = spriteData.v2;

    // Adjusts object position according to the sprite offset
    //PositionSetOffset(spriteData.xOffset, spriteData.yOffset);

    boundingBox = {spriteData.lowerBoundX, spriteData.lowerBoundY, spriteData.upperBoundX, spriteData.upperBoundY};
    solidBoundingBox = {spriteData.lowerBoundX, spriteData.lowerBoundY, spriteData.upperBoundX, spriteData.upperBoundY};
    firstSpriteOfCurrentAnimationIsLoaded = true;
}

IEntity *Ship::Create() {
    return new Ship();
}

Ship::~Ship() = default;

bool Ship::ShouldBeginAnimationLoopAgain() {
    return false;
}

void Ship::STATE_Straight_Flight() {
    UpdatePreviousDirection();
    LoadAnimationWithId(ShipAnimation::STRAIGHT_FLIGHT);
    ProcessPressedKeys(false);
}

void Ship::STATE_Ascending() {
    UpdatePreviousDirection();
    LoadAnimationWithId(ShipAnimation::ASCENDING);
    ProcessPressedKeys(false);
}

void Ship::STATE_Descending() {
    UpdatePreviousDirection();
    LoadAnimationWithId(ShipAnimation::DESCENDING);
    ProcessPressedKeys(false);
}