#define P_OK 0
#define P_ERR_RANGE -10
#define P_ERR_VAL -20


#include <iostream>
#include <time.h>
#include <unistd.h>
#include <string>
#include <cctype>


using namespace std;

class caltime
{
    public:

    struct calendar
    {

        int result;

        int day;
        int mo;
        int date;
        int year;
    };

    std::string str_day[7]
    {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };

    std::string str_month[12]
    {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    std::string str_month_he[13]
    {
        "תִּשְׁרֵי", "חֶשְׁוָן", "כִּסְלֵו", "טֵבֵת", "שְׁבָט", "אֲדָר א", "אֲדָר ב", "נִיסָן", "אִיָּר", "סִיוָן", "תַּמּוּז", "אָב", "אֱלוּל"
    };

    std::string str_day_he[7]
    {
        "ראשון", "שני", "שלישי", "רביעי", "חמישי", "שישי", "שבת"
    };


    std::string str_day_he_eng[7]
    {
        "Rishon", "Sheni", "Shlishi", "Revi'i", "Chamishi", "Shishi", "Shabbat"
    };

    std::string str_month_he_eng[13]
    {
        "Tishrei", "Cheshvan", "Kislev", "Tevet", "Shevat", "Adar I", "Adar II", "Nisan", "Iyar", "Sivan", "Tammuz", "Av"
    };

    struct calendar cal_get_ce_local();
    struct calendar convert_ce_to_he(struct calendar cal);

};




struct caltime::calendar caltime::cal_get_ce_local()
{
    struct calendar cal;

    time_t t = time(0);
    struct tm * now = localtime( & t );

    cal.day = now->tm_wday + 1;
    cal.mo = now->tm_mon + 1;
    cal.date = now->tm_mday;
    cal.year = now->tm_year + 1900;
    cal.result = P_OK;

    return cal;

};

// Returns JDN of 1 Tishrei for a given Hebrew year
static long he_tishrei1(long y)
{
    long months = (235 * y - 234) / 19;
    long parts  = 12084 + 13753 * months;
    long jdn    = 347997 + 29 * months + parts / 25920;
    long dow    = (jdn + 1) % 7;
    if (dow == 2 || dow == 4 || dow == 6) jdn++;
    if (dow == 0)                          jdn++;
    // ADU postponement on following year check
    long nm = (235 * (y + 1) - 234) / 19;
    long np = 12084 + 13753 * nm;
    long nj = 347997 + 29 * nm + np / 25920;
    long nd = (nj + 1) % 7;
    if (nd == 2 || nd == 4 || nd == 6) nj++;
    if (nd == 0)                        nj++;
    long ylen = nj - jdn;
    if (ylen == 356) jdn++;
    if (ylen == 382) jdn++;
    return jdn;
}

struct caltime::calendar caltime::convert_ce_to_he(struct calendar cal)
{
    struct calendar cal_he;

    if( cal.result == P_OK && cal.mo >= 1 && cal.mo <= 12 && cal.date >= 1 && cal.date <= 31 )
    {
        // Step 1: Gregorian -> Julian Day Number
        long a   = (14 - cal.mo) / 12;
        long y   = cal.year + 4800 - a;
        long m   = cal.mo + 12 * a - 3;
        long jdn = cal.date + (153 * m + 2) / 5 + 365 * y
                   + y / 4 - y / 100 + y / 400 - 32045;

        // Step 2: Approximate Hebrew year then adjust
        long hyr = (long)((jdn - 347997) * 19.0 / 6940.0) + 1;
        while (he_tishrei1(hyr + 1) <= jdn) hyr++;
        while (he_tishrei1(hyr)     >  jdn) hyr--;

        // Step 3: Day of year within Hebrew year
        long yr_start = he_tishrei1(hyr);
        long day_of_yr = jdn - yr_start;

        // Month lengths (1=Tishrei .. 12=Elul, 13=Adar II in leap)
        bool leap = ((7 * hyr + 1) % 19) < 7;
        long yr_len = he_tishrei1(hyr + 1) - yr_start;
        int mlen[14] = {0, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 29};
        if (yr_len % 10 == 5) mlen[2] = 30; // complete: Cheshvan=30
        if (yr_len % 10 == 3) mlen[3] = 29; // deficient: Kislev=29
        if (!leap)            mlen[6] = 0;  // no Adar I in regular year

        long hmo = 1;
        while (day_of_yr >= mlen[hmo]) { day_of_yr -= mlen[hmo]; hmo++; }

        cal_he.date   = (int)(day_of_yr + 1);
        cal_he.mo     = (int)hmo;
        cal_he.year   = (int)hyr;
        cal_he.day    = cal.day;
        cal_he.result = P_OK;
    }
    else
    {
        cal_he.result = P_ERR_VAL;
    };

    return cal_he;
};






int display_local()
{

    int res;

    caltime cal;

    int month;
    int date;
    int year;
    int day;

    struct caltime::calendar calen;
    struct caltime::calendar calen_he;
    

    calen = cal.cal_get_ce_local();

    month = calen.mo;
    date = calen.date;
    year = calen.year;
    day = calen.day;

    calen_he = cal.convert_ce_to_he(calen);


    if( calen.result == P_OK )
    {

        cout<<"Local Time: ";
        cout<<" "<<cal.str_day[day-1]<<" - ";
        cout<<cal.str_month[month-1]<<" ";
        cout<<date<<", "<<year<<endl;

        cout<<"Hebrew Date: ";
        cout<<cal.str_day_he[calen_he.day-1]<<" ";
        cout<<cal.str_day_he_eng[calen_he.day-1]<<" - ";
        cout<<cal.str_month_he[calen_he.mo-1]<<" ";
        cout<<cal.str_month_he_eng[calen_he.mo-1]<<" ";
        cout<<calen_he.date<<", "<<calen_he.year<<endl;

        
        res=P_OK;
    }else
    {
        res=P_ERR_VAL;
    };
    

    return res;


};


int main(int argc, char *argv[])
{

    display_local();



    return 0;

};
