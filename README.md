# Calendar-HE

A command-line tool for converting dates between the **Civil (Gregorian)** calendar and the **Hebrew (Jewish)** calendar. Written in C++, it supports bidirectional conversion and displays dates with Hebrew day/month names in both Hebrew script and English transliteration.

## Features

- **Display today's date** in both Civil (Gregorian) and Hebrew calendars
- **Convert Civil (Gregorian) to Hebrew** calendar dates
- **Convert Hebrew to Civil (Gregorian)** calendar dates
- Hebrew month and day names displayed in **Hebrew script** and **English transliteration**
- Full support for **Hebrew leap years** (Adar I and Adar II)
- Lightweight, single-file C++ program with **no external dependencies**

## Prerequisites

A C++ compiler supporting C++11 or later is required. The program uses only the C++ standard library.

| OS | Recommended Compiler |
|---|---|
| Linux | GCC (`g++`) or Clang (`clang++`) |
| macOS | Apple Clang (included with Xcode Command Line Tools) or GCC via Homebrew |
| Windows | MinGW-w64 (`g++`), MSYS2, or Microsoft Visual Studio (`cl`) |

## Installation

### Linux (Debian/Ubuntu)

```bash
# Install GCC if not already installed
sudo apt update
sudo apt install g++ -y

# Clone the repository
git clone https://github.com/ad-digital-labs/calendar-he.git
cd calendar-he

# Compile
g++ -o calendar-he calendar-he.cpp

# (Optional) Install system-wide
sudo cp calendar-he /usr/local/bin/
```

### Linux (Fedora/RHEL/CentOS)

```bash
# Install GCC if not already installed
sudo dnf install gcc-c++ -y

# Clone the repository
git clone https://github.com/ad-digital-labs/calendar-he.git
cd calendar-he

# Compile
g++ -o calendar-he calendar-he.cpp

# (Optional) Install system-wide
sudo cp calendar-he /usr/local/bin/
```

### Linux (Arch Linux)

```bash
# Install GCC if not already installed
sudo pacman -S gcc

# Clone the repository
git clone https://github.com/ad-digital-labs/calendar-he.git
cd calendar-he

# Compile
g++ -o calendar-he calendar-he.cpp

# (Optional) Install system-wide
sudo cp calendar-he /usr/local/bin/
```

### macOS

```bash
# Install Xcode Command Line Tools (includes Apple Clang compiler)
xcode-select --install

# Clone the repository
git clone https://github.com/ad-digital-labs/calendar-he.git
cd calendar-he

# Compile
g++ -o calendar-he calendar-he.cpp

# (Optional) Install to a directory in your PATH
sudo cp calendar-he /usr/local/bin/
```

### Windows (MinGW-w64 / MSYS2)

