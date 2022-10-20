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
#include "specificworker.h"
/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(TuplePrx tprx, bool startup_check) : GenericWorker(tprx)
{
	this->startup_check_flag = startup_check;
	// Uncomment if there's too many debug messages
	// but it removes the possibility to see the messages
	// shown in the console with qDebug()
//	QLoggingCategory::setFilterRules("*.debug=false\n");
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	std::cout << "Destroying SpecificWorker" << std::endl;
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
//	THE FOLLOWING IS JUST AN EXAMPLE
//	To use innerModelPath parameter you should uncomment specificmonitor.cpp readConfig method content
//	try
//	{
//		RoboCompCommonBehavior::Parameter par = params.at("InnerModelPath");
//		std::string innermodel_path = par.value;
//		innerModel = std::make_shared(innermodel_path);
//	}
//	catch(const std::exception &e) { qFatal("Error reading config params"); }






	return true;
}

void SpecificWorker::initialize(int period)
{
	std::cout << "Initialize worker" << std::endl;
	this->Period = period;
	if(this->startup_check_flag)
	{
		this->startup_check();
	}
	else
	{
		timer.start(Period);
	}

}

void SpecificWorker::compute() {

    RoboCompLaserMulti::TLaserData ldata;
    //El robot siente
    try
    {
        ldata = lasermulti_proxy->getLaserData(2);
    }catch (const Ice::Exception &e) {std::cout << e.what() << std::endl; return;};

    switch(state)
    {
        case State::IDLE:
            valores=IDLE_function(ldata);
            break;
        case State::STRAIGHT:
            valores=FORWARD_function(ldata);
            break;
        case State::TURN:
            valores=TURN_function(ldata);
            break;
        case State::FOLLOW_WALL:
            valores= follow_wall_method(ldata);
            break;
        case State::SPIRAL:
            valores= SPIRAL_function(ldata);
            break;
    }


    try
    {
        differentialrobotmulti_proxy->setSpeedBase(2,get<0>(valores),get<1>(valores));
    }catch (const Ice::Exception &e) {std::cout << e.what() << std::endl;};
}

std::tuple<float, float> SpecificWorker::IDLE_function(const RoboCompLaserMulti::TLaserData &ldata)
{
    std::cout << "Estado: IDLE" << std::endl;
    std::tuple<float, float> tuplaAdevolver;
    tuplaAdevolver=make_tuple(MAX_ADV, 0);
    state=State::STRAIGHT;

    return tuplaAdevolver;
}

std::tuple<float, float> SpecificWorker::FORWARD_function(const RoboCompLaserMulti::TLaserData &ldata)
{
    std::cout << "Estado: FORWARD" << std::endl;
    std::tuple<float, float> tuplaAdevolver;


    //Inicializamos con los valores que ya tenia la tupla anteriormente por si no hay cambio
    tuplaAdevolver = make_tuple(get<0>(valores), get<1>(valores));

    const int partesVector = 3;
    //ordenar por distancia la sección control de lalser
    RoboCompLaserMulti::TLaserData parteCentral(ldata.begin() + ldata.size() / partesVector,ldata.end() - ldata.size() / partesVector);
    std::ranges::sort(parteCentral, {}, &RoboCompLaserMulti::TData::dist);
    cout<<"VELOCIDAD HORLEWILL: "<<get<0>(valores)<<endl;
    //Si hay un choque inminente (La menor distancia es menor que 1000 seleccionamos el estado TURN)
    if (parteCentral.front().dist < 1100) {
        state=State::TURN;
        if (GirarIzquierda(ldata))
        {
            tuplaAdevolver= make_tuple(0, -0.4);
            std::cout<<"GIRARIZQUIERDA"<<std::endl;
        }
        else
        {
            tuplaAdevolver= make_tuple(0, 0.4);
            std::cout<<"GIRARDERECHA"<<std::endl;
        }
    }
    else
    {
        //LLAMADA AL ESTADO ESPIRAL
    }

    //Si la menor de las distancias es mayor que 1200 quiere decir que hay mucho espacio libre, por tanto pasamos a espiral
    RoboCompLaserMulti::TLaserData laserCompleto(ldata.begin(), ldata.end());
    std::ranges::sort(laserCompleto, {}, &RoboCompLaserMulti::TData::dist);
    /*if (laserCompleto.front().dist > 1200) {
        tuplaAdevolver = make_tuple(1100, -0.7);
        state = State::SPIRAL;
    }*/
    return tuplaAdevolver;
}

