/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2010 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "BaseComp.h"

//==================================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey, 5)
{
    // add baseComp.
    BaseComp* baseComp = new BaseComp();
    setContentOwned(baseComp, true);

    centreWithSize (baseComp->getWidth(), baseComp->getHeight());
    setTitleBarButtonsRequired(5, true);
    setUsingNativeTitleBar(true);
    setVisible (true);
}
//==================================================================================
MainAppWindow::~MainAppWindow()
{
}
//==================================================================================
void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
