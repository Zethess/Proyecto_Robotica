#ifndef ejemplo1_H
#define ejemplo1_H

#include <QtGui>
#include "ui_counterDlg.h"
#include "timerThread.h"

class ejemplo1 : public QWidget, public Ui_Counter
{
    Q_OBJECT
    public:
        ejemplo1();

    public slots:
        void doButton();
        void fTimer();
        void doStart();
        void doReset();
        void cambiarSlider();
        void cambiarDecrementar();

    private:
        timerThread crono;
        int count=0;
    
};

#endif // ejemplo1_H
