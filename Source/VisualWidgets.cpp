/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2010 by SwingCoder
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
    currentTimingLb->setFont (Font (45.0f, Font::bold));
	currentTimingLb->setColour (Label::textColourId, Colours::lightgrey);
    currentTimingLb->setJustificationType (Justification::centred);
	currentTimingLb->setText(showTime(), dontSendNotification);

    // add current date and time label..
    dateAndTimeLb = new Label();
    addAndMakeVisible(dateAndTimeLb);
    dateAndTimeLb->setFont(Font(18.0f));    
	dateAndTimeLb->setColour (Label::textColourId, Colours::lightgrey);
    dateAndTimeLb->setJustificationType(Justification::centred);
    dateAndTimeLb->setText(DateAndTime::getDateAndTime(true), dontSendNotification);

    // add processBar.. 
    processbar = new ProgressBar(progressValue);
    addAndMakeVisible(processbar);
    processbar->setPercentageDisplay(false);
	processbar->setColour(ProgressBar::foregroundColourId, Colours::cyan);
	processbar->setColour(ProgressBar::backgroundColourId, Colours::darkgrey.withAlpha(0.6f));
   
    Image img;

    // add buttons.
    for (int i = 0, x = 10; i < NUMS; ++i, x += 68)
    {
        bts.add(new ImageButton());
        addAndMakeVisible(bts[i]);
        bts[i]->addListener(this);
        bts[i]->setBounds(x, 10, 48, 48);

        // get each button's image..
        switch(i)
        {
        case SETUP:
            img = ImageCache::getFromMemory(BinaryData::setup_png, BinaryData::setup_pngSize);
            break;

        case VIEW:
            img = ImageCache::getFromMemory(BinaryData::view_png, BinaryData::view_pngSize);
            break;

        case STARTANDPAUSE:
            img = ImageCache::getFromMemory(BinaryData::start_png, BinaryData::start_pngSize);
            break;

        case STOP:
            img = ImageCache::getFromMemory(BinaryData::stop_png, BinaryData::stop_pngSize);
            break;

        case ABOUT:
            img = ImageCache::getFromMemory(BinaryData::about_png, BinaryData::about_pngSize);
            break;

        default:
            break;
        }

        // set each button's image..
        bts[i]->setImages(false, false, false, 
            img, 1.0f, Colour(0x0), 
            img, 1.0f, Colours::yellowgreen.withAlpha(0.6f), 
			img, 1.0f, Colours::yellowgreen.withAlpha(0.6f));
    }

    bts[SETUP]->setTooltip(L"设置工作时间");
    bts[STARTANDPAUSE]->setTooltip(L"开始/暂停");
    bts[STOP]->setTooltip(L"停止提醒");
    bts[VIEW]->setTooltip(L"查看提醒记录");
    bts[ABOUT]->setTooltip(L"关于");
    bts[ABOUT]->addShortcut(KeyPress(KeyPress::spaceKey));

    dateAndTimeLb->setTooltip(L"当前日期和时间");
    currentTimingLb->setTooltip(L"剩余时间");
    processbar->setTooltip(L"进度指示条");

    setSize(NUMS * 68, 200);
    setVisible(true);

    // position labels and processBar.
    dateAndTimeLb->setBounds(0, bts[0]->getBottom() + 15 , getWidth(), 25);
    processbar->setBounds(0, dateAndTimeLb->getBottom() + 25, getWidth(), 10);    
    currentTimingLb->setBounds(0, processbar->getBottom() + 10, getWidth(), 50);

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
        img = ImageCache::getFromMemory(BinaryData::start_png, BinaryData::start_pngSize);
    else
        img = ImageCache::getFromMemory(BinaryData::pause_png, BinaryData::pause_pngSize);

    bts[STARTANDPAUSE]->setImages(false, false, false, 
        img, 1.0f, Colour(0x0), 
		img, 1.0f, Colours::yellowgreen.withAlpha(0.6f), 
        img, 1.0f, Colours::yellowgreen.withAlpha(0.6f));
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


