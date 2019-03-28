# Alteryx Formula Add Ons #

Set of XML and C++ Based Formula Add Ons for Alteryx.

***Suggestions of extra useful functions welcome!!***

## Installation ##

There is an [install.bat](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/./install.bat) script which should promote via UAC, and install the necessary files into the Formula Add Ins directory.

You can uninstall the functions using [uninstall.bat](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/./uninstall.bat) script, which again should promote via UAC, and remove the necessary files from the directory.

### Manual Installation ###

If the installer script fails, you can manually install it to `%AlteryxBinDirectory%\RuntimeData\FormulaAddIn`. You will need to copy all the `XML` and `DLL` files.

## Current functions ##

Those functions which require the *AlteryxAbacus.dll* are labelled with *C++*

### [MiscUtils](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml)) ###

A few additional general methods for data preparation.

- [Version](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#version): Gets the major and minor version of the Alteryx Engine as a number *(C++)*
- [IfNull](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#ifnull): If first value is null return second
- [Coalesce](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#coalesce): Given list of values return first non null value *(C++)*
- [ReportError](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#reporterror): Raise an error from a formula if a confition is met, otherwise return a specified value *(C++)*
- [LogToFile](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#logtofile): Write a message to a log file *(C++)*
- [RangeJoin](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#rangejoin): Finds the first value in the `RangeCSV` parameter which is greater than or equal to the `Value` argument. *(C++)*

#### Variables ... ####

**These are very experimental so please use with caution**. 

- [VarPrint](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varprint): Lists all current variable names and values to a string table *(C++)*
- [VarReset](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varreset): Clears the internal caches of all variables. Can take a `Key` parameter to delete just that variable *(C++)*
- [VarNum](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varnum): Retrieves (if no `Value` argument passed) or stores a number value in the `Key` variable *(C++)*
- [VarNumExists](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varnumexists): Returns true if a number variable exists, false otherwise *(C++)*
- [VarText](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#vartext): Retrieves (if no `Value` argument passed) or stores a string value in the `Key` variable *(C++)*
- [VarTextExists](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#vartextexists): Returns true if a string variable exists, false otherwise *(C++)*
- [VarListExists](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varlistexists): Returns true if a list variable exists, false otherwise *(C++)*
- [VarListLength](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varlistlength): Returns the current length of a list if it exists, or NULL if the list does not exist *(C++)*
- [VarListAdd](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varlistadd): Adds an item to a list variable (creating a new list if needed) at the end of the list *(C++)*
- [VarListInsert](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varlistinsert): Inserts an item into a list (creating a new list if needed) at specified index. If `Index` is negative accesses from the end of the array backwards *(C++)*
- [VarListSet](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varlistset): Sets an item in an existing list at specified index. If `Index` is negative accesses from the end of the array backwards *(C++)*
- [VarListRemove](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varlistremove): Removes an item from a list variable at specified index. If `Index` is negative accesses from the end of the array backwards *(C++)*
- [VarListGet](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Miscellaneous-Functions-(MiscUtils.xml#varlistget): Gets a value from a list variable at the specified index. If `Index` is negative accesses from the end of the array backwards *(C++)*

### [MathUtils](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)) ###

Math based functions that I havent got a better home for!

- [Int](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#int): Rounds a number to nearest integer either equal to the number or closer to 0.
- [Modulo](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#modulo): General Double Based Modulo function
- [Quotient](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#quotient): Returns the integer part of a division
- [Sign](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#sign): Deteremines the sign of a number (-1 if less than 0, 1 if greater than, 0 otherwise)
- [HexBinX](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#hexbinx): Given an X,Y point and optional radius, get X co-ordinate of hexagonal bin's centre *(C++)*
- [HexBinY](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#hexbiny): Given an X,Y point and optional radius get Y co-ordinate of hexagonal bin's centre *(C++)* 
- [Rand_Triangular](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#rand_triangular): Given a uniform random number transform into a triangular distributed random
- [Avg](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#avg): Average of a list of values ignoring `NULL` *(C++)*
- [Count](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#count): Count of a list of values ignoring `NULL` *(C++)*
- [Sum](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#sum): Sum of a list of values ignoring `NULL` *(C++)*
- [Deg](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#deg): Convert radians to degrees
- [Rad](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#rad): Convert degrees to radians
- [NormDist](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#normdist): Compute PDF or CDF on Normal distribution *(C++)*
- [NormInv](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#norminv): Compute inverse CDF on Normal distribution *(C++)*
- [LogNormDist](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#lognormdist): Compute PDF or CDF on Log Normal distribution *(C++)*
- [LogNormInv](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#lognorminv): Compute inverse CDF on Log Normal distribution *(C++)*
- [TDist](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#tdist): Compute two tailed Student T distribution *(C++)*
- [TInv](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#tinv): Compute inverse two tailed Student T distribution *(C++)*
- [ChiDist](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#chidist): Compute CDF on Chi Squared distribution *(C++)*
- [ChiInv](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#chiinv): Compute inverse CDF on Chi Squared distribution *(C++)*
- [Phi](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#phi): Returns the golden ratio constant.
- [RandTriangular](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Math-Functions-(MathUtils.xml)#randtriangular): Produces a random number from a triangular distribution

### [DateUtils](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)) ###

Some additional functions for working with Dates and to a certain extent Times.

#### Date Time Creation Functions (Currently Just Concatenation) ####

- [MakeDate](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#makedate): Create a new date from Year, Month, Day *(C++)*
- [MakeTime](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#maketime): Create a new time from Hour, Minute, Second *(C++)*
- [MakeDateTime](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#makedatetime): Create a new `DateTime` from Year, Month, Day, Hour, Minute, Second *(C++)*
- [ToDate](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#todate): Truncate a `DateTime` to a `Date`
- [ToDateTime](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#todatetime): Appends midnight to a `Date` to create a `DateTime`
- [ToTime](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#totime): Get the time from a `DateTime`, `Date` (defaults to `00:00:00`) or a `Time`.

#### Date Time Parse Functions ####

- [DateFromMDY](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#datefrommdy): Parse a string in Month Day Year format to a Date (copes without leading 0s and different separators)
- [DateFromDMY](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#datefromdmy): Parse a string in Day Month Year format to a Date (copes without leading 0s and different separators)

#### Date Part Functions (returns numbers) ####

- [Day](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#day): Get the day of the month for a date or datetime [1-31]
- [Month](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#month): Gets the month number for a date or datetime [1-12]
- [Year](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#year): Gets the four digit year
- [Century](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#century): Gets the century for a date
- [WeekDay](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#weekday): Gets the day of the week [Sunday (0) through to Saturday (6)]
- [WeekNum](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#weeknum): Gets the week number of a Datetime, with Sunday as start of week and January 1st in Week 1 [1-53]
- [Quarter](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#quarter): Gets the quarter of the date [1-4]
- [OrdinalDay](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#ordinalday): Gets the day of the year [1-366]
- [DatePart](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#datepart): Replicates the SQL DatePart function, getting a specified part of the datetime input

#### Time Part Functions (returns numbers) ####

- [Hour](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#hour): Get the hour part of a DateTime or Time [0-23]
- [Minute](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#minute): Gets the minute part of a DateTime or Time [0-59]
- [Second](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#second): Gets the second part of a DateTime or Time [0-59]

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

- [DateAdd](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#dateadd): Equivalent to [DateTimeAdd](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/https://help.alteryx.com/current/Reference/Functions.htm?Highlight=datetimeadd) but returning a Date
- [BusinessDays](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#businessdays): Number of weekdays between two dates
- [Workday](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#workday): Add or remove a specified number of weekdays to a date (similar to Excel's Workday function but no support for holidays)
- [IsLeapYear](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/Date-and-Time-Functions-(DateUtils.xml)#isleapyear): Is a year a leap year *(takes a year not a date as an input use `IsLearYear(Year([Date])`)*

### [StringUtils](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)) ###

A few extension methods for working with strings.

- [FindStringLast](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#findstringlast): Gets the position from the left of the last instance of a term in a string
- [LeftPart](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#leftpart): Gets the text before the first instance of a separator
- [RightPart](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#rightpart): Gets the text after the first instance of a separator
- [Split](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#split): Splits a string into tokens and then returns the specified instance *(C++)*
- [ToRoman](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#toroman): Given a number between 0 and 5000, convert to Roman numerals *(C++)*
- [FromRoman](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#fromroman): Given Roman numeral convert to a number *(C++)*

#### Data Generation ####

- [RandomIPAddress](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#randomipaddress): Generates a random IP address, can be restricted to be within a CIDR block *(C++)*
- [RandomItem](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#randomitem): Picks a random item from the input list (can be list of numbers or list of strings but must be one type) *(C++)*
- [RandomString](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#randomstring): Generates a random string using a template to control format *(C++)*

#### Retired Functions ####

- [StartsWith](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#startswith): Does a string start with another
- [EndsWith](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#endswith): Does a string end with another
- [Contains](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/String-Functions-(StringUtils.xml)#contains): Is a string in another

## Testing ##

Assuming you have the CReW Runner macro, there is a workflow [RunUnitTest.yxmd](https://github.com/jdunkerley/AlteryxFormulaAddOns/wiki/./RunUnitTest.yxmd) which will run all the test workflows checking the formula add ins.
