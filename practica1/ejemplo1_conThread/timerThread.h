//
// Created by oem on 26/09/22.
//

#ifndef EJEMPLO1_TIMERTHREAD_H
#define EJEMPLO1_TIMERTHREAD_H
#include <thread>
#include <chrono>
#include <functional>
#include <future>
#include <cstdio>
#include <iostream>
using namespace std;

class timerThread {
public:
    timerThread(){};

    template <class callable>
    void connect(callable&& f)
    {
        thread([=]()
                    {
                        while(true)
                        {
                            if(go.load())
                                invoke(f);
                            this_thread::sleep_for(chrono::milliseconds(period.load()));
                        }
                    }).detach();
    };

    void start(int p)
    {
        period.store(p);
        go.store(true);
    };

    void stop() { go.store(!go); };
    void setPeriod(int p) { period.store(p) ;};

private:
    atomic_bool go = false;
    atomic_int period = 0;

};

#endif //EJEMPLO1_TIMERTHREAD_H
