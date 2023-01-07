//
// Created by alumno on 20/12/22.
//

#include "stateMachine.h"
void stateMachine::state_machine(const std::vector<rc::GenericObject> &objects, const std::vector<Eigen::Vector2f> &line, rc::Robot &robot){

    switch(state)
    {
        case State::IDLE:
            break;
        case State::SEARCHING:
            search_state(objects, robot);
            break;
        case State::APPROACHING:
            approach_state(objects, line, robot);
            break;
        case State::WAITING:
            break;
    }

}
void stateMachine::approach_state(const std::vector<rc::GenericObject> &objects, const std::vector<Eigen::Vector2f> &line, rc::Robot &robot)
{
    std::cout << "ESTOY EN EL APPROACH" <<std::endl;
    if (robot.get_distance_to_target() < 800){
        state = State::SEARCHING;
    }
    else{
        if(auto it=std::find_if(objects.begin(), objects.end(),
                                [r=robot](auto &a){return a.type == r.get_current_target().type;}); it != objects.end())
            //En una funcion lamda lo que hay entre corchete es para capturar un objeto del entorno, y en a esta los elementos del it
        {
            robot.set_current_target(*it);
        }
    }
}


void stateMachine::search_state(const std::vector<rc::GenericObject> &objects, rc::Robot &robot)
{
    std::cout << "ESTOY EN EL SEARCH" <<std::endl;

    //Comprueba que el objeto que identifica es distinto del objeto que tenemos actualmente.
    //Una vez comprobado, si es distinto, cambia en el iterador a los atributos del nuevo objeto y cambia de estado
    if(auto it=std::find_if_not(objects.begin(), objects.end(),
                                [r=robot](auto &a){return a.type == r.get_current_target().type;}); it != objects.end())
        //En una funcion lamda lo que hay entre corchete es para capturar un objeto del entorno, y en a esta los elementos del it
    {
        if(it->type==80)
        {
            robot.set_current_target(*it);
            std::cout << "OBJETIVO ENCONTRADO" <<std::endl;
            state = State::APPROACHING;
        }

    }   //Si no, sigue rotando
    else
    {
        robot.set_pure_rotation(0.5f);
    }
}
