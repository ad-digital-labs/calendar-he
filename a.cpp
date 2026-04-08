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

<<<<<<< HEAD
    std::string str_month_he[13]
=======
    std::string str_month_he[12]
    {
        "תִּשְׁרֵי", "חֶשְׁוָן", "כִּסְלֵו", "טֵבֵת", "שְׁבָט", "אֲדָר", "נִיסָן", "אִיָּר", "סִיוָן", "תַּמּוּז", "אָב", "אֱלוּל"
    };

    std::string str_month_he_leap[13]
>>>>>>> 66880ae (corrected01)
    {
        "תִּשְׁרֵי", "חֶשְׁוָן", "כִּסְלֵו", "טֵבֵת", "שְׁבָט", "אֲדָר א", "אֲדָר ב", "נִיסָן", "אִיָּר", "סִיוָן", "תַּמּוּז", "אָב", "אֱלוּל"
    };

<<<<<<< HEAD
=======

>>>>>>> 66880ae (corrected01)
    std::string str_day_he[7]
    {
        "ראשון", "שני", "שלישי", "רביעי", "חמישי", "שישי", "שבת"
    };


    std::string str_day_he_eng[7]
    {
        "Rishon", "Sheni", "Shlishi", "Revi'i", "Chamishi", "Shishi", "Shabbat"
    };

<<<<<<< HEAD
    std::string str_month_he_eng[13]
    {
        "Tishrei", "Cheshvan", "Kislev", "Tevet", "Shevat", "Adar I", "Adar II", "Nisan", "Iyar", "Sivan", "Tammuz", "Av"
    };

    struct calendar cal_get_ce_local();
    struct calendar convert_ce_to_he(struct calendar cal);
=======
    std::string str_month_he_leap_eng[13]
    {
        "Tishrei", "Cheshvan", "Kislev", "Tevet", "Shevat", "Adar I", "Adar II", "Nisan", "Iyar", "Sivan", "Tammuz", "Av", "Elul"
    };

    std::string str_month_he_eng[12]
    {
        "Tishrei", "Cheshvan", "Kislev", "Tevet", "Shevat", "Adar", "Nisan", "Iyar", "Sivan", "Tammuz", "Av", "Elul"
    };

    struct calendar cal_get_ce_today();
    struct calendar cal_get_ce(int month, int date, int year);
    struct calendar convert_ce_to_he(struct calendar cal);
    struct calendar convert_he_to_ce(struct calendar cal);
>>>>>>> 66880ae (corrected01)

};


<<<<<<< HEAD


