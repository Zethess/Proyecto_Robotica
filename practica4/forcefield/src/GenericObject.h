//
// Created by alumno on 14/12/22.
//

#include <Eigen/Dense>
#include <YoloObjects.h>
#include <JointMotorSimple.h>
#include <OmniRobot.h>
#include <door_detector.h>


#ifndef FORCEFIELD_GENERICOBJECT_H
#define FORCEFIELD_GENERICOBJECT_H


class GenericObject{

  private:
      int id;
      int type;
      int left;
      int top;
      int right;
      int bot;
      float score;
      float depth;
      float x;
      float y;
      float z;


   public:
    GenericObject(const RoboCompYoloObjects::TBox &box); //objetos de yolo
    GenericObject(const Door_detector::Door &door);
    GenericObject();


    static std::vector<GenericObject> createList(const std::vector<RoboCompYoloObjects::TBox> &objs); //Para crear la lista de objetos del Tbox
    static std::vector<GenericObject> createList(const std::vector<Door_detector::Door> &doors); //Para crear la lista de objetos puertas

};



#endif //FORCEFIELD_GENERICOBJECT_H
