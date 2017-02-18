/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2010 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

/** 本类的静态函数用于获取当前的日期和时间. */
class DateAndTime
{
public:
    DateAndTime(){}     
    ~DateAndTime() {}
    //==============================================================================
    /** 返回当前的日期、星期和时间，精确到秒 */
    static const String getDateAndTime(bool isCN) 
    { 
        String s(String::empty);
        s << getDate(isCN) << " "
            << getWeek(isCN) << "  "
            << getTime(false, true);

        return s; 
    }
    //==============================================================================
    /** 返回当前的年月日 
        @param isCN    是否返回中文字符串
    */
    static const String getDate(bool isCN)
    {
        Time time(Time::getCurrentTime());
        String s(String::empty);

        s << String(time.getYear()) << (isCN ? L"年" : L"-")
            << String(time.getMonth() + 1) << (isCN ? L"月" : L"-")
            << String(time.getDayOfMonth()) << (isCN ? L"日" : String::empty);

        return s;
    }
    //==============================================================================
    /** 返回当前星期几 
        @param isCN    是否返回中文字符串
    */
    static const String getWeek(bool isCN)
    {
        Time time(Time::getCurrentTime());

        if (isCN)
        {
            switch (time.getDayOfWeek())
            {
            case 0: return L"星期天";
            case 1: return L"星期一";
            case 2: return L"星期二";
            case 3: return L"星期三";
            case 4: return L"星期四";
            case 5: return L"星期五";
            case 6: return L"星期六";
            default: break;
            }
        }
        else
        {
            return time.getWeekdayName(time.getDayOfWeek(), true);
        }

        return String::empty;
    }
    //==============================================================================
    /** 返回当前时间，返回的字符串为 “08 : 20 : 35 AM”.
        @param is24    是否24小时制. 如果为true, 则2参无效
        @param useFlagAmOrPm    是否使用“AM”和“PM”标记
    */
    static const String getTime(bool is24, bool useFlagAmOrPm)
    {
        Time time(Time::getCurrentTime());
        String s(String::empty);

        if (is24)
        {
            useFlagAmOrPm = false;
            s << String(time.getHours()).paddedLeft ('0', 2);
        }
        else
        {
            s << String(time.getHoursInAmPmFormat()).paddedLeft ('0', 2);
        }

        s << " : "
            << String(time.getMinutes()).paddedLeft ('0', 2) << " : "
            << String(time.getSeconds()).paddedLeft ('0', 2);
        
        if (useFlagAmOrPm)
            s << (time.isAfternoon() ? " PM" : " AM");

        return s;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DateAndTime)
};