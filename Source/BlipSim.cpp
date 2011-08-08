#include "BlipSim.h"
#include "globals.h"
#include "OverflowTimer.h"

class BlipBoxThread : public Thread { 
public:
  BlipBoxThread() : Thread(T("BlipBox Simulator")) {}
  void run(){
    while(!threadShouldExit()){
      loop();
      yield();
    }
  }
};

extern "C" void SIG_USART_RECV();
extern "C" uint8_t UDR0;

void BlipSim::sendSerial(uint8_t* data, ssize_t size){
  for(int i=0; i<size; ++i){
    UDR0 = data[i];
    SIG_USART_RECV();    
  }
}

void BlipSim::initialise(){
  std::cout << "BlipSim::initialise" << std::endl;
  init();
  setup();
  blipbox.config.touchscreen_x_min = 0;
  blipbox.config.touchscreen_y_min = 0;
  blipbox.config.touchscreen_x_range = 1023;
  blipbox.config.touchscreen_y_range = 1023;
  blipthread = new BlipBoxThread();
  timer0 = new OverflowTimer(0.001);
}

void BlipSim::start(){
  blipthread->startThread();
  timer0->startThread();
  std::cout << "started threads" << std::endl;
}

void BlipSim::stop(){
  blipthread->stopThread(100);
  timer0->stopThread(100);
  std::cout << "stopped threads" << std::endl;
}

void BlipSim::shutdown(){
  stop();
  deleteAndZero(timer0);
  deleteAndZero(blipthread);
}
