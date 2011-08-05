#include "SimScreen.h"

#include "globals.h"
#include "BlipBox.h"

static int row_count = 8;
static int column_count = 10;

SimScreen::SimScreen ()
{
  std::cout << "SimScreen " << isEnabled() << std::endl;
  setMouseCursor(MouseCursor::CrosshairCursor);
}

SimScreen::~SimScreen()
{
}

void SimScreen::mouseUp (const MouseEvent& e){
  std::cout << "SimScreen::mouseUp" << std::endl;
  blipbox.keys.setValue(0, 1023);
}

void SimScreen::mouseExit (const MouseEvent& e){
  std::cout << "SimScreen::mouseExit" << std::endl;
  blipbox.keys.setValue(0, 1023);
}

void SimScreen::position(const Point<float> p){
  float x = p.getX()/getWidth()*1024;
  float y = p.getY()/getHeight()*1024;
  blipbox.keys.setValue(1, x);
  blipbox.keys.setValue(2, y);
  blipbox.keys.setValue(0, 40);
}

void SimScreen::mouseDown (const MouseEvent& e)
{
  std::cout << "SimScreen::mouseDown" << std::endl;
  position(getMouseXYRelative().toFloat());
  Point<float> p = getMouseXYRelative().toFloat();
}

void SimScreen::mouseDrag (const MouseEvent& e)
{
  std::cout << "SimScreen::mouseDrag" << std::endl;
  position(getMouseXYRelative().toFloat());
}

void SimScreen::paint (Graphics& g)
{
  g.fillAll(Colours::black);
  Colour c = Colours::red;
  g.setColour(c);
  float width = std::min((float)getWidth()/column_count, (float)getHeight()/row_count)*0.8;
  float margin = width/2;
  g.setOrigin(margin, margin);
  float dx = (getWidth()-margin) / column_count;
  float dy = (getHeight()-margin) / row_count;
  for(int col=0; col<column_count; ++col){
    for(int row=0; row<row_count; ++row){
      g.setOpacity(0.4);
      g.drawEllipse(col*dx, row*dy, width, width, 4);
      uint8_t value = blipbox.leds.getLed(col, row_count-row-1);
//       g.setOpacity(blipbox.leds.getLed(col, row)/255.0);
//       g.setColour(c.withBrightness(blipbox.leds.getLed(col, row)/255.0));
      g.setOpacity(value/255.0);
      g.fillEllipse(col*dx, row*dy, width, width);
    }
  }
  repaint(); // continuously redraw...
}

void SimScreen::resized()
{
  
}
