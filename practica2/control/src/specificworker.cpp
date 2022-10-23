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
        ldata = lasermulti_proxy->getLaserData(1);
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
        differentialrobotmulti_proxy->setSpeedBase(1,get<0>(valores),get<1>(valores));
    }catch (const Ice::Exception &e) {std::cout << e.what() << std::endl;};
}

std::tuple<float, float> SpecificWorker::IDLE_function(const RoboCompLaserMulti::TLaserData &ldata)
{
    std::cout << "Estado: IDLE" << std::endl;
    std::tuple<float, float> tuplaAdevolver;
    tuplaAdevolver=make_tuple(consts.MAX_ADV, 0);
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
    if (parteCentral.front().dist < 1300) {
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
        RoboCompLaserMulti::TLaserData laserCompleto(ldata.begin(), ldata.end());
        std::ranges::sort(laserCompleto, {}, &RoboCompLaserMulti::TData::dist);
        if (laserCompleto.front().dist > 1200) {
            state = State::SPIRAL;
            tuplaAdevolver = make_tuple(1, consts.MAX_ROT);
        }
    }


    return tuplaAdevolver;
}

std::tuple<float, float> SpecificWorker::TURN_function(const RoboCompLaserMulti::TLaserData &ldata) {
    std::cout << "Estado: TURN" << std::endl;
    std::tuple<float, float> tuplaAdevolver;
    static int partesVector=3;
    static int derecha=0;

    static bool inicioTurn = true;  //SOlo generamos numeros aleatorios al inicio del giro

    //Inicializamos con los valores que ya tenia la tupla anteriormente por si no hay cambio
    tuplaAdevolver = make_tuple(get<0>(valores), get<1>(valores));

    srand(time(NULL));
    static int aleatorio =rand() % 2;

    if (pared==true && inicioTurn==true)
    {
        std::cout<<"regenerando aleatorio"<<std::endl;
        aleatorio =rand() % 2;
        inicioTurn=false;
        pared=false; //Dejamos libre la bandera para que pueda volver otra vez a entrar en el estado
    }

    std::cout<<aleatorio<<std::endl;

    if (aleatorio && hayQueSeguirLaPared(ldata)) //NO tiene sentido que se siga una pared en la mitad del mapa,. por eso aparte de generar el aleatorio
                                                 //Se comprueba que se pueda seguir pared
    {
        RoboCompLaserMulti::TLaserData parteCentral(ldata.begin()+ldata.size()/partesVector, ldata.end()-ldata.size()/partesVector);
        std::ranges::sort(parteCentral, {}, &RoboCompLaserMulti::TData::dist);

        if(parteCentral.front().dist<1300) {
            if (GirarIzquierda(ldata) && derecha==0) {
                tuplaAdevolver = make_tuple(0, -0.5);
                std::cout << "GIRARIZQUIERDA" << std::endl;
            } else {
                derecha=1;
                tuplaAdevolver = make_tuple(0, 0.5);
                std::cout << "GIRARDERECHA" << std::endl;
            }
        }else
        {
            derecha=0;
            state=State::FOLLOW_WALL;
            tuplaAdevolver = make_tuple(consts.MAX_ADV, 0);
            inicioTurn=true; //CAmbiamos de estado ya no hay que mantener la rotación sin generar numero aleatorio
        }
    }
    else {
        pared=true;
        //pared=false; //Dejamos libre la bandera para que pueda volver otra vez a entrar en el estado
        //ordenar por distancia la sección control de lalser
        RoboCompLaserMulti::TLaserData parteCentral(ldata.begin()+ldata.size()/partesVector, ldata.end()-ldata.size()/partesVector);
        std::ranges::sort(parteCentral, {}, &RoboCompLaserMulti::TData::dist);
        //si hay espacio libre delante del robot se selecciona el método forward
        if (parteCentral.front().dist > 1100) {
            derecha=0;  //evita el baile de la J
            inicioTurn=true; //CAmbiamos de estado ya no hay que mantener la rotación sin generar numero aleatorio
            state = State::STRAIGHT;
            tuplaAdevolver = make_tuple(consts.MAX_ADV, 0);
        }else
        {
            if (GirarIzquierda(ldata) && derecha==0) {
                tuplaAdevolver = make_tuple(0, -0.5);
                std::cout << "GIRARIZQUIERDA" << std::endl;
            } else {
                derecha = 1;
                tuplaAdevolver = make_tuple(0, 0.5);
                std::cout << "GIRARDERECHA" << std::endl;
            }
        }
    }

    return tuplaAdevolver;
}

