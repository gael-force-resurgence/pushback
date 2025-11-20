#pragma once

using namespace vex;

enum IntakeState {
    IN,
    IN_STORAGE,
    OUT,
    OFF
};

class Intake {
   private:
    vex::motor FrontstageRoller, BackstageRoller, ScoringRoller;

   public:
    Intake(motor frontstage, motor back, motor scoring)
        : FrontstageRoller(frontstage), BackstageRoller(back), ScoringRoller(scoring) {};

    /**
     * @brief Spins the intake rollers based on the specified state and speed.
     * @param state The desired intake state (IN, IN_STORAGE, OUT, STOP).
     * @param speed The speed at which to spin the rollers (percentage).
     */
    inline void spin(IntakeState state, float speed) {
        switch (state) {
            case IN:
                FrontstageRoller.spin(fwd, speed, pct);
                BackstageRoller.spin(fwd, speed, pct);
                ScoringRoller.spin(fwd, speed, pct);
                break;
            case IN_STORAGE:
                FrontstageRoller.spin(fwd, speed, pct);
                BackstageRoller.spin(fwd, speed, pct);
                ScoringRoller.stop(hold);
                break;
            case OUT:
                FrontstageRoller.spin(fwd, -speed, pct);
                BackstageRoller.spin(fwd, -speed, pct);
                ScoringRoller.spin(fwd, -speed, pct);
                break;
            case STOP:
                this->stop();
                break;
        };
    };

    inline void stop() {
        FrontstageRoller.stop(hold);
        BackstageRoller.stop(hold);
        ScoringRoller.stop(hold);
    };
};