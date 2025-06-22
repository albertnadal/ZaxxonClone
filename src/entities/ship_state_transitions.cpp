#include <entities/ship.h>

void Ship::RightKeyPressed() {
    BEGIN_TRANSITION_MAP                            // - Current State -
            TRANSITION_MAP_ENTRY (STATE_STRAIGHT_FLIGHT)  // STATE_Idle_Right
    END_TRANSITION_MAP(nullptr)
}

void Ship::RightKeyReleased() {
    BEGIN_TRANSITION_MAP                            // - Current State -
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)    // STATE_Idle_Right
    END_TRANSITION_MAP(nullptr)
}

void Ship::LeftKeyPressed() {
    BEGIN_TRANSITION_MAP                            // - Current State -
            TRANSITION_MAP_ENTRY (STATE_STRAIGHT_FLIGHT)   // STATE_Idle_Right
    END_TRANSITION_MAP(nullptr)
}

void Ship::LeftKeyReleased() {
    BEGIN_TRANSITION_MAP                            // - Current State -
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)    // STATE_Idle_Right
    END_TRANSITION_MAP(nullptr)
}
