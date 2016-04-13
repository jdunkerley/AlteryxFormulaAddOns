# Alteryx Formula AddOns
Set of Xml Based Formula AddOns for Alteryx. Suggestions of extra useful functions welcome!!
Also some simple C++ based functions as well.

## Installation
Assuming admin installed then put into %Program Files%\Alteryx\bin\RuntimeData\FormulaAddIn (or wherever you installed Alteryx)
There is an `install.bat` script which should promote via UAC and install to this directory. If Alteryx installed elsewhere than manuall copy xml files to appropriate subdirectory there.

## Testing
Assuming you have the CReW Runner macro, there is a workflow `RunUnitTest.yxmd` which will run all the test workflows checking the formula addins.

## Currently functions:

### MiscUtils
General functions
- IfNull - If first value is null return second
- Coalesce - Given list of values return first non null value

### MathUtils
Math based functions that I havent got a better home for!
- Modulo - General Double Based Modulo function
- HexBinX - Given an X,Y point and HexBin radius get X co-ordinate of bin (aiming to reproduce Tableau function)
- HexBinY - Given an X,Y point and HexBin radius get Y co-ordinate of bin (aiming to reproduce Tableau function) 
- Rand_Triangular - Given a uniform random number transform into a triangular distributed random

### DateUtils
Some useful date functions
- Day, Month, Year - extract part of the date
- WeekDay - 0 Sunday through to 6 Saturday
- Quarter - 1-4 for quarter
- BusinessDays - Number of weekdays between two dates
- OrdinalDay - Day of the year
- IsLeapYear - Is a year a leap year (takes a year not a date as an input use IsLearYear(Year([Date]))
- MakeDate - Create a new date from Year, Month, Day
- WeekStart - Get first Sunday before or equal to date
- WeekEnd - Get first Saturday after or equak to date
- MonthStart - Get First Day of Month
- MonthEnd - Get Last Day of Month
- YearStart - Get First Day of Year
- YearEnd - Get Last Day of Year
- QuarterStart - Get First Day of Quarter
- QuarterEnd - Get Last Day of Quarter 

### StringUtils
Some basic string functions I needed (e.g. StartsWith, EndsWith). 

*Ned has incorporated these into the v10 code base so not needed there. If running in older versions uncomment the Xml*
- StartsWith - Does a string start with another
- EndsWith - Does a string end with another
- Contains - Is a string in another
