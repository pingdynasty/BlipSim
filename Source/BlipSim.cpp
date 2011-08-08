#include "BlipSim.h"
#include "globals.h"
#include "OverflowTimer.h"

class BlipBoxThread : public Thread { 
public:
  BlipBoxThread() : Thread(T("BlipBox Simulator")) {}
  void run(){
    while(!threadShouldExit()){
      loop();
    }
  }
};

void BlipSim::initialise(){
  std::cout << "BlipSim::initialise" << std::endl;
  init();
  setup();
  blipbox.config.touchscreen_x_min = 0;
  blipbox.config.touchscreen_y_min = 0;
  blipbox.config.touchscreen_x_range = 1023;
  blipbox.config.touchscreen_y_range = 1023;
  blipthread = new BlipBoxThread();
  blipthread->startThread();
  timer0 = new OverflowTimer(0.001);
  timer0->startThread();
  std::cout << "started threads" << std::endl;
}

void BlipSim::shutdown(){
  timer0->stopThread(100);
  deleteAndZero(timer0);
  blipthread->stopThread(100);
  std::cout << "stopped thread" << std::endl;
  deleteAndZero(blipthread);
}
