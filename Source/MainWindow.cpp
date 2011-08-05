/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic outline for a simple desktop window.

  ==============================================================================
*/

#include "MainWindow.h"
#include "BlipSimComponent.h"


//==============================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey,
                      DocumentWindow::allButtons, true)
{
    centreWithSize (500, 400);
    setVisible (true);
    setResizable(true, true); // resizable, with resize corner (instead of border)
    sim = new BlipSimComponent();
    setContentOwned(sim, true);
}

MainAppWindow::~MainAppWindow()
{
  deleteAndZero(sim);
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