std::tuple<float, float> SpecificWorker::TURN_function(const RoboCompLaserMulti::TLaserData &ldata) {
    std::cout << "Estado: TURN" << std::endl;
    std::tuple<float, float> tuplaAdevolver;

    const int partesVector = 3;

    //Inicializamos con los valores que ya tenia la tupla anteriormente por si no hay cambio
    tuplaAdevolver = make_tuple(get<0>(valores), get<1>(valores));
    if (hayQueSeguirLaPared(ldata) && pared==false)
    {
        state=State::FOLLOW_WALL;
        RoboCompLaserMulti::TLaserData parteCentral(ldata.begin()+ldata.size()/partesVector, ldata.end()-ldata.size()/partesVector);
        std::ranges::sort(parteCentral, {}, &RoboCompLaserMulti::TData::dist);

        if(parteCentral.front().dist<1100) {
            if (GirarIzquierda(ldata)) {
                tuplaAdevolver = make_tuple(0, -0.9);
                std::cout << "GIRARIZQUIERDA" << std::endl;
            } else {
                tuplaAdevolver = make_tuple(0, 0.9);
                std::cout << "GIRARDERECHA" << std::endl;
            }
        }
    }
    else {
        //ordenar por distancia la sección control de lalser
        RoboCompLaserMulti::TLaserData parteCentral(ldata.begin()+ldata.size()/partesVector, ldata.end()-ldata.size()/partesVector);
        std::ranges::sort(parteCentral, {}, &RoboCompLaserMulti::TData::dist);
        //si hay espacio libre delante del robot se selecciona el método forward
        if (parteCentral.front().dist > 1100) {
            state = State::STRAIGHT;
            tuplaAdevolver = make_tuple(MAX_ADV, 0);
            pared=false; //Dejamos libre la bandera para que pueda volver otra vez a entrar en el estado
        }else
        {
            pared=false; //Dejamos libre la bandera para que pueda volver otra vez a entrar en el estado
            if (GirarIzquierda(ldata)) {
                tuplaAdevolver = make_tuple(0, -0.9);
                std::cout << "GIRARIZQUIERDA" << std::endl;
            } else {
                tuplaAdevolver = make_tuple(0, 0.9);
                std::cout << "GIRARDERECHA" << std::endl;
            }
        }
    }

    return tuplaAdevolver;
}

std::tuple<float, float> SpecificWorker::SPIRAL_function(const RoboCompLaserMulti::TLaserData &ldata) {
    std::cout << "Estado: SPIRAL" << std::endl;

    std::tuple<float, float> tuplaAdevolver;

    //Inicializamos con los valores que ya tenia la tupla anteriormente por si no hay cambio
    tuplaAdevolver=make_tuple(get<0>(valores), get<1>(valores));

    const int partesVector=4;
    //ordenar por distancia la sección control de lalser
    RoboCompLaserMulti::TLaserData parteCentral(ldata.begin()+ldata.size()/partesVector, ldata.end()-ldata.size()/partesVector);
    std::ranges::sort(parteCentral, {}, &RoboCompLaserMulti::TData::dist);

    //si hay un obstaculo se selecciona el método turn
    if(parteCentral.front().dist < 1000)
    {
        state=State::TURN;
        if (GirarIzquierda(ldata))
        {
            tuplaAdevolver= make_tuple(0, -0.8);
            std::cout<<"GIRARIZQUIERDA"<<std::endl;
        }
        else
        {
            tuplaAdevolver= make_tuple(0, 0.8);
            std::cout<<"GIRARDERECHA"<<std::endl;
        }
    }

    return tuplaAdevolver;
}


std::tuple<float, float> SpecificWorker:: follow_wall_method(const RoboCompLaserMulti::TLaserData &ldata)
{
    static bool first_time = true;
    static auto start = std::chrono::system_clock::now();

    bool noEvaluo=false;

    std::cout << "Estado: SEGUIR PARED" << std::endl;
    std::tuple<float, float> tuplaAdevolver;
    int partesVector=3;
    //ordenar por distancia la sección control de lalser
    RoboCompLaserMulti::TLaserData parteCentral(ldata.begin()+ldata.size()/partesVector, ldata.end()-ldata.size()/partesVector);
    std::ranges::sort(parteCentral, {}, &RoboCompLaserMulti::TData::dist);

    if (first_time !=true)
    {
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float,std::milli> duration = end - start;
        if(duration.count() > 10000)
        {
            pared=true; //Ponemos pared a true para que no entre de nuevo en este estado por el turn y pueda salir a un estado distinto
            first_time=true;
            state=State::TURN;
            noEvaluo=true;
            tuplaAdevolver = make_tuple(0, 0);
        }
    }

    if (noEvaluo==false) {
        first_time = false;
        if (parteCentral.front().dist < 1100) {
            state = State::TURN;
        } else { //ESta parte corrige trayectoria y se debe de hacer aqui y no en el turn
            partesVector = 2;
            //Si la distancia a la pared por la parte izquierda o derecha es menor que 300 esta en pared y tiene que seguirla
            RoboCompLaserMulti::TLaserData parteIzquierda(ldata.begin(), ldata.end() - (ldata.size() / partesVector));
            std::ranges::sort(parteIzquierda, {}, &RoboCompLaserMulti::TData::dist);
            if (calcularMediaLaser(parteIzquierda) > 200) {
                std::cout << "corrigiendo trayecto" << std::endl;
                tuplaAdevolver = make_tuple(800, 0.1);
            } else {
                RoboCompLaserMulti::TLaserData parteDerecha(ldata.begin(), ldata.end() - (ldata.size() / partesVector));
                std::ranges::sort(parteDerecha, {}, &RoboCompLaserMulti::TData::dist);
                if (calcularMediaLaser(parteDerecha) > 200) {
                    std::cout << "corriegiendo trayecto" << std::endl;
                    tuplaAdevolver = make_tuple(800, -0.1);
                } else {
                    tuplaAdevolver = make_tuple(MAX_ADV, 0);
                }
            }
        }
    }
    noEvaluo=false;
    return tuplaAdevolver;
}