struct caltime::calendar caltime::cal_get_ce_local()
=======
// Returns JDN of 1 Tishrei for a given Hebrew year
static long he_tishrei1(long y)
{
    long months = (235 * y - 234) / 19;
    long parts  = 12084 + 13753 * months;
    long jdn    = 347997 + 29 * months + parts / 25920;
    long dow    = (jdn + 1) % 7;
    if (dow == 2 || dow == 4 || dow == 6) jdn++;
    if (dow == 0)                          jdn++;
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


// determine the hebrew year is leap year
bool is_hebrew_leap_year(int year)
{
    return ((7 * year + 1) % 19) < 7;
};

struct caltime::calendar caltime::cal_get_ce_today()
>>>>>>> 66880ae (corrected01)
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

<<<<<<< HEAD
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
=======
>>>>>>> 66880ae (corrected01)

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

<<<<<<< HEAD
        // Step 2: Approximate Hebrew year then adjust
=======
        // Step 2: JDN -> Hebrew year (increments at Tishrei)
>>>>>>> 66880ae (corrected01)
        long hyr = (long)((jdn - 347997) * 19.0 / 6940.0) + 1;
        while (he_tishrei1(hyr + 1) <= jdn) hyr++;
        while (he_tishrei1(hyr)     >  jdn) hyr--;

<<<<<<< HEAD
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
=======
        bool leap     = ((7 * hyr + 1) % 19) < 7;
        long yr_start = he_tishrei1(hyr);
        long yr_len   = he_tishrei1(hyr + 1) - yr_start;

        // Month lengths in Tishrei-first order (1=Tishrei..13=Elul in leap)
        // non-leap: 1=Tishrei,2=Cheshvan,3=Kislev,4=Tevet,5=Shevat,6=Adar,
        //           7=Nisan,8=Iyar,9=Sivan,10=Tammuz,11=Av,12=Elul
        // leap:     1=Tishrei,2=Cheshvan,3=Kislev,4=Tevet,5=Shevat,6=AdarI,
        //           7=AdarII,8=Nisan,9=Iyar,10=Sivan,11=Tammuz,12=Av,13=Elul
        int mlen[14] = {0, 30,29,30,29,30,29, 30,29,30,29,30,29,29};
        if (yr_len % 10 == 5) mlen[2] = 30;
        if (yr_len % 10 == 3) mlen[3] = 29;
        if (!leap)            mlen[7] = 0;  // no AdarII in non-leap

        // Step 3: Walk Tishrei-first to find month and day
        long doy   = jdn - yr_start;
        long hmo_t = 1;
        int  slots = leap ? 13 : 12;
        while (hmo_t <= slots)
        {
            if (mlen[hmo_t] == 0) { hmo_t++; continue; }  // skip empty slot (AdarII in non-leap)
            if (doy < mlen[hmo_t]) break;                  // found the month
            doy -= mlen[hmo_t];
            hmo_t++;
        }
        // If we landed on the empty slot, move to next valid slot
        if (hmo_t <= slots && mlen[hmo_t] == 0) hmo_t++;

        // Step 4: Map slot index to Tishrei-first compact month number
        long hmo;
        if (!leap && hmo_t > 7)
            hmo = hmo_t - 1;  // compress over missing Adar II
        else
            hmo = hmo_t;

        cal_he.date   = (int)(doy + 1);
>>>>>>> 66880ae (corrected01)
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


<<<<<<< HEAD




int display_local()
=======
struct caltime::calendar caltime::convert_he_to_ce(struct calendar cal)
{
    struct calendar cal_ce;

    bool leap  = ((7 * cal.year + 1) % 19) < 7;
    int max_mo = leap ? 13 : 12;

    if( !leap && cal.mo == 13 )
    {
        cal_ce.result = P_ERR_VAL;
        return cal_ce;
    };

    if( cal.result == P_OK && cal.mo >= 1 && cal.mo <= max_mo && cal.date >= 1 && cal.date <= 30 )
    {
        long yr_start = he_tishrei1(cal.year);
        long yr_len   = he_tishrei1(cal.year + 1) - yr_start;

        // Same Tishrei-first month length table
        int mlen[14] = {0, 30,29,30,29,30,29, 30,29,30,29,30,29,29};
        if (yr_len % 10 == 5) mlen[2] = 30;
        if (yr_len % 10 == 3) mlen[3] = 29;
        if (!leap)            mlen[7] = 0;

        // Map compact Tishrei-first month numbering to Tishrei-first slot index
        int mo_t;
        if (!leap && cal.mo >= 7)
            mo_t = cal.mo + 1;  // shift past missing Adar II
        else
            mo_t = cal.mo;

        // Build JDN from Tishrei start + months before mo_t
        long jdn = yr_start + (cal.date - 1);
        for (int i = 1; i < mo_t; i++)
            if (mlen[i] > 0) jdn += mlen[i];

        // JDN -> Gregorian
        long aa = jdn + 32044;
        long b  = (4 * aa + 3) / 146097;
        long c  = aa - (146097 * b) / 4;
        long d  = (4 * c + 3) / 1461;
        long e  = c - (1461 * d) / 4;
        long mm = (5 * e + 2) / 153;

        cal_ce.date = (int)(e - (153 * mm + 2) / 5 + 1);
        cal_ce.mo   = (int)(mm + (mm < 10 ? 3 : -9));
        cal_ce.year = (int)(100 * b + d - 4800 + (cal_ce.mo <= 2 ? 1 : 0));

        struct tm t = {};
        t.tm_year = cal_ce.year - 1900;
        t.tm_mon  = cal_ce.mo - 1;
        t.tm_mday = cal_ce.date;
        mktime(&t);
        cal_ce.day    = t.tm_wday + 1;
        cal_ce.result = P_OK;
    }
    else
    {
        cal_ce.result = P_ERR_VAL;
    };

    return cal_ce;
};


int display_today()
{

    caltime cal;

    struct caltime::calendar cal_ce;
    struct caltime::calendar cal_he;    
    
    
    cal_ce=cal.cal_get_ce_today();
    cal_he=cal.convert_ce_to_he(cal_ce);

    cout<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"Today:"<<endl;
    cout<<"Civil : ";
    cout<<cal.str_day[cal_ce.day-1]<<" - ";
    cout<<cal.str_month[cal_ce.mo-1]<<" ";
    cout<<cal_ce.date<<", "<<cal_ce.year<<endl;

    cout<<"Hebrew: ";
    cout<<cal.str_day_he[cal_he.day-1]<<" "<<cal.str_day_he_eng[cal_he.day-1]<<" - ";
    if( ((7 * cal_he.year + 1) % 19) < 7 )
        cout<<cal.str_month_he_leap[cal_he.mo-1]<<" "<<cal.str_month_he_leap_eng[cal_he.mo-1]<<" ";
    else
        cout<<cal.str_month_he[cal_he.mo-1]<<" "<<cal.str_month_he_eng[cal_he.mo-1]<<" ";
    cout<<cal_he.date<<", ";
    cout<<cal_he.year<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<endl;

    return 0;

};


int display_he(int month, int date, int year)
>>>>>>> 66880ae (corrected01)
{

    int res;

    caltime cal;

<<<<<<< HEAD
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

=======
    struct caltime::calendar cal_ce;
    struct caltime::calendar cal_he;    
    
    
    if(month >= 1 && month <= 12 && date >= 1 && date <= 31)
    {
        cal_ce.mo   = month;
        cal_ce.date = date;
        cal_ce.year = year;

        struct tm t = {};
        t.tm_year = year - 1900;
        t.tm_mon  = month - 1;
        t.tm_mday = date;
        mktime(&t);
        cal_ce.day    = t.tm_wday + 1;
        cal_ce.result = P_OK;

        cal_he=cal.convert_ce_to_he(cal_ce);

        if(cal_he.result == P_OK)
        {
            cout<<endl;
            cout<<"----------------------------------------"<<endl;
            cout<<"Civil : ";
            cout<<cal.str_day[cal_ce.day-1]<<" - ";
            cout<<cal.str_month[cal_ce.mo-1]<<" ";
            cout<<cal_ce.date<<", "<<cal_ce.year<<endl;

            cout<<"Hebrew: ";
            cout<<cal.str_day_he[cal_he.day-1]<<" "<<cal.str_day_he_eng[cal_he.day-1]<<" - ";
            if( ((7 * cal_he.year + 1) % 19) < 7 )
                cout<<cal.str_month_he_leap[cal_he.mo-1]<<" "<<cal.str_month_he_leap_eng[cal_he.mo-1]<<" ";
            else
                cout<<cal.str_month_he[cal_he.mo-1]<<" "<<cal.str_month_he_eng[cal_he.mo-1]<<" ";
            cout<<cal_he.date<<", ";
            cout<<cal_he.year<<endl;
            cout<<"----------------------------------------"<<endl;
            cout<<endl;

            res=P_OK;

            
        }
        else
        {
            res=P_ERR_VAL;
        };
    }
    else
    {
        res=P_ERR_RANGE;
    };


    return res;

};


int display_ce(int month, int date, int year)
{

    int res;

    caltime cal;

    struct caltime::calendar cal_ce;
    struct caltime::calendar cal_he;    


    if(month >= 1 && month <= 13 && date >= 1 && date <= 30)
    {
        cal_he.mo     = month;
        cal_he.date   = date;
        cal_he.year   = year;
        cal_he.day    = 0;  // unknown until after conversion
        cal_he.result = P_OK;

        cal_ce = cal.convert_he_to_ce(cal_he);

        if(cal_ce.result == P_OK)
        {
            cout<<endl;
            cout<<"----------------------------------------"<<endl;
            cout<<"Hebrew: ";
            cout<<cal.str_day_he[cal_ce.day-1]<<" "<<cal.str_day_he_eng[cal_ce.day-1]<<" - ";
            if( ((7 * cal_he.year + 1) % 19) < 7 )
                cout<<cal.str_month_he_leap[cal_he.mo-1]<<" "<<cal.str_month_he_leap_eng[cal_he.mo-1]<<" ";
            else
                cout<<cal.str_month_he[cal_he.mo-1]<<" "<<cal.str_month_he_eng[cal_he.mo-1]<<" ";
            cout<<cal_he.date<<", ";
            cout<<cal_he.year<<endl;

            cout<<"Civil : ";
            cout<<cal.str_day[cal_ce.day-1]<<" - ";
            cout<<cal.str_month[cal_ce.mo-1]<<" ";
            cout<<cal_ce.date<<", "<<cal_ce.year<<endl;            
            cout<<"----------------------------------------"<<endl;
            cout<<endl;

            res=P_OK;

            
        }
        else
        {
            res=P_ERR_VAL;
        };
    }
    else
    {
        res=P_ERR_RANGE;
    };
    
    
    return res;

};

    



>>>>>>> 66880ae (corrected01)

int main(int argc, char *argv[])
{

<<<<<<< HEAD
    display_local();



    return 0;
=======
    int res = P_OK;

    if(argc == 1)
    {
        if( (res=display_today()) != P_OK )
        {
            cout<<"Undefined error... "<<endl;
        };

    }else if(argc == 5)
    {
        if(argv[1][0] == '-' && argv[1][1] == 'h')
        {
            int month = atoi(argv[2]);
            int date  = atoi(argv[3]);
            int year  = atoi(argv[4]);

            if( (res=display_he(month, date, year)) != P_OK )
            {
                if(res == P_ERR_RANGE)
                {
                    cout<<"ERROR: Input out of range... "<<endl;
                }
                else if(res == P_ERR_VAL)
                {
                    cout<<"ERROR: Invalid input value... "<<endl;
                }
                else
                {
                    cout<<"ERROR: Undefined error... "<<endl;
                };
            };



        }else if(argv[1][0] == '-' && argv[1][1] == 'c')
        {
            int month = atoi(argv[2]);
            int date  = atoi(argv[3]);
            int year  = atoi(argv[4]);

            if( (res=display_ce(month, date, year)) != P_OK )
            {
                if(res == P_ERR_RANGE)
                {
                    cout<<"ERROR: Input out of range... "<<endl;
                }
                else if(res == P_ERR_VAL)
                {
                    cout<<"ERROR: Invalid input value... "<<endl;
                }
                else
                {
                    cout<<"ERROR: Undefined error... "<<endl;
                };
            };




        }else
        {
            cout<<"Usage: "<<argv[0]<<" -h|-c month date year"<<endl;
            res=P_ERR_VAL;
        };

    }else
    {
        cout<<"Usage: "<<argv[0]<<" -h|-c month date year"<<endl;
        res=P_ERR_VAL;
    };

    return res;
>>>>>>> 66880ae (corrected01)

};
