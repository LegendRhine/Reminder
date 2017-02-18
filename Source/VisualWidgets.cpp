/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "VisualWidgets.h"
#include "SoundPlayer.h"
#include "DateAndTime.h"

//==================================================================================
VisualWidgets::VisualWidgets () : 
    isStop(true), totalSec(/*60 * 60*/5), currentSec(0), progressValue(1.0), processbar(nullptr)
{
    // add currentTimingLb to display current time..
    currentTimingLb = new Label();
    addAndMakeVisible(currentTimingLb);
    currentTimingLb->setFont (Font (50.0f, Font::bold));
    currentTimingLb->setJustificationType (Justification::centred);
	currentTimingLb->setText(showTime(), dontSendNotification);

    // add current date and time label..
    dateAndTimeLb = new Label();
    addAndMakeVisible(dateAndTimeLb);
    dateAndTimeLb->setFont(Font(18.0f));    
    dateAndTimeLb->setJustificationType(Justification::centred);
    dateAndTimeLb->setText(DateAndTime::getDateAndTime(true), dontSendNotification);

    // add processBar.. 
    processbar = new ProgressBar(progressValue);
    addAndMakeVisible(processbar);
    processbar->setPercentageDisplay(false);
    processbar->setColour(ProgressBar::foregroundColourId, Colours::green);
   
    Image img;

    // add buttons.
    for (int i = 0, x = 0; i < NUMS; ++i, x += 58)
    {
        bts.add(new ImageButton());
        addAndMakeVisible(bts[i]);
        bts[i]->addListener(this);
        bts[i]->setBounds(x, 5, 48, 48);

        // get each button's image..
        switch(i)
        {
        case SETUP:
            img = ImageCache::getFromMemory(BinaryData::setup_gif, BinaryData::setup_gifSize);
            break;

        case VIEW:
            img = ImageCache::getFromMemory(BinaryData::view_gif, BinaryData::view_gifSize);
            break;

        case STARTANDPAUSE:
            img = ImageCache::getFromMemory(BinaryData::start_gif, BinaryData::start_gifSize);
            break;

        case STOP:
            img = ImageCache::getFromMemory(BinaryData::stop_gif, BinaryData::stop_gifSize);
            break;

        case ABOUT:
            img = ImageCache::getFromMemory(BinaryData::about_gif, BinaryData::about_gifSize);
            break;

        default:
            break;
        }

        // set each button's image..
        bts[i]->setImages(false, false, false, 
            img, 1.0f, Colour(0x0), 
            img, 1.0f, Colours::yellow.withAlpha(0.3f), 
            img, 1.0f, Colours::red.withAlpha(0.4f));
    }

    bts[SETUP]->setTooltip(L"设置工作时间");
    bts[STARTANDPAUSE]->setTooltip(L"开始/暂停");
    bts[STOP]->setTooltip(L"停止提醒");
    bts[ABOUT]->setTooltip(L"关于");
    bts[ABOUT]->addShortcut(KeyPress(KeyPress::spaceKey));

    dateAndTimeLb->setTooltip(L"当前日期和时间");
    currentTimingLb->setTooltip(L"剩余时间");
    processbar->setTooltip(L"进度指示条");

    setSize(NUMS * 58, 160);
    setVisible(true);

    // position labels and processBar.
    dateAndTimeLb->setBounds(0, bts[0]->getBottom() + 5 , getWidth(), 25);
    processbar->setBounds(0, dateAndTimeLb->getBottom() + 5, getWidth(), 10);    
    currentTimingLb->setBounds(0, processbar->getBottom(), getWidth(), 50);

    // 记录启动时间点
    String s = DateAndTime::getTime(false, true);
    timePoint.add(s);

    startTimer(1000);
}
//==================================================================================
VisualWidgets::~VisualWidgets()
{
    deleteAndZero(currentTimingLb);
    deleteAndZero(dateAndTimeLb);
    deleteAndZero(processbar);
}
//==================================================================================
void VisualWidgets::buttonClicked(Button* button)
{
    // start/pause button..
    if (bts[STARTANDPAUSE] == button)
    {
        if (isStop)
            isStop = false;
        else
            isStop = true;            

        setImgOfStartBt(isStop);
    }
    // stop timing..
    else if (bts[STOP] == button && !isStop)
    {
        if (AlertWindow::showOkCancelBox (AlertWindow::QuestionIcon, 
            L"询问", L"要停止提醒吗？", L"确认", L"取消", this, nullptr))
        {
            isStop = true;
            setImgOfStartBt(true);
            currentSec = 0;
            progressValue = 1.0;
        }             
    }
    // setup button, pop-up menu for setup time.
    else if (bts[SETUP] == button)
    {
        setupTime();
    }
    // about button..
    else if (bts[ABOUT] == button)
    {
        String s = TRANS(L"作者");
        s << ": SwingCoder" << "\n" <<
            TRANS("E-mail") << ": underwaySoft@126.com" << "\n\n" << 
            TRANS(L"(C)2010 版权所有");

        AlertWindow::showMessageBoxAsync (AlertWindow::InfoIcon,
            L"关于...", s, L"确定");
    }
    // 查看本次运行期间的休息时间点
    else if (bts[VIEW] == button)
    {
        viewTimePoint();
    }
}
//==================================================================================
void VisualWidgets::timerCallback()
{
    if (!isStop)
    {  
        ++currentSec;
        progressValue = (totalSec - currentSec) / double(totalSec);
    }

    if (currentSec > totalSec)  // time's up..
    {
        isStop = true;
        currentSec = 0;
        setImgOfStartBt(true); 
        remind();
    }
    
    dateAndTimeLb->setText(DateAndTime::getDateAndTime(true), dontSendNotification);
    currentTimingLb->setText(showTime(), dontSendNotification);
}
//==================================================================================
void VisualWidgets::setImgOfStartBt( bool willStart )
{
    Image img;

    if (willStart)
        img = ImageCache::getFromMemory(BinaryData::start_gif, BinaryData::start_gifSize);
    else
        img = ImageCache::getFromMemory(BinaryData::pause_gif, BinaryData::pause_gifSize);

    bts[STARTANDPAUSE]->setImages(false, false, false, 
        img, 1.0f, Colour(0x0), 
        img, 1.0f, Colours::yellow.withAlpha(0.3f), 
        img, 1.0f, Colours::red.withAlpha(0.4f));
}
//==================================================================================
const String VisualWidgets::showTime() const
{
    int cs = totalSec - currentSec;

    if (cs < 0)
        cs = 0;
    
    int hours = cs / 3600;
    int mins = cs / 60 % 60;
    int secs = cs % 60;

    String s;
    s << String (hours).paddedLeft ('0', 2) << " : "
        << String (mins).paddedLeft ('0', 2) << " : "
        << String (secs).paddedLeft ('0', 2);

    return s;
}
//==================================================================================
void VisualWidgets::remind()
{
    ScopedPointer<SoundPlayer> soundPlayer = new SoundPlayer();

    MemoryInputStream* audioStream = new MemoryInputStream
        (BinaryData::loop_ogg, BinaryData::loop_oggSize, false);
    
    soundPlayer->play(audioStream);

    AlertWindow::showMessageBox(AlertWindow::WarningIcon,
        L"时间到！", L"该活动活动筋骨了！", L"确定");

    timePoint.add(DateAndTime::getTime(false, true));
}
//==================================================================================
void VisualWidgets::setupTime()
{
    PopupMenu m;

    for (int i = 1; i < 11; ++i)
    {
        m.addItem(i, String(i * 30) + L" 分钟", true, (totalSec / (30 * 60)) == i);
    }

    int result = m.show();

    // To prevent automatically to 0 which empty click.
    if (result > 0)
    {
        totalSec = result * 30 * 60;
    }

    currentTimingLb->setText(showTime(), dontSendNotification);
}
//==================================================================================
void VisualWidgets::viewTimePoint()
{
    PopupMenu m;

    for (int i = 0; i < timePoint.size(); ++i)
    {
        m.addItem(i + 1, "(" + String(i) + ") - " + timePoint[i]);
    }

    m.show();
}

//==================================================================================


