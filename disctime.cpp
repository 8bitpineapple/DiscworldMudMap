#include "disctime.h"

//                                            0         1           2         3        4      5       6       7          8       9           10        11          12
const char*  DiscTime::kMonths[kNumMonths] = {"Offle", "February", "March", "April", "May", "June", "Grune", "August", "Spune", "Sektober", "Ember", "December", "Ick"};
//                                                 0      1     2      3      4      5      6       7     8       9      10     11     12   
const char*  DiscTime::kMonthsShort[kNumMonths] = {"Off", "Feb", "Mar", "Apr", "May", "Jun", "Gru", "Aug", "Spu", "Sek", "Emb", "Dec", "Ick"};
//                                       0          1         2          3           4           5          6          7
const char* DiscTime::kDay[kNumDays] = {"Octeday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

//                                           0      1     2      3      4      5       6      7
const char* DiscTime::kDayShort[kNumDays] = {"Oct", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

std::chrono::seconds DiscTime::Now()
{
    auto now = std::chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    unixTime = std::chrono::duration_cast<std::chrono::seconds>(epoch);
    return unixTime;
}

//Name of discworld month. Counts from 0 - 12
std::string DiscTime::MonthName(int i)
{
    if(i < 0)
        return "INVALID MONTH";
    else
        return kMonths[i % kNumMonths];
}
//Name of discworld month shortened. Counts from 0 - 12
std::string DiscTime::ShortMonthName(int i)
{
    if(i < 0)
        return "INVALID MONTH";
    else
        return kMonthsShort[i % kNumMonths];
}
//Name of discworld day. 0 - 15
std::string DiscTime::DayName(int i)
{
    if(i < 0)
        return "INVALID DAY";
    else
        return kDay[i%kNumDays];
}

std::string DiscTime::ShortDayName(int i)
{
    if(i < 0)
        return "INVALID DAY";
    else
        return kDayShort[i%kNumDays];
}
//Returns number of days in month i, counts from 0.
int DiscTime::DaysInMonth(int i)
{
    const int kIck = 12;
    //Ick has 16 days all the rest have 32.
    if(i%kNumMonths == kIck)
        return 16;
    else
        return 32;
}
//Pick a day of the year, e.g. 358, and it returns which month the day is in.
int DiscTime::DayToMonth(int d)
{
    //There are 400 days in  a discworld year,
    int dayMod = d%400;
    //Day mod is now in the range 0 - 399

    //In a discworld  year, months 0 to 11 have 32 days, and the last month 12 has 16 days.
    //Labeling the first day = 0 and the last 399
    //Every month starts on a multiple of 32.
    //So we can just divide by 32, doesn't matter that the last month has less than 32 days
    //It still starts on a multiple of 32.
    return dayMod/32;
}


//Discworld MUD technical details.
//In Discworld Mud time passes in discworld 10/3 times normal speed.
//So in 18 RoundWorld seconds, 1 Discworld Minute passes.
//Discworld time is translated from Unix Epoch time
//Unix Epoch time should be the only thing we have to store in DiscTime and from that
//Should be able to work out the discworld second/hour/day/month/year

//Current minutes should be 
//(unixTime / 18)%60
//Current hour, should be (unixTime / (18*60))%24
//Current day should be, (unixTime / (18*60*24) )%400
//Current Month = currentDay / 32    
//Not all discworld months have 32 days, but it's the only the last one that doesn't and it has >32.
//Which conveniently means all months start on a day divisble by 32 (When counting the fist day as day 0.)
//DayOfMonth = currentDay % 32
//For day of month remember to add 1 when showing to user, i.e. 1st of Grune NOT 0st of Grune.

int DiscTime::Second()
{
    //(unixTime.count() * 18)%60 would work, buy maybe this has int overflow concerns?
    //Cause the current epoch time times 18 is in the order 2^34
    //So instead of this maybe we do unixTime.count() - unixTime.count()/18
    //Since unixTime.count()/18 will be the total number of whole discworld minutes passed,
    return unixTime.count() - unixTime.count()/18;
}

int DiscTime::Minute()
{
    return (unixTime.count() / 18)%60;
}

int DiscTime::Hour24()
{
    return(unixTime.count() / (18*60))%24;
}

int DiscTime::Hour12()
{
    return(unixTime.count() / (18*60))%12;
}

int DiscTime::DayOfYear()
{
    return (unixTime.count() / (18*60*24) )%400;
}

int DiscTime::DayOfMonth()
{
    return DayOfYear()%32;
}

int DiscTime::Month()
{
    return DayOfYear()/32;
}

int DiscTime::CommonYear()
{
    
    return (unixTime.count() / (18*60*24))/400;
}

int DiscTime::UCYear()
{
    int magicNumber = 1888; //The year of time 0
    return CommonYear() + magicNumber;
}

int DiscTime::AstroYear()
{
    return (unixTime.count() / (18*60*24))/800;
}

    //Which cycle, i.e. Whether we're in the first or second half
    //Of the astral year 0 => Prime , 1 => Secundus
bool DiscTime::Cycle()
{
    return (unixTime.count() / (18*60*24) )%800 >= 400;
}

//Name of Cycle
std::string DiscTime::CycleName(bool c)
{
    if(c)
        return "Secundus";
    else
        return "Prime";
}

//Name of Cycle Shortened
std::string DiscTime::ShortCycleName(bool c)
{
    if(c)
        return "II";
    else
        return "I";
}

std::string DiscTime::MonthName()
{
    return MonthName(Month());
}
std::string DiscTime::DayName()
{
    return DayName(DayOfMonth());
}

std::string DiscTime::ShortMonthName()
{
    return ShortMonthName(Month());
}

//Name of discworld day shortened. 0 - 7
std::string DiscTime::ShortDayName()
{
    return ShortDayName(DayOfMonth());
}

std::string DiscTime::DayOrdinal(int d)
{
    if(d > 3)
        return "th";
    else if(d == 1)
        return "st";
    else if(d == 2)
        return "nd";
    else if(d == 3)
        return "rd";
    else
        return "th"; // Shouldn't ever get here.
}

std::string DiscTime::DayOrdinal()
{
    return DayOrdinal(DayOfMonth()+1);
}

//Returns a human readable string of the Discworld Date Time, e.g. 5:52pm Octeday 2nd Grune
std::string DiscTime::Readable()
{
    std::string output = "";
    //Output should read like
    // 5:23pm, Tuesday 3rd Grune Prime UC 2044
    output += ReadableTime();
    output += ", ";
    output += ReadableDate();
    output += " ";
    output += ReadableUCYear();

    return output;   
}

//Returns a human readable string of the Discworld Time, e.g. 5:52pm
std::string DiscTime::ReadableTime()
{
    std::string output = "";
    output += std::to_string(Hour12());
    output += ":";
    if(Minute()<10)
        output += "0";
    output += std::to_string(Minute());
    if(Hour24() > 12)
        output += "pm";
    else
        output += "am";
    return output;
}

//Returns a human readable string of the Discworld Date, e.g. Octeday 2nd Grune
std::string DiscTime::ReadableDate()
{
    std::string output = "";
    output += DayName(DayOfMonth());
    output += " ";
    output += std::to_string(DayOfMonth()+1);
    output += DayOrdinal(DayOfMonth()+1);
    output += " ";
    output += MonthName(Month());
    return output;
}
//Returns a human readable string of the Discworld UC Year, i.e. Prime, UC 2044
std::string DiscTime::ReadableUCYear()
{
    std::string output = "";
    output += CycleName(Cycle());
    output += ", ";
    output += "UC ";
    output += std::to_string(UCYear());
    return output;
}