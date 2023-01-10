//
// Created by alumno on 20/12/22.
//

#ifndef FORCEFIELD_STATEMACHINE_H
#define FORCEFIELD_STATEMACHINE_H

#include <Eigen/Dense>
#include <YoloObjects.h>
#include <JointMotorSimple.h>
#include <OmniRobot.h>
#include <door_detector.h>
#include "robot.h"
#include "GenericObject.h"

class stateMachine {
public:
    enum class State {IDLE, SEARCHING, APPROACHING, WAITING};
    State state = State::SEARCHING;
    void state_machine(const std::vector<rc::GenericObject> &objects, const std::vector<Eigen::Vector2f> &line, rc::Robot &robot);
private:
    void approach_state(const std::vector<rc::GenericObject> &objects, const std::vector<Eigen::Vector2f> &line, rc::Robot &robot);
    void search_state(const std::vector<rc::GenericObject> &objects, rc::Robot &robot);
    void wait_state(const std::vector<rc::GenericObject> &objects, rc::Robot &robot);
};


#endif //FORCEFIELD_STATEMACHINE_H