std::tuple<float, float> SpecificWorker::SPIRAL_function(RoboCompLaserMulti::TLaserData &ldata)
{
    const int part = 3;
    static float spiralAvance=1.0;
    static float spiralRot=consts.MAX_ROT;
    RoboCompLaserMulti::TLaserData parteCentral(ldata.begin()+ldata.size()/part, ldata.end()-ldata.size()/part);
    std::ranges::sort(parteCentral, {},&RoboCompLaserMulti::TData::dist);

    qInfo() <<"SPIRAL:"<< " distancia:" <<parteCentral.front().dist;

    tuple<float, float> tuplaAdevolver = make_tuple(spiralAvance, spiralRot);

    if(parteCentral.front().dist < 1300)
    {
        state = State::TURN;
        spiralAvance=1.0;
        spiralRot=consts.MAX_ROT;
        tuplaAdevolver = make_tuple(0, 0);
    }
    else {
        if(spiralAvance < consts.MAX_ADV && spiralRot > 0)
        {
            sleep(1);
            spiralAvance+=50;
            spiralRot-=0.03;
        }else
        {
            state = State::STRAIGHT;
            tuplaAdevolver = make_tuple(consts.MAX_ADV, 0);
        }
    }

    return tuplaAdevolver;
}


std::tuple<float, float> SpecificWorker:: follow_wall_method(const RoboCompLaserMulti::TLaserData &ldata)
{
    static bool first_time = true;
    static std::chrono::time_point<std::chrono::system_clock> start;

    if(first_time == true)
    {
        start = std::chrono::system_clock::now();
    }

    bool noEvaluo=false;

    std::cout << "Estado: SEGUIR PARED" << std::endl;
    std::tuple<float, float> tuplaAdevolver;
    const int partesVector=3;
    //ordenar por distancia la sección control de laser
    RoboCompLaserMulti::TLaserData parteCentral(ldata.begin()+ldata.size()/partesVector, ldata.end()-ldata.size()/partesVector);
    std::ranges::sort(parteCentral, {}, &RoboCompLaserMulti::TData::dist);
    RoboCompLaserMulti::TLaserData parteIzquierda(ldata.begin(), ldata.end()-2*(ldata.size()/partesVector));
    std::ranges::sort(parteIzquierda, {}, &RoboCompLaserMulti::TData::dist);
    RoboCompLaserMulti::TLaserData parteDerecha(ldata.begin()+2*(ldata.size()/partesVector), ldata.end());
    std::ranges::sort(parteDerecha, {}, &RoboCompLaserMulti::TData::dist);

    if (first_time !=true)
    {
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float,std::milli> duration = end - start;
        std::cout<<duration.count()<<std::endl;
        if(duration.count() > 5000)
        {
            std::cout<<"sale del seguir pared"<<std::endl;
            pared=true; //Ponemos pared a true para que no entre de nuevo en este estado por el turn y pueda salir a un estado distinto
            first_time=true;
            state=State::TURN;
            noEvaluo=true;
            if (calcularMediaLaser(parteIzquierda) < calcularMediaLaser(parteDerecha)) { //Esto se hace para que cuando vaya a salir del estado
                tuplaAdevolver = make_tuple(consts.MAX_ADV, -0.8);                                         //no se quede al lado de la pared y salga para alante, de
            }                                                                                       //de manera que no vuelva a segir la pared.
            else{                                                                                   //Para ello le metemos una rotación contrario al lado de la
                tuplaAdevolver = make_tuple(consts.MAX_ADV, +0.8);                                         //pared.
            }
        }
    }

    if (noEvaluo==false) {
        first_time = false;
        if (parteCentral.front().dist < 1300) {
            state = State::TURN;
        } else
        { //ESta parte corrige trayectoria y se debe de hacer aqui y no en el turn
            std::cout<<"Corregir trayecto"<<std::endl;

            //Los laser estan cambiado de sentido
            std::cout << "MEDIADERECHA: "<<calcularMediaLaser(parteIzquierda) << std::endl;
            std::cout << "MEDIAIZQUIERDA: "<<calcularMediaLaser(parteDerecha) << std::endl;

            if (calcularMediaLaser(parteIzquierda) < calcularMediaLaser(parteDerecha)) { //Tengo la pared a la derecha
                if (calcularMediaLaser(parteIzquierda) > 900 + consts.DELTA) {
                    std::cout << "girando a la derecha pared a la derecha" << std::endl;
                    tuplaAdevolver = make_tuple(consts.MAX_ADV, 0.2); //-----------------
                } else {
                    if (calcularMediaLaser(parteIzquierda) < 900 - consts.DELTA) {
                        std::cout << "girando a la izquierda pared a la derecha" << std::endl;
                        tuplaAdevolver = make_tuple(consts.MAX_ADV, -0.2); //--------------
                    }
                    else{
                        tuplaAdevolver = make_tuple(consts.MAX_ADV, 0);
                    }
                }
            }
            else{   //Tengo la pared a la izquierda
                if (calcularMediaLaser(parteDerecha) > 900 + consts.DELTA) {
                    std::cout << "girando a la izquierda pared a la izquierda" << std::endl;
                    tuplaAdevolver = make_tuple(consts.MAX_ADV, -0.2);  //------------------
                } else {
                    if (calcularMediaLaser(parteDerecha) < 900 - consts.DELTA) {
                        std::cout << "girando a la derecha pared a la izquierda" << std::endl;
                        tuplaAdevolver = make_tuple(consts.MAX_ADV, 0.2);  //----------------------
                    }
                    else{
                        tuplaAdevolver = make_tuple(consts.MAX_ADV, 0);
                    }
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

