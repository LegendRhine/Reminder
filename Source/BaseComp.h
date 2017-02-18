/*
================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
================================================================================
*/

// base component contain by main window.

#ifndef __BASECOMP_H_
#define __BASECOMP_H_

class VisualWidgets;

//==============================================================================
class BaseComp : public Component 
{
public:
    BaseComp ();
    ~BaseComp();

    void resized();
	void paint (Graphics& g) override;

private:
    //==========================================================================
     VisualWidgets* widgets;

     JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BaseComp)
};

#endif  // __BASECOMP_H_
