//
// Created by alumno on 14/12/22.
//

#include "GenericObject.h"

GenericObject::GenericObject(const RoboCompYoloObjects::TBox &box)
{


}

GenericObject::GenericObject(const Door_detector::Door &door) {

}

std::vector<GenericObject> GenericObject::createList(const std::vector<RoboCompYoloObjects::TBox> &objs) //creamos la lista de objetos
{
    std::vector<GenericObject> objects;
    for (const auto &obj: objs)
        objects.emplace_back(GenericObject(obj));
    return objects;
}