1. Download and install [MSYS2](https://www.msys2.org/).
2. Open the **MSYS2 UCRT64** terminal and install the compiler:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

3. Clone and compile:

```bash
git clone https://github.com/ad-digital-labs/calendar-he.git
cd calendar-he
g++ -o calendar-he.exe calendar-he.cpp
```

4. (Optional) Add the directory containing `calendar-he.exe` to your system `PATH`.

### Windows (Visual Studio / Developer Command Prompt)

1. Install [Visual Studio](https://visualstudio.microsoft.com/) with the **Desktop development with C++** workload.
2. Open **Developer Command Prompt for VS** or **Developer PowerShell for VS**.

```cmd
git clone https://github.com/ad-digital-labs/calendar-he.git
cd calendar-he
cl /EHsc /Fe:calendar-he.exe calendar-he.cpp
```

> **Note for Windows users:** The source uses `<unistd.h>`, which is a POSIX header. Building with MinGW-w64/MSYS2 is recommended for full compatibility. If using MSVC (`cl`), you may need to replace `<unistd.h>` with `<io.h>` or remove it if unused in your build.

## Usage

### Display Today's Date

Run the program with no arguments to display today's date in both Civil and Hebrew calendars (using local timezone):

```bash
./calendar-he
```

**Example output:**

```
----------------------------------------
Today:
Civil : Wed - Apr 8, 2026
Hebrew: רביעי Revi'i - נִיסָן Nisan 22, 5786
----------------------------------------
```

### Convert Civil (Gregorian) Date to Hebrew

Use the `-h`, `-H`, `-g`, or `-G` flag followed by month, date, and year:

```bash
./calendar-he -h <month> <date> <year>
```

**Example** -- Convert October 1, 2024 to Hebrew:

```bash
./calendar-he -h 10 1 2024
```

**Output:**

```
----------------------------------------
Civil : Tue - Oct 1, 2024
Hebrew: שלישי Shlishi - תִּשְׁרֵי Tishrei 28, 5785
----------------------------------------
```

### Convert Hebrew Date to Civil (Gregorian)

Use the `-c`, `-C`, `-j`, or `-J` flag followed by month, date, and year:

```bash
./calendar-he -c <month> <date> <year>
```

**Example** -- Convert 1 Tishrei 5785 to Civil:

```bash
./calendar-he -c 1 1 5785
```

**Output:**

```
----------------------------------------
Hebrew: רביעי Revi'i - תִּשְׁרֵי Tishrei 1, 5785
Civil : Wed - Oct 2, 2024
----------------------------------------
```

### Help / Usage Information

Run with incorrect or extra arguments to display the full help text:

```bash
./calendar-he --help
```

## Command-Line Reference

| Command | Description |
|---|---|
| `./calendar-he` | Show today's date in both calendars |
| `./calendar-he -h month date year` | Convert Civil (Gregorian) to Hebrew |
| `./calendar-he -H month date year` | Convert Civil (Gregorian) to Hebrew |
| `./calendar-he -g month date year` | Convert Civil (Gregorian) to Hebrew |
| `./calendar-he -G month date year` | Convert Civil (Gregorian) to Hebrew |
| `./calendar-he -c month date year` | Convert Hebrew to Civil (Gregorian) |
| `./calendar-he -C month date year` | Convert Hebrew to Civil (Gregorian) |
| `./calendar-he -j month date year` | Convert Hebrew to Civil (Gregorian) |
| `./calendar-he -J month date year` | Convert Hebrew to Civil (Gregorian) |

## Hebrew Calendar Month Numbering

When providing Hebrew dates, months are numbered in **Tishrei-first** order:

| Month Number | Non-Leap Year | Leap Year |
|---|---|---|
| 1 | Tishrei (תִּשְׁרֵי) | Tishrei (תִּשְׁרֵי) |
| 2 | Cheshvan (חֶשְׁוָן) | Cheshvan (חֶשְׁוָן) |
| 3 | Kislev (כִּסְלֵו) | Kislev (כִּסְלֵו) |
| 4 | Tevet (טֵבֵת) | Tevet (טֵבֵת) |
| 5 | Shevat (שְׁבָט) | Shevat (שְׁבָט) |
| 6 | Adar (אֲדָר) | Adar I (אֲדָר א) |
| 7 | Nisan (נִיסָן) | Adar II (אֲדָר ב) |
| 8 | Iyar (אִיָּר) | Nisan (נִיסָן) |
| 9 | Sivan (סִיוָן) | Iyar (אִיָּר) |
| 10 | Tammuz (תַּמּוּז) | Sivan (סִיוָן) |
| 11 | Av (אָב) | Tammuz (תַּמּוּז) |
| 12 | Elul (אֱלוּל) | Av (אָב) |
| 13 | -- | Elul (אֱלוּל) |

## How It Works

The program uses the **Julian Day Number (JDN)** as an intermediate representation for all date conversions:

1. **Gregorian to Hebrew:** The Gregorian date is first converted to a JDN. The Hebrew year is then estimated and refined by computing the JDN of 1 Tishrei for candidate years. The month and day are determined by walking through month lengths from Tishrei.

2. **Hebrew to Gregorian:** The JDN is computed from the Hebrew year start (1 Tishrei) plus the accumulated days of preceding months and the day within the month. The JDN is then converted back to a Gregorian date.

3. **Leap Year Handling:** The Hebrew calendar follows a 19-year Metonic cycle. Years 3, 6, 8, 11, 14, 17, and 19 of each cycle are leap years, gaining an extra month (Adar I), bringing the total from 12 to 13 months. The formula `((7 * year + 1) % 19) < 7` is used to determine leap years.

4. **Variable Month Lengths:** Cheshvan and Kislev have variable lengths (29 or 30 days) depending on the total year length, which ensures the calendar stays synchronized with both lunar months and the solar year.

## Important Notes

- **Day transition:** In the Hebrew calendar, the day transitions at **sunset**, not at midnight. The exact time of transition varies by location and season. This program converts dates based on the civil (midnight-based) convention.
- **Timezone:** When displaying today's date, the program uses the system's **local timezone**.
- **Date range:** The program accepts Gregorian months 1-12 and days 1-31 for Civil-to-Hebrew conversion, and Hebrew months 1-13 and days 1-30 for Hebrew-to-Civil conversion.

## Error Codes

| Code | Meaning |
|---|---|
| `0` | Success |
| `-10` | Input out of range |
| `-20` | Invalid input value |

## Project Structure

```
calendar-he/
├── calendar-he.cpp    # Main source file (single-file program)
├── LICENSE            # MIT License
└── README.md          # This file
```

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

Copyright (c) 2026 ad-digital-labs

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes (`git commit -m 'Add your feature'`)
4. Push to the branch (`git push origin feature/your-feature`)
5. Open a Pull Request
