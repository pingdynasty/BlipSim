#ifndef __BLIPSIM_H__
#define __BLIPSIM_H__

#include "../JuceLibraryCode/JuceHeader.h"

class BlipSim {
private:
  Thread* blipthread;
  Thread* timer0;
public:
  BlipSim(){}
  void initialise();
  void shutdown();
};

#endif  // __BLIPSIM_H_
