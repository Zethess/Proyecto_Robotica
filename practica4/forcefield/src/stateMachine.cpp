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
            wait_state(objects, robot);
            break;
    }

}
void stateMachine::approach_state(const std::vector<rc::GenericObject> &objects, const std::vector<Eigen::Vector2f> &line, rc::Robot &robot)
{
    std::cout << "ESTOY EN EL APPROACH" <<std::endl;

    static std::chrono::time_point<std::chrono::system_clock> start;

    if (robot.get_distance_to_target() < 100)
    {
       qInfo()<< __FUNCTION__<<" -> Atraviesa la puerta: " << robot.get_current_target().type <<" con ID:" << robot.get_current_target().id;

        state = State::WAITING;
    }
    else{
        if(auto it=std::find_if(objects.begin(), objects.end(),
                                [r=robot](auto &a){return a.type == r.get_current_target().type;}); it != objects.end())
            //En una funcion lamda lo que hay entre corchete es para capturar un objeto del entorno, y en a esta los elementos del it
        {
            robot.set_current_target(*it);
            qInfo() << "siguiendo al target "<< it->type;
        }
    }
}


void stateMachine::search_state(const std::vector<rc::GenericObject> &objects, rc::Robot &robot)
{
    std::cout << "ESTOY EN EL SEARCH Y EL OBJETIVO ANTERIOR ES " << robot.get_current_target().type <<std::endl;

    //Comprueba que el objeto que identifica es distinto del objeto que tenemos actualmente.
    //Una vez comprobado, si es distinto, cambia en el iterador a los atributos del nuevo objeto y cambia de estado
    if(auto it=std::find_if_not(objects.begin(), objects.end(),
                                [r=robot](auto &a){return a.type == r.get_current_target().type;}); it != objects.end() && it->type==80) //que el objeto no se salga del rango de la lista y que sea de tipo 80, eso es lo que dice el final despues del punto y coma
        //En una funcion lamda lo que hay entre corchete es para capturar un objeto del entorno, y en a esta los elementos del it
    {

            robot.set_current_target(*it);
            std::cout << "OBJETIVO ENCONTRADO" << it->type <<std::endl;
            state = State::APPROACHING;


    }   //Si no, sigue rotando
    else
    {
        qInfo() << "rotar para buscar target";
        robot.set_pure_rotation(0.5f);
    }
}

void stateMachine::wait_state(const std::vector<rc::GenericObject> &objects, rc::Robot &robot)
{

    std::cout << "ESTOY EN EL ESTADO WAIT "  <<std::endl;

    static std::chrono::time_point<std::chrono::system_clock> start;
    static bool primera_vez=true;
    if (primera_vez)
    {
        start = std::chrono::system_clock::now();
        primera_vez=false;
        robot.pasandoPuerta=true;
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float,std::milli> duration = end - start;

    if(duration.count() > 1500 )
    {
        qInfo()<< __FUNCTION__ <<" -> Realizada la espera, buscamos otro Target";
        state = State::SEARCHING;
        robot.resetearTarget();
        robot.set_has_target(false);
        primera_vez=true;
        robot.pasandoPuerta=false;
    }
}
