//
// Created by alumno on 14/12/22.
//

//#include "GenericObject.h"
//GenericObject::GenericObject(const RoboCompYoloObjects::TBox &box)
//{
//    id = box.id;
//    type = box.type;
//    left = box.left;
//    top = box.top;
//    right = box.right;
//    bot = box.bot;
//    score = box.score;
//    depth = box.depth;
//    x = box.x;
//    y = box.y;
//    z = box.z;
//}
//
//GenericObject::GenericObject(const Door_detector::Door &door)
//{
//    id=81;
//    x=door.pcenter.x();
//    y=door.pcenter.y();
//    z=0;
//}
//
//
//std::vector<GenericObject> GenericObject::createList(const std::vector<Door_detector::Door> &doors)
//{
//    std::vector<GenericObject> objects;
//    for (const auto &obj: doors)
//        objects.emplace_back(GenericObject(obj));
//    return objects;
//}
//
//std::vector<GenericObject> GenericObject::createList(const std::vector<RoboCompYoloObjects::TBox> &objs) //creamos la lista de objetos
//{
//    std::vector<GenericObject> objects;
//    for (const auto &obj: objs)
//        objects.emplace_back(GenericObject(obj));
//    return objects;
//}

#include "GenericObject.h"

namespace rc
{
    GenericObject::GenericObject(const RoboCompYoloObjects::TBox &box, const  Eigen::Transform<float, 3, Eigen::Affine> &tf) :
            id(box.id), type(box.type), left(box.left), top(box.top),
            right(box.right), bot(box.bot), score(box.score), depth(box.depth),
            x(box.x), y(box.y), z(box.z)
    {
        Eigen::Vector3f rc = tf * Eigen::Vector3f(box.x, box.y, box.z);
        rx = rc.x();
        ry = rc.y();
        rz = rc.z();
    }
    GenericObject::GenericObject(const Door_detector::Door &d)
    {
        type = 80;  // door
        rx = d.pcenter.x();
        ry = d.pcenter.y();
        rz = 0.f;
        x = d.pcenter.x();
        y = d.pcenter.y();
        z = 0.f;
    }
    std::vector<GenericObject> GenericObject::add_yolo(const std::vector<RoboCompYoloObjects::TBox> &boxes, const  Eigen::Transform<float, 3, Eigen::Affine> &tf )
    {
        std::vector<GenericObject> bobjs;
        for(const auto &b: boxes)
            bobjs.emplace_back(GenericObject(b, tf));
        return bobjs;
    }
    std::vector<GenericObject> GenericObject::add_doors(const std::vector<Door_detector::Door> &doors)
    {
        std::vector<GenericObject> bdoors;
        for(const auto &d: doors)
            bdoors.emplace_back(GenericObject(d));
        return bdoors;
    }
    Eigen::Vector3f GenericObject::get_local_coordinates() const
    {
        return Eigen::Vector3f(x, y, z);
    }
    Eigen::Vector3f GenericObject::get_robot_coordinates() const
    {
        return Eigen::Vector3f(rx, ry, rz);
    }
    void GenericObject::print() const
    {
        std::cout << "Object: " << std::endl;
        std::cout << "  type: " << type << std::endl;
        std::cout << "  rx: " << rx << std::endl;
        std::cout << "  ry: " << ry << std::endl;
        std::cout << "  rz: " << rz << std::endl;
        std::cout << "--------------"<< std::endl;
    }
} // rc

