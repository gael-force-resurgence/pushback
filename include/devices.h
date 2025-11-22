#pragma once
#include "v5.h"
#include "v5_vcs.h"

using namespace vex;

enum IntakeState {
    IN,
    IN_STORAGE,
    OUT,
    STOP
};

class Intake {
   private:
    vex::motor FrontstageRoller, ScoringRoller;
    IntakeState currentState;

   public:
    bool antiJamEnabled = true;
    Intake(motor frontstage, motor scoring)
        : FrontstageRoller(frontstage), ScoringRoller(scoring) {};

    /**
     * @brief Spins the intake rollers based on the specified state and speed.
     * @param state The desired intake state (IN, IN_STORAGE, OUT, STOP).
     * @param speed The speed at which to spin the rollers (percentage).
     */
    void spin(IntakeState state, float speed);

    void unjam();

    inline void stop() {
        this->spin(STOP, 0);
    };
};