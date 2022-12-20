//
// Created by alumno on 14/12/22.
//

#include "GenericObject.h"
GenericObject::GenericObject(const RoboCompYoloObjects::TBox &box)
{
    id = box.id;
    type = box.type;
    left = box.left;
    top = box.top;
    right = box.right;
    bot = box.bot;
    score = box.score;
    depth = box.depth;
    x = box.x;
    y = box.y;
    z = box.z;
}

GenericObject::GenericObject(const Door_detector::Door &door)
{
    id=81;
    x=door.pcenter.x();
    y=door.pcenter.y();
    z=0;
}


std::vector<GenericObject> GenericObject::createList(const std::vector<Door_detector::Door> &doors)
{
    std::vector<GenericObject> objects;
    for (const auto &obj: doors)
        objects.emplace_back(GenericObject(obj));
    return objects;
}

std::vector<GenericObject> GenericObject::createList(const std::vector<RoboCompYoloObjects::TBox> &objs) //creamos la lista de objetos
{
    std::vector<GenericObject> objects;
    for (const auto &obj: objs)
        objects.emplace_back(GenericObject(obj));
    return objects;
}
