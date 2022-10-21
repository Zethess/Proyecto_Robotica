/*
 *    Copyright (C) 2022 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
	\brief
	@author authorname
*/



#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H
#define MAX_ADV 1200.0
#define DELTA 50
#define MAX_ROT 1.2


#include <genericworker.h>
#include <innermodel/innermodel.h>
#include <ranges>
#include <numeric>
#include <functional>
#include <chrono>

using myclock = std::chrono::system_clock;
using msec = std::chrono::duration<double, std::milli>;

class SpecificWorker : public GenericWorker
{
Q_OBJECT
public:
	SpecificWorker(TuplePrx tprx, bool startup_check);
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);



public slots:
	void compute();
	int startup_check();
	void initialize(int period);

    std::tuple<float, float> FORWARD_function(const RoboCompLaserMulti::TLaserData &ldata);
    //Este método lo único que va hacer es pasar al estado STRAIGHT (RECTO)
    std::tuple<float, float> IDLE_function(const RoboCompLaserMulti::TLaserData &ldata);
    std::tuple<float, float> TURN_function(const RoboCompLaserMulti::TLaserData &ldata);
    std::tuple<float, float> SPIRAL_function(RoboCompLaserMulti::TLaserData &ldata);

    std::tuple<float, float> follow_wall_method(const RoboCompLaserMulti::TLaserData &ldata);
    bool hayQueSeguirLaPared(const RoboCompLaserMulti::TLaserData &ldata);
    bool GirarIzquierda(const RoboCompLaserMulti::TLaserData &ldata);
    float calcularMediaLaser(const RoboCompLaserMulti::TLaserData &laser);


private:
	std::shared_ptr < InnerModel > innerModel;
	bool startup_check_flag;
    bool pared =false;


    //Declaramos el enum del estado del robot
    enum class State {IDLE, STRAIGHT, TURN, FOLLOW_WALL, SPIRAL};
    State state = State::IDLE;

    //Declaramos una tupla donde se alamacenarán los valores de adv, rot y State
    std::tuple<float, float> valores;



};

#endif
