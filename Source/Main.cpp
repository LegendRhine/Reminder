/*
================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2010 by SwingCoder
================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"


//==============================================================================
class SwingRemindApplication  : public JUCEApplication
{
public:
    //==============================================================================
    SwingRemindApplication()
    {
    }

    ~SwingRemindApplication()
    {
    }

    //==============================================================================
    void initialise (const String& /*commandLine*/)
    {
        LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("Microsoft YaHei");
        //LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("Arial Unicode MS");
        LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);

        mainWindow = new MainAppWindow();
    }

    void shutdown()
    {
        mainWindow = 0;
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        quit();
    }

    //==============================================================================
    const String getApplicationName()
    {
        return "SwingRemind";
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return true;
    }

    void anotherInstanceStarted (const String& /*commandLine*/)
    {
        
    }

private:
    ScopedPointer <MainAppWindow> mainWindow;
};

//==============================================================================
START_JUCE_APPLICATION(SwingRemindApplication)