bool SpecificWorker::GirarIzquierda(const RoboCompLaserMulti::TLaserData &ldata)
{
    bool giroIzquierda = false;
    const int partesVector=3;
    float mediaIzquierda, mediaDerecha;
    //ordenar por distancia la sección control de laser
    RoboCompLaserMulti::TLaserData parteIzquierda(ldata.begin(), ldata.end()-2*(ldata.size()/partesVector));
    RoboCompLaserMulti::TLaserData parteDerecha(ldata.begin()+2*(ldata.size()/partesVector), ldata.end());
    mediaIzquierda=calcularMediaLaser(parteIzquierda);
    mediaDerecha= calcularMediaLaser(parteDerecha);

    if (mediaIzquierda < mediaDerecha)
    {
        giroIzquierda=true;
    }
    return giroIzquierda;
}


bool SpecificWorker::hayQueSeguirLaPared(const RoboCompLaserMulti::TLaserData &ldata)
{
    bool bandera=false;
    int partesVector=3;
    //Si la distancia a la pared por la parte izquierda o derecha es menor que 300 esta en pared y tiene que seguirla
    RoboCompLaserMulti::TLaserData parteCentral(ldata.begin()+(ldata.size()/partesVector), ldata.end()-(ldata.size()/partesVector));
    std::ranges::sort(parteCentral, {}, &RoboCompLaserMulti::TData::dist);


    partesVector=2;
    //Si la distancia a la pared por la parte izquierda o derecha es menor que 300 esta en pared y tiene que seguirla
    RoboCompLaserMulti::TLaserData parteIzquierda(ldata.begin(), ldata.end()-(ldata.size()/partesVector));
    std::ranges::sort(parteIzquierda, {}, &RoboCompLaserMulti::TData::dist);
    if(calcularMediaLaser(parteIzquierda) > 500)
    {
        bandera=true;
    }

    RoboCompLaserMulti::TLaserData parteDerecha(ldata.begin()+(ldata.size()/partesVector), ldata.end());
    std::ranges::sort(parteDerecha, {}, &RoboCompLaserMulti::TData::dist);
    if(calcularMediaLaser(parteDerecha) > 500)
    {
        bandera=true;
    }

    return bandera;
}


float SpecificWorker::calcularMediaLaser(const RoboCompLaserMulti::TLaserData &laser)
{
    float media=0.0;

   for(auto it = laser.begin(); it != laser.end(); it++)
    {
        media += it->dist;
    }
    media = media / laser.size();
    return media;
}


int SpecificWorker::startup_check()
{
	std::cout << "Startup check" << std::endl;
	QTimer::singleShot(200, qApp, SLOT(quit()));
	return 0;
}



/**************************************/
// From the RoboCompDifferentialRobot you can call this methods:
// this->differentialrobot_proxy->correctOdometer(...)
// this->differentialrobot_proxy->getBasePose(...)
// this->differentialrobot_proxy->getBaseState(...)
// this->differentialrobot_proxy->resetOdometer(...)
// this->differentialrobot_proxy->setOdometer(...)
// this->differentialrobot_proxy->setOdometerPose(...)
// this->differentialrobot_proxy->setSpeedBase(...)
// this->differentialrobot_proxy->stopBase(...)

/**************************************/
// From the RoboCompDifferentialRobot you can use this types:
// RoboCompDifferentialRobot::TMechParams

/**************************************/
// From the RoboCompLaser you can call this methods:
// this->laser_proxy->getLaserAndBStateData(...)
// this->laser_proxy->getLaserConfData(...)
// this->laser_proxy->getLaserData(...)

/**************************************/
// From the RoboCompLaser you can use this types:
// RoboCompLaser::LaserConfData
// RoboCompLaser::TData

