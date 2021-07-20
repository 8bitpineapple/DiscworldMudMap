#ifndef DISCTIME
#define DISCTIME
#include <string>
#include <chrono>
#include <iostream>

//See comments at the end of .h for descriptions of how DiscworldTime works.

class DiscTime
{
public:
    static std::string MonthName(int i);
    static std::string ShortMonthName(int i);
    static std::string DayName(int i);
    static std::string ShortDayName(int i);
    static int DaysInMonth(int i);
    static int DayToMonth(int d);
    static std::string CycleName(bool c);
    static std::string ShortCycleName(bool c);

    //Returns a human readable string of the Discworld Date Time, e.g. 5:52pm Octeday 2nd Grune
    std::string Readable();
    std::string ReadableTime();
    std::string ReadableDate();
    std::string ReadableUCYear();

    //Sets time to now and ruturns Unix Time.
    std::chrono::seconds Now();

    //Time calculators
    int Second();
    int Minute();
    int Hour24();
    int Hour12();
    int DayOfYear();
    int DayOfMonth();
    int Month();
    int UCYear();
    bool Cycle();

    //Getters for this
    std::string MonthName();
    std::string DayName();
    std::string ShortMonthName();
    std::string ShortDayName();

private:
    static const int kNumMonths = 13;
    static const char* kMonths[kNumMonths];
    static const char* kMonthsShort[kNumMonths];
    static const int kNumDays = 8;
    static const char* kDay[kNumDays];
    static const char* kDayShort[kNumDays];
    static const int kMagicStartDay = 5; //The day discworld months start on
    std::chrono::seconds unixTime;

    //NOTE counts from day 1. i.e. 1 => st, 2 => nd, etc
    static std::string DayOrdinal(int d);
    std::string DayOrdinal();

    int CommonYear();
    int AstroYear();

};



//Discworld time description.
//Discworld has 13 months. Each month has 32 days -- except the last (Ick) which has 16
//The months are
//"Offle", "February", "March", "April", "May", "June", "Grune", "August", "Spune", "Sektober", "Ember", "December", "Ick"
//These 13 months compose a "common year" with 400 days.
//An astrological year is actually 800 days.
//The seasons repeat every half year as the discworld is rotated 180 degrees
//This is why on the discworld the calendars deal with half astrological years i.e. Common Years, since that's all you
//Need to track seasons.
//There are 8 days in a discworld week.
//"Octeday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
//Discworld Days are also 24 hours long, with 60 minutes in an hour and 60 seconds in a minute.
//There are two popular calendars on the discworld,
//AM and UC
//AM counts full astro years since the founding on AM
//UC counts half years since the founding of the unseen university (1282 AM)



//There are special holidays,


//Typing Calendar list in game says - 
// Special days tied to the Discworld calendar
// -------------------------------------------
// Hogswatchday (1 Offle Prime)
// Crueltide (1 Offle Secundus)
// Small Gods Day (24 June Prime)
// Alls Fallow (24 June Secundus)
// Soul Cake Tuesday (23 August)
// Sektober Fools' Day (1 Sektober)

// Special days tied to the Roundworld calendar
// --------------------------------------------
// Cream Pie Day (11 January)
// Cabbage Day (17 February)
// Lilac Day (12 March)
// Ukulele Day (23 August)
// Beard Day (10 September)
// Pirate Day (19 September)
// Greco's Day Off (30 October)
// Pink Bow Day (10 November)
// Christmas Season (21-25 December)


// In Quows QuowBar in the code it looks like he uses 16/7 = Small Gods Day?
// This is a mistake, and it is actually  24 June Prime

#endif