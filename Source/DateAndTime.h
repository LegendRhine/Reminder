/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

/** ����ľ�̬�������ڻ�ȡ��ǰ�����ں�ʱ��. */
class DateAndTime
{
public:
    DateAndTime(){}     
    ~DateAndTime() {}
    //==============================================================================
    /** ���ص�ǰ�����ڡ����ں�ʱ�䣬��ȷ���� */
    static const String getDateAndTime(bool isCN) 
    { 
        String s(String::empty);
        s << getDate(isCN) << " "
            << getWeek(isCN) << "  "
            << getTime(false, true);

        return s; 
    }
    //==============================================================================
    /** ���ص�ǰ�������� 
        @param isCN    �Ƿ񷵻������ַ���
    */
    static const String getDate(bool isCN)
    {
        Time time(Time::getCurrentTime());
        String s(String::empty);

        s << String(time.getYear()) << (isCN ? L"��" : L"-")
            << String(time.getMonth() + 1) << (isCN ? L"��" : L"-")
            << String(time.getDayOfMonth()) << (isCN ? L"��" : String::empty);

        return s;
    }
    //==============================================================================
    /** ���ص�ǰ���ڼ� 
        @param isCN    �Ƿ񷵻������ַ���
    */
    static const String getWeek(bool isCN)
    {
        Time time(Time::getCurrentTime());

        if (isCN)
        {
            switch (time.getDayOfWeek())
            {
            case 0: return L"������";
            case 1: return L"����һ";
            case 2: return L"���ڶ�";
            case 3: return L"������";
            case 4: return L"������";
            case 5: return L"������";
            case 6: return L"������";
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
    /** ���ص�ǰʱ�䣬���ص��ַ���Ϊ ��08 : 20 : 35 AM��.
        @param is24    �Ƿ�24Сʱ��. ���Ϊtrue, ��2����Ч
        @param useFlagAmOrPm    �Ƿ�ʹ�á�AM���͡�PM�����
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