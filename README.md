# Alteryx Formula Add Ons #

Set of XML and C++ Based Formula Add Ons for Alteryx.

***Suggestions of extra useful functions welcome!!***

## Installation ##

There is an [install.bat](./install.bat) script which should promote via UAC, and install the necessary files into the Formula Add Ins directory.

You can uninstall the functions using [uninstall.bat](./uninstall.bat) script, which again should promote via UAC, and remove the necessary files from the directory.

### Manual Installation ###

If the installer script fails, you can manually install it to `%AlteryxBinDirectory%\RuntimeData\FormulaAddIn`. You will need to copy all the `XML` and `DLL` files.

## Current functions ##

### [MiscUtils](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-%28MiscUtils.xml%29) ###

A few additional general methods for data preparation.

- [IfNull](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-%28MiscUtils.xml%29#ifnull): If first value is null return second
- [Coalesce](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-%28MiscUtils.xml%29#coalesce): Given list of values return first non null value *(C++)*

### [MathUtils](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)) ###

Math based functions that I havent got a better home for!

- [Modulo](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#modulo): General Double Based Modulo function
- [HexBinX](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#hexbinx): Given an X,Y point and optional radius, get X co-ordinate of hexagonal bin's centre
- [HexBinY](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#hexbiny): Given an X,Y point and optional radius get Y co-ordinate of hexagonal bin's centre 
- [Rand_Triangular](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#rand_triangular): Given a uniform random number transform into a triangular distributed random
- [Avg](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#avg): Average of a list of values ignoring `NULL`
- [Count](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#count): Count of a list of values ignoring `NULL`
- [Sum](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#sum): Sum of a list of values ignoring `NULL`

### [DateUtils](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)) ###

Some additional functions for working with Dates and to a certain extent Times.

#### Date Time Creation Functions (Currently Just Concatenation) ####

- [MakeDate](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#makedate): Create a new date from Year, Month, Day
- [MakeTime](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#maketime): Create a new time from Hour, Minute, Second
- [MakeDateTime](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#makedatetime): Create a new `DateTime` from Year, Month, Day, Hour, Minute, Second
- [ToDate](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#todate): Truncate a `DateTime` to a `Date`
- [ToDateTime](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#todatetime): Appends midnight to a `Date` to create a `DateTime`

#### Date Time Parse Functions ####

- [DateFromMDY](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#datefrommdy): Parse a string in Month Day Year format to a Date (copes without leading 0s and different separators)
- [DateFromDMY](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#datefromdmy): Parse a string in Day Month Year format to a Date (copes without leading 0s and different separators)

#### Date Part Functions (returns numbers) ####

- [Day](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#day): Get the day of the Month [1-31]
- [Month](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#month): Gets the month number [1-12]
- [Year](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#year): Gets the four digit year
- [WeekDay](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#weekday): Gets the day of the week [Sunday (0) through to Saturday (6)]
- [Quarter](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#quarter): Gets the quarter of the date [1-4]
- [OrdinalDay](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#ordinalday): Gets the day of the year [1-366]

#### Period Start and End ####

- [WeekStart](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#weekstart): Get first Sunday before or equal to date
- [WeekEnd](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#weekend): Get first Saturday after or equal to date
- [MonthStart](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#monthstart): Get First Day of Month
- [MonthEnd](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#monthend): Get Last Day of Month
- [QuarterStart](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#quarterstart): Get First Day of Quarter
- [QuarterEnd](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#quarterend): Get Last Day of Quarter
- [YearStart](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#yearstart): Get First Day of Year
- [YearEnd](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#yearend): Get Last Day of Year

#### Other Date Functions ####

- [DateAdd](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#dateadd): Equivalent to [DateTimeAdd](http://downloads.alteryx.com/Alteryx8.6.2/WebHelp/Reference/DateTimeFunctions.htm) but returning a Date
- [BusinessDays](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#businessdays): Number of weekdays between two dates
- [IsLeapYear](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#isleapyear): Is a year a leap year *(takes a year not a date as an input use `IsLearYear(Year([Date])`)*

### [StringUtils](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-%28StringUtils.xml%29) ###

A few extension methods for working with strings.

- [LeftPart](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#leftpart): Gets the text before the first instance of a separator
- [RightPart](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#rightpart): Gets the text after the first instance of a separator
- [Split](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#split): Splits a string into tokens and then returns the specified instance

#### Retired Functions ####

- [StartsWith](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#startswith): Does a string start with another
- [EndsWith](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#endswith): Does a string end with another
- [Contains](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#contains): Is a string in another

## Testing ##

Assuming you have the CReW Runner macro, there is a workflow [RunUnitTest.yxmd](./RunUnitTest.yxmd) which will run all the test workflows checking the formula add ins.
