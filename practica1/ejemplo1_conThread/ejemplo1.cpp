#include "ejemplo1.h"
using namespace std;

int valorSlider=500;
int valorDecrementar=0;

ejemplo1::ejemplo1(): Ui_Counter()
{
    setupUi(this);
    show();

    connect(start, SIGNAL(clicked()),this,SLOT(doStart()));
    connect(button, SIGNAL(clicked()), this, SLOT(doButton()));
    connect(reset, SIGNAL(clicked()), this, SLOT(doReset()));
    connect(decrementar, SIGNAL(clicked()),this,SLOT(cambiarDecrementar()));
    crono.connect(bind(&ejemplo1::fTimer, this));
    
    sliderPeriodo->setMaximum(1000);
    sliderPeriodo->setMinimum(10);
    sliderPeriodo->setValue(valorSlider);
    
    connect(sliderPeriodo,SIGNAL(valueChanged(int)),this,SLOT(cambiarSlider()));
}


void ejemplo1::cambiarSlider()
{
  valorSlider=sliderPeriodo->value();
  crono.stop();
  crono.start(valorSlider);
}

void ejemplo1::doReset()
{
    count=0;
  lcdNumber->display(count);
  crono.stop();
  
}

void ejemplo1::doStart()
{
  crono.start(valorSlider);
}

void ejemplo1::doButton()
{
    qDebug() << "click on button";
    qDebug() <<valorSlider;
    crono.stop();
}

void ejemplo1::cambiarDecrementar()
{
  if(valorDecrementar==0)
    valorDecrementar=1;
  else
    valorDecrementar=0;
}

void ejemplo1::fTimer(){
  if(valorDecrementar==0){
    lcdNumber->display(++count);
  }else{
    lcdNumber->display(--count);
  }
}



