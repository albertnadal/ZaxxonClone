#include <entities/ship.h>

void Ship::UpKeyPressed() {
    BEGIN_TRANSITION_MAP                                  // - Current State -
        TRANSITION_MAP_ENTRY (STATE_ASCENDING)            // STATE_Straight_Flight
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Ascending
        TRANSITION_MAP_ENTRY (STATE_ASCENDING)            // STATE_Descending
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Exploding
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Dead
    END_TRANSITION_MAP(nullptr)
}

void Ship::UpKeyReleased() {
    BEGIN_TRANSITION_MAP                                  // - Current State -
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Straight_Flight
        TRANSITION_MAP_ENTRY (STATE_STRAIGHT_FLIGHT)      // STATE_Ascending
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Descending
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Exploding
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Dead
    END_TRANSITION_MAP(nullptr)
}

void Ship::DownKeyPressed() {
    BEGIN_TRANSITION_MAP                                  // - Current State -
        TRANSITION_MAP_ENTRY (STATE_DESCENDING)           // STATE_Straight_Flight
        TRANSITION_MAP_ENTRY (STATE_DESCENDING)           // STATE_Ascending
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Descending
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Exploding
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Dead
    END_TRANSITION_MAP(nullptr)
}

void Ship::DownKeyReleased() {
    BEGIN_TRANSITION_MAP                                  // - Current State -
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Straight_Flight
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Ascending
        TRANSITION_MAP_ENTRY (STATE_STRAIGHT_FLIGHT)      // STATE_Descending
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Exploding
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Dead
    END_TRANSITION_MAP(nullptr)
}

void Ship::Explode() {
    BEGIN_TRANSITION_MAP                                  // - Current State -
        TRANSITION_MAP_ENTRY (STATE_EXPLODING)            // STATE_Straight_Flight
        TRANSITION_MAP_ENTRY (STATE_EXPLODING)            // STATE_Ascending
        TRANSITION_MAP_ENTRY (STATE_EXPLODING)            // STATE_Descending
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Exploding
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)              // STATE_Dead
    END_TRANSITION_MAP(nullptr)
}