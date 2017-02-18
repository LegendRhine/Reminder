/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

// visual widgets of this application which used in BaseComp.

#ifndef __VISUALWIDGETS_H_
#define __VISUALWIDGETS_H_

//==================================================================================
class VisualWidgets : public Component, 
    public ButtonListener,
    private Timer
{
public:
    VisualWidgets ();
    ~VisualWidgets();

    void buttonClicked(Button* button);

private:
    //==============================================================================
    enum {SETUP = 0, VIEW, STARTANDPAUSE, STOP, ABOUT, NUMS};
    static const int timerCycle = 1000;   
    
    virtual void timerCallback();    
    void setImgOfStartBt(bool willStart);
    void setupTime();
    void viewTimePoint();
    const String showTime() const;
    void remind();

    OwnedArray<ImageButton> bts;
    Label* currentTimingLb; 
    Label* dateAndTimeLb;
    ProgressBar* processbar; 

    StringArray timePoint;

    int totalSec, currentSec;
    double progressValue;
    bool isStop;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualWidgets)        
};

#endif  // __VISUALWIDGETS_H_
