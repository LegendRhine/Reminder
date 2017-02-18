/*
================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
================================================================================
*/

// base component contain by main window.

#include "../JuceLibraryCode/JuceHeader.h"
#include "BaseComp.h"
#include "VisualWidgets.h"

//=========================================================================

BaseComp::BaseComp ()  
{
    // add widgets..
    widgets = new VisualWidgets();    
    addAndMakeVisible(widgets);
    
    setSize(widgets->getWidth() + 20, widgets->getHeight());
    setVisible(true);

    // position widgets.    
    widgets->setBounds(10, 0, widgets->getWidth(), widgets->getHeight());
}
//===========================================================================
BaseComp::~BaseComp()
{
    deleteAndZero(widgets);
}

//===========================================================================
void BaseComp::resized()
{
}

//===========================================================================
void BaseComp::paint (Graphics& g)
{
	//g.fillAll (Colours::darkgrey);
}


