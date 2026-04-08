# Calendar-HE Wiki

## Table of Contents

- [Overview](#overview)
- [Background: The Hebrew Calendar](#background-the-hebrew-calendar)
  - [Lunisolar Structure](#lunisolar-structure)
  - [Months of the Hebrew Calendar](#months-of-the-hebrew-calendar)
  - [Leap Years and the Metonic Cycle](#leap-years-and-the-metonic-cycle)
  - [Variable Year Lengths](#variable-year-lengths)
  - [Day of the Week](#day-of-the-week)
  - [Day Transition at Sunset](#day-transition-at-sunset)
- [Architecture and Design](#architecture-and-design)
  - [Single-File Design](#single-file-design)
  - [Class Structure](#class-structure)
  - [Error Handling](#error-handling)
- [Conversion Algorithms](#conversion-algorithms)
  - [Julian Day Number (JDN)](#julian-day-number-jdn)
  - [Gregorian to JDN](#gregorian-to-jdn)
  - [JDN to Hebrew Date](#jdn-to-hebrew-date)
  - [Hebrew Date to JDN](#hebrew-date-to-jdn)
  - [JDN to Gregorian](#jdn-to-gregorian)
  - [Computing 1 Tishrei (he_tishrei1)](#computing-1-tishrei-he_tishrei1)
  - [Postponement Rules (Dehiyyot)](#postponement-rules-dehiyyot)
- [API Reference](#api-reference)
  - [caltime Class](#caltime-class)
  - [calendar Struct](#calendar-struct)
  - [Public Methods](#public-methods)
  - [Helper Functions](#helper-functions)
  - [Error Codes](#error-codes)
- [Input and Output Formats](#input-and-output-formats)
  - [Command-Line Interface](#command-line-interface)
  - [Output Format](#output-format)
  - [Localization Support](#localization-support)
- [Limitations and Edge Cases](#limitations-and-edge-cases)
- [Building and Portability](#building-and-portability)
- [Glossary](#glossary)
- [References](#references)

---

## Overview

**Calendar-HE** is a lightweight, zero-dependency C++ command-line utility for bidirectional date conversion between the Civil (Gregorian) calendar and the Hebrew (Jewish) calendar. It is designed to be simple, self-contained, and portable.

The program operates in three modes:

1. **Today mode** — Display today's date in both calendars (no arguments).
2. **Civil-to-Hebrew mode** — Convert a given Gregorian date to its Hebrew equivalent.
3. **Hebrew-to-Civil mode** — Convert a given Hebrew date to its Gregorian equivalent.

All output includes day and month names in both **Hebrew script** and **English transliteration**, making it useful for both Hebrew-literate and non-Hebrew-literate users.

---

## Background: The Hebrew Calendar

### Lunisolar Structure

The Hebrew calendar is a **lunisolar** calendar — it tracks both the Moon's phases (lunar months) and the Earth's orbit around the Sun (solar year). Each month begins approximately at the new moon (molad), and months alternate between 29 and 30 days. To keep the calendar aligned with the solar year and the agricultural seasons of the Land of Israel, an extra month is intercalated in 7 out of every 19 years.

### Months of the Hebrew Calendar

In a **regular (non-leap) year**, there are 12 months:

| # | Month | Hebrew | Days |
|---|-------|--------|------|
| 1 | Tishrei | תִּשְׁרֵי | 30 |
| 2 | Cheshvan | חֶשְׁוָן | 29 or 30 |
| 3 | Kislev | כִּסְלֵו | 29 or 30 |
| 4 | Tevet | טֵבֵת | 29 |
| 5 | Shevat | שְׁבָט | 30 |
| 6 | Adar | אֲדָר | 29 |
| 7 | Nisan | נִיסָן | 30 |
| 8 | Iyar | אִיָּר | 29 |
| 9 | Sivan | סִיוָן | 30 |
| 10 | Tammuz | תַּמּוּז | 29 |
| 11 | Av | אָב | 30 |
| 12 | Elul | אֱלוּל | 29 |

In a **leap year**, an additional month is inserted after Shevat:

| # | Month | Hebrew | Days |
|---|-------|--------|------|
| 6 | Adar I | אֲדָר א | 30 |
| 7 | Adar II | אֲדָר ב | 29 |

The remaining months (Nisan through Elul) shift up by one position, making the leap year total 13 months.

### Leap Years and the Metonic Cycle

The Hebrew calendar follows the **Metonic cycle**, a 19-year period after which the lunar phases nearly repeat on the same days of the solar year. Within each 19-year cycle, years **3, 6, 8, 11, 14, 17, and 19** are leap years. This is mathematically determined by the formula:

```
is_leap = ((7 * year + 1) % 19) < 7
```

Over 19 years, there are 235 lunar months (12 x 12 + 7 x 13 = 235), which closely matches 19 solar years.

### Variable Year Lengths

Hebrew years can be one of six lengths:

| Type | Non-Leap | Leap |
|------|----------|------|
| **Deficient** (חסרה) | 353 days | 383 days |
| **Regular** (כסדרה) | 354 days | 384 days |
| **Complete** (שלמה) | 355 days | 385 days |

The variation comes from **Cheshvan** and **Kislev**, which can each have either 29 or 30 days:

- **Deficient**: Cheshvan = 29, Kislev = 29
- **Regular**: Cheshvan = 29, Kislev = 30
- **Complete**: Cheshvan = 30, Kislev = 30

This flexibility allows the calendar to satisfy its postponement rules (dehiyyot) and synchronize with astronomical cycles.

### Day of the Week

Hebrew days of the week are numbered rather than named, except for the seventh day:

| # | Hebrew | Transliteration | Equivalent |
|---|--------|-----------------|------------|
| 1 | ראשון | Rishon | Sunday |
| 2 | שני | Sheni | Monday |
| 3 | שלישי | Shlishi | Tuesday |
| 4 | רביעי | Revi'i | Wednesday |
| 5 | חמישי | Chamishi | Thursday |
| 6 | שישי | Shishi | Friday |
| 7 | שבת | Shabbat | Saturday |

### Day Transition at Sunset

In the Hebrew calendar, a new day begins at **sunset**, not at midnight. The exact time of sunset varies by geographic location and time of year. This program uses the **civil convention** (midnight-based day boundaries) for all conversions. Users should be aware that for dates near sunset, the Hebrew date shown may differ by one day from the halachic (Jewish law) date.

---

## Architecture and Design

### Single-File Design

Calendar-HE is implemented as a single C++ source file (`calendar-he.cpp`, ~546 lines). This design choice prioritizes:

- **Simplicity** — No build system (Makefile, CMake, etc.) is needed; a single compiler command builds the program.
- **Portability** — The program compiles on any platform with a C++11-compatible compiler.
- **Zero dependencies** — Only standard library headers are used (`<iostream>`, `<time.h>`, `<unistd.h>`, `<string>`, `<cctype>`).

### Class Structure

The program is organized around a single class:

```
caltime
├── calendar (struct)
│   ├── result   (int)    — Error code (P_OK, P_ERR_RANGE, P_ERR_VAL)
│   ├── day      (int)    — Day of week (1=Sunday .. 7=Saturday)
│   ├── mo       (int)    — Month number
│   ├── date     (int)    — Day of month
│   └── year     (int)    — Year
│
├── String arrays (day/month names in English, Hebrew, and transliteration)
│
├── cal_get_ce_today()     — Get today's Gregorian date
├── convert_ce_to_he()     — Gregorian → Hebrew
└── convert_he_to_ce()     — Hebrew → Gregorian
```

Standalone helper functions:
- `he_tishrei1(y)` — Compute the Julian Day Number of 1 Tishrei for Hebrew year `y`
- `is_hebrew_leap_year(y)` — Determine whether Hebrew year `y` is a leap year

Display functions:
- `display_today()` — Show today's date in both calendars
- `display_he()` — Convert and display a Gregorian date in both calendars
- `display_ce()` — Convert and display a Hebrew date in both calendars

### Error Handling

The program uses integer error codes propagated through the `calendar.result` field:

| Constant | Value | Meaning |
|----------|-------|---------|
| `P_OK` | 0 | Operation succeeded |
| `P_ERR_RANGE` | -10 | Input is out of acceptable range |
| `P_ERR_VAL` | -20 | Input value is invalid or conversion failed |

Input validation is performed at multiple levels:
1. **Argument count check** in `main()` — Ensures the correct number of arguments.
2. **Range check** in `display_he()` / `display_ce()` — Validates month and day ranges.
3. **Conversion validation** in `convert_ce_to_he()` / `convert_he_to_ce()` — Verifies the input `calendar` struct has valid data.

---

## Conversion Algorithms

### Julian Day Number (JDN)

The program uses the **Julian Day Number** as an intermediate representation for all date conversions. The JDN is a continuous count of days since the beginning of the Julian Period (January 1, 4713 BCE in the proleptic Julian calendar). Using JDN as a pivot simplifies bidirectional conversion:

```
Gregorian date  ↔  JDN  ↔  Hebrew date
```

### Gregorian to JDN

The conversion from Gregorian to JDN uses the standard algorithm:

```cpp
long a   = (14 - month) / 12;
long y   = year + 4800 - a;
long m   = month + 12 * a - 3;
long jdn = date + (153 * m + 2) / 5 + 365 * y
           + y / 4 - y / 100 + y / 400 - 32045;
```

This formula accounts for the Gregorian calendar's leap year rules (divisible by 4, except centuries, except 400-year cycles).

### JDN to Hebrew Date

Converting a JDN to a Hebrew date involves:

1. **Estimate the Hebrew year** using the ratio of days to average Hebrew year length:
   ```cpp
   hyr = (long)((jdn - 347997) * 19.0 / 6940.0) + 1;
   ```

2. **Refine the estimate** by computing the JDN of 1 Tishrei for candidate years and adjusting:
   ```cpp
   while (he_tishrei1(hyr + 1) <= jdn) hyr++;
   while (he_tishrei1(hyr)     >  jdn) hyr--;
   ```

3. **Determine the month and day** by walking through the month-length table from Tishrei, subtracting each month's length from the day-of-year until the correct month is found.

### Hebrew Date to JDN

Converting a Hebrew date to a JDN involves:

1. **Compute the JDN of 1 Tishrei** for the given Hebrew year using `he_tishrei1()`.
2. **Accumulate month lengths** from Tishrei up to (but not including) the target month.
3. **Add the day within the month** (minus 1, since 1 Tishrei is the start).

### JDN to Gregorian

The reverse conversion from JDN back to Gregorian uses the standard algorithm:

```cpp
long aa = jdn + 32044;
long b  = (4 * aa + 3) / 146097;
long c  = aa - (146097 * b) / 4;
long d  = (4 * c + 3) / 1461;
long e  = c - (1461 * d) / 4;
long mm = (5 * e + 2) / 153;

date = e - (153 * mm + 2) / 5 + 1;
mo   = mm + (mm < 10 ? 3 : -9);
year = 100 * b + d - 4800 + (mo <= 2 ? 1 : 0);
```

### Computing 1 Tishrei (he_tishrei1)

The `he_tishrei1()` function is the mathematical core of the program. It computes the Julian Day Number of 1 Tishrei for any Hebrew year using the **molad** (new moon) calculation:

```cpp
static long he_tishrei1(long y) {
    long months = (235 * y - 234) / 19;     // Total months since epoch
    long parts  = 12084 + 13753 * months;    // Molad in halakim (parts)
    long jdn    = 347997 + 29 * months + parts / 25920;  // Base JDN
    ...
}
```

Key constants:
- **235** — Total lunar months in a 19-year Metonic cycle
- **13753** — The average month length in halakim (1 helek = 1/1080 of an hour): 29 days, 12 hours, 793 halakim = 29 + 13753/25920 days
- **25920** — Halakim per day (24 hours x 1080 halakim/hour)
- **347997** — JDN offset for the Hebrew calendar epoch

### Postponement Rules (Dehiyyot)

After computing the raw molad-based date for 1 Tishrei, the `he_tishrei1()` function applies **postponement rules** (dehiyyot) that ensure the calendar obeys certain constraints:

1. **Lo ADU Rosh** — Rosh Hashanah (1 Tishrei) cannot fall on Sunday (1), Wednesday (4), or Friday (6). If it does, it is postponed by one day.
   ```cpp
   if (dow == 2 || dow == 4 || dow == 6) jdn++;
   if (dow == 0)                          jdn++;
   ```
   (Note: `dow` here is `(jdn+1) % 7`, so the numeric values are offset by 1 from the typical 0=Sunday convention.)

2. **Year length constraints** — A Hebrew year cannot be 356 or 382 days long. If the computed year length would be one of these values, 1 Tishrei is postponed by one additional day:
   ```cpp
   if (ylen == 356) jdn++;
   if (ylen == 382) jdn++;
   ```

---

## API Reference

### caltime Class

The `caltime` class encapsulates all calendar data and conversion methods.

### calendar Struct

```cpp
struct calendar {
    int result;  // Error code: P_OK (0), P_ERR_RANGE (-10), P_ERR_VAL (-20)
    int day;     // Day of week: 1 (Sunday) through 7 (Saturday)
    int mo;      // Month number (1-based)
    int date;    // Day of month (1-based)
    int year;    // Year number
};
```

### Public Methods

#### `cal_get_ce_today()`
Returns a `calendar` struct populated with today's Gregorian date using the system's local timezone.

#### `convert_ce_to_he(calendar cal)`
Converts a Gregorian date (in `cal`) to a Hebrew date. Returns a new `calendar` struct with the Hebrew date. Sets `result` to `P_ERR_VAL` if the input is invalid.

**Input constraints:**
- `cal.mo`: 1-12
- `cal.date`: 1-31
- `cal.result`: must be `P_OK`

#### `convert_he_to_ce(calendar cal)`
Converts a Hebrew date (in `cal`) to a Gregorian date. Returns a new `calendar` struct with the Gregorian date. Sets `result` to `P_ERR_VAL` if the input is invalid.

**Input constraints:**
- `cal.mo`: 1-12 (non-leap) or 1-13 (leap year)
- `cal.date`: 1-30
- `cal.result`: must be `P_OK`

### Helper Functions

#### `he_tishrei1(long y)` (static)
Returns the Julian Day Number of 1 Tishrei for Hebrew year `y`. This is the foundational function for all Hebrew calendar computations.

#### `is_hebrew_leap_year(int year)`
Returns `true` if the given Hebrew year is a leap year (has 13 months), `false` otherwise.

### Error Codes

| Constant | Value | Description |
|----------|-------|-------------|
| `P_OK` | `0` | Success |
| `P_ERR_RANGE` | `-10` | Input month or day is outside the valid range |
| `P_ERR_VAL` | `-20` | Input value is invalid or conversion could not be performed |

---

## Input and Output Formats

### Command-Line Interface

```
calendar-he                           # Display today's date
calendar-he -h <month> <date> <year>  # Civil (Gregorian) → Hebrew
calendar-he -c <month> <date> <year>  # Hebrew → Civil (Gregorian)
```

**Flag aliases:**

| Direction | Flags |
|-----------|-------|
| Civil → Hebrew | `-h`, `-H`, `-g`, `-G` |
| Hebrew → Civil | `-c`, `-C`, `-j`, `-J` |

### Output Format

All output follows this pattern:

```
----------------------------------------
Civil : <DayAbbr> - <MonthAbbr> <date>, <year>
Hebrew: <HebrewDay> <TranslitDay> - <HebrewMonth> <TranslitMonth> <date>, <year>
----------------------------------------
```

Where:
- `<DayAbbr>` — Three-letter English day abbreviation (Sun, Mon, Tue, ...)
- `<MonthAbbr>` — Three-letter English month abbreviation (Jan, Feb, Mar, ...)
- `<HebrewDay>` — Hebrew day name in Hebrew script (ראשון, שני, ...)
- `<TranslitDay>` — Transliterated day name (Rishon, Sheni, ...)
- `<HebrewMonth>` — Hebrew month name in Hebrew script (תִּשְׁרֵי, חֶשְׁוָן, ...)
- `<TranslitMonth>` — Transliterated month name (Tishrei, Cheshvan, ...)

### Localization Support

The program includes string arrays for:

| Array | Description |
|-------|-------------|
| `str_day[7]` | English day abbreviations (Sun-Sat) |
| `str_month[12]` | English month abbreviations (Jan-Dec) |
| `str_day_he[7]` | Hebrew day names in Hebrew script |
| `str_day_he_eng[7]` | Hebrew day names transliterated to English |
| `str_month_he[12]` | Hebrew month names (non-leap year) in Hebrew script |
| `str_month_he_eng[12]` | Hebrew month names (non-leap year) transliterated |
| `str_month_he_leap[13]` | Hebrew month names (leap year) in Hebrew script |
| `str_month_he_leap_eng[13]` | Hebrew month names (leap year) transliterated |

---

## Limitations and Edge Cases

| Limitation | Details |
|-----------|---------|
| **Sunset boundary** | The program uses midnight-based day boundaries. Near sunset, the Hebrew date may differ by one day from the halachic date. |
| **Timezone** | Today's date uses the system's local timezone. No timezone argument is supported. |
| **Date validation** | The program checks basic ranges (month 1-12, day 1-31 for Gregorian; month 1-13, day 1-30 for Hebrew) but does not validate that the specific day exists in the given month (e.g., February 30 would be accepted). |
| **Far-future/past dates** | The algorithm uses `long` arithmetic. Extremely distant dates may encounter overflow, though this is unlikely for practical use. |
| **POSIX dependency** | The `<unistd.h>` header is included, which is POSIX-specific. This may require attention when building with MSVC on Windows. |
| **No Adar disambiguation input** | In non-leap years, month 6 is Adar. In leap years, month 6 is Adar I and month 7 is Adar II. Users must know whether the target year is a leap year to provide the correct month number. |

---

## Building and Portability

### Compiler Requirements

- C++11 or later
- Standard library only (no third-party dependencies)

### Platform-Specific Notes

| Platform | Compiler | Notes |
|----------|----------|-------|
| Linux | `g++` / `clang++` | Fully supported. `g++ -o calendar-he calendar-he.cpp` |
| macOS | Apple Clang / `g++` | Fully supported via Xcode Command Line Tools. |
| Windows (MSYS2) | MinGW-w64 `g++` | Fully supported. Use `.exe` extension. |
| Windows (MSVC) | `cl` | May need `<unistd.h>` replaced with `<io.h>` or removed. |
| FreeBSD / OpenBSD | `clang++` / `g++` | Expected to work; uses only POSIX and standard C++ features. |

### Build Command

```bash
g++ -o calendar-he calendar-he.cpp
```

No flags beyond the default are required. For optimized builds:

```bash
g++ -O2 -o calendar-he calendar-he.cpp
```

---

## Glossary

| Term | Definition |
|------|-----------|
| **Adar** | The 6th month of the Hebrew calendar (or Adar I/II in leap years) |
| **CE** | Common Era (equivalent to AD in the Gregorian calendar) |
| **Dehiyyot** | Postponement rules that adjust the start of the Hebrew year |
| **Gregorian calendar** | The internationally used civil calendar, introduced by Pope Gregory XIII in 1582 |
| **Halakim** | "Parts" — the smallest unit of time in the Hebrew calendar (1/1080 of an hour, approximately 3.33 seconds) |
| **Hebrew calendar** | The lunisolar calendar used in Jewish religious and cultural life |
| **JDN** | Julian Day Number — a continuous count of days used as an intermediate for calendar conversions |
| **Leap year (Hebrew)** | A year with 13 months (an extra Adar), occurring 7 times in every 19-year cycle |
| **Metonic cycle** | A 19-year cycle after which lunar phases repeat on approximately the same days of the solar year |
| **Molad** | The calculated moment of the new moon that determines the start of each Hebrew month |
| **Nisan** | The 7th month of the civil Hebrew year (1st month of the religious year); the month of Passover |
| **Rosh Hashanah** | The Hebrew New Year, observed on 1 Tishrei |
| **Tishrei** | The 1st month of the civil Hebrew year; the month of Rosh Hashanah and Yom Kippur |

---

## References

1. Dershowitz, N., & Reingold, E. M. (2008). *Calendrical Calculations* (3rd ed.). Cambridge University Press.
2. Meeus, J. (1991). *Astronomical Algorithms*. Willmann-Bell.
3. Wikipedia: [Hebrew calendar](https://en.wikipedia.org/wiki/Hebrew_calendar)
4. Wikipedia: [Julian day](https://en.wikipedia.org/wiki/Julian_day)
5. Wikipedia: [Metonic cycle](https://en.wikipedia.org/wiki/Metonic_cycle)
6. Hebcal: [Hebrew Calendar Resources](https://www.hebcal.com/)
