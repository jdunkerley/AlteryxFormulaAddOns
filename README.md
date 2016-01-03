# Alteryx Formula AddOns
Set of Xml Based Formula AddOns for Alteryx

Assuming admin installed then put into %Program Files%\Alteryx\bin\RuntimeData\FormulaAddIn (or wherever you installed Alteryx)
There is an install.bat script which should promote via UAC and install to this directory. If Alteryx installed elsewhere than manuall copy xml files to appropriate subdirectory there.

Set of test workflows checking the formula addin.

Currently have:

## MathUtils
General functions that I havent got a better home for!
- Modulo = General Double Based Modulo function
- HexBinX - Given an X,Y point and HexBin radius get X co-ordinate of bin (aiming to reproduce Tableau function)
- HexBinY - Given an X,Y point and HexBin radius get Y co-ordinate of bin (aiming to reproduce Tableau function) 

## DateUtils
Some useful date functions
- Day, Month, Year - extract part of the date
- WeekDay - 0 Sunday through to 6 Saturday
- Quarter - 1-4 for quarter
- BusinessDays - Number of weekdays between two dates [Untested at moment]
- MakeDate - Create a new date from Year, Month, Day
- MonthStart - Get First of Month
- MonthEnd - Get Last of Month
- YearStart - Get First Day of Year
- YearEnd - Get Last Day of Year

## StringUtils
Some basic string functions I needed (e.g. StartsWith, EndsWith). 
*Ned has incorporated these into the v10 code base so not needed there.*
- StartsWith - Does a string start with another
- EndsWith - Does a string end with another
- Contains - Is a string in another
