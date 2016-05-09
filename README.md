# Alteryx Formula Add Ons

Set of XML and C++ Based Formula Add Ons for Alteryx.
***Suggestions of extra useful functions welcome!!***

## Installation

There is an [install.bat](./install.bat) script which should promote via UAC, and install the necessary files
into the Formula Add Ins directory.

### Manual Installation

If the installer script fails, you can manually install it to 
`%AlteryxBinDirectory%\RuntimeData\FormulaAddIn`.
You will need to copy all the `XML` and `DLL` files.

## Current functions

### MiscUtils

General functions

- `IfNull`: If first value is null return second
- `Coalesce`: Given list of values return first non null value *(C++)*

### MathUtils

Math based functions that I havent got a better home for!

- `Modulo`: General Double Based Modulo function
- `HexBinX`: Given an X,Y point and optional radius, get X co-ordinate of bin's centre *(C++)*
- `HexBinY`: Given an X,Y point and optional radius get Y co-ordinate of bin's centre *(C++)* 
- `Rand_Triangular`: Given a uniform random number transform into a triangular distributed random
- `Avg`: Average of a list of values ignoring `NULL` *(C++)*
- `Count`: Count of a list of values ignoring `NULL` *(C++)*
- `Sum`: Sum of a list of values ignoring `NULL` *(C++)*

### DateUtils

Some useful date functions. 

#### Date Time Creation Functions (Currently Just Concatenation)

- `MakeDate`: Create a new date from Year, Month, Day
- `MakeTime`: Create a new time from Hour, Minute, Second
- `MakeDateTime`: Create a new `DateTime` from Year, Month, Day, Hour, Minute, Second
- `ToDate`: Truncate a `DateTime` to a `Date`
- `ToDateTime`: Appends midnight to a `Date` to create a `DateTime`

#### Date Part Functions (returns numbers)

- `Day`: Get the day of the Month [1-31]
- `Month`: Gets the month number [1-12]
- `Year`: Gets the four digit year
- `WeekDay`: Gets the day of the week [Sunday (0) through to Saturday (6)]
- `Quarter`: Gets the quarter of the date [1-4]
- `OrdinalDay`: Gets the day of the year [1-366]

#### Period Start and End

- `WeekStart`: Get first Sunday before or equal to date
- `WeekEnd`: Get first Saturday after or equal to date
- `MonthStart`: Get First Day of Month
- `MonthEnd`: Get Last Day of Month
- `QuarterStart`: Get First Day of Quarter
- `QuarterEnd`: Get Last Day of Quarter
- `YearStart`: Get First Day of Year
- `YearEnd`: Get Last Day of Year

#### Other Date Functions

- `DateAdd`: Equivalent to [DateTimeAdd](http://downloads.alteryx.com/Alteryx8.6.2/WebHelp/Reference/DateTimeFunctions.htm) but returning a Date
- `BusinessDays`: Number of weekdays between two dates
- `IsLeapYear`: Is a year a leap year *(takes a year not a date as an input use `IsLearYear(Year([Date])`)*

### StringUtils

String manipulation

- `LeftPart`: Gets the text before the first instance of a separator
- `RightPart`: Gets the text after the first instance of a separator
- `Split`: Splits a string into tokens and then returns the specified instance *(C++)*

#### Retired Functions

*Alteryx has incorporated these into the v10 code base so not needed there.
If running in older versions un-comment the Xml*

- `StartsWith`: Does a string start with another
- `EndsWith`: Does a string end with another
- `Contains`: Is a string in another

## Testing

Assuming you have the CReW Runner macro, there is a workflow [RunUnitTest.yxmd](./RunUnitTest.yxmd) which will run all 
the test workflows checking the formula add ins.
