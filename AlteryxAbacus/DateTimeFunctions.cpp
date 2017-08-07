#include <string>
#include "AlteryxAbacus.h"
#include "AlteryxAbacusUtils.h"

const int daysInMonthArray[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int daysInMonth(int year, int month)
{
	if (month < 1 || month > 12)
	{
		return 0;
	}

	if (month != 2)
	{	
		return daysInMonthArray[month - 1];
	}

	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) ? 29 : 28;
}

extern "C" long __declspec(dllexport) _stdcall MakeDate(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 2;

	if (nNumArgs < 1 || pArgs[0].nVarType != 1 || pArgs[0].isNull || (nNumArgs > 1 && pArgs[1].nVarType != 1) || (nNumArgs > 2 && pArgs[2].nVarType != 1) || nNumArgs > 3)
	{
		return AlteryxAbacusUtils::ReturnError(L"MakeDate: Requires between 1 and 3 numerical arguments", pReturnValue, nNumArgs, pArgs);
	}

	int year = static_cast<int>(pArgs[0].dVal);
	int month = nNumArgs > 1 && !pArgs[1].isNull ? static_cast<int>(pArgs[1].dVal) : 1;
	int day = nNumArgs > 2 && !pArgs[2].isNull ? static_cast<int>(pArgs[2].dVal) : 1;

	if (year == 0  && month == 0 && day == 0)
	{
		// Parse mode passes 3 0s
		pReturnValue->isNull = 1;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	if (year < 1400 || year > 9999)
	{
		return AlteryxAbacusUtils::ReturnError(L"MakeDate: Alteryx Dates only valid between 1400 and 9999", pReturnValue, nNumArgs, pArgs);
	}

	if (month < 1 || month > 12)
	{
		return AlteryxAbacusUtils::ReturnError(L"MakeDate: Month must be between 1 and 12", pReturnValue, nNumArgs, pArgs);
	}

	int maxDay = daysInMonth(year, month);
	if (day < 1 || day > maxDay)
	{
		std::wstring msg(L"MakeDate: Day must be between 1 and ");
		return AlteryxAbacusUtils::ReturnError((msg + std::to_wstring(maxDay)).c_str(), pReturnValue, nNumArgs, pArgs);
	}

	std::wstring output = std::to_wstring(year);
	output += (month < 10 ? L"-0" : L"-") + std::to_wstring(month);
	output += (day < 10 ? L"-0" : L"-") + std::to_wstring(day);
	AlteryxAbacusUtils::SetString(pReturnValue, output.c_str());
	pReturnValue->isNull = 0;
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long __declspec(dllexport) _stdcall MakeTime(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 2;

	if ((nNumArgs > 0 && pArgs[0].nVarType != 1) || (nNumArgs > 1 && pArgs[1].nVarType != 1) || (nNumArgs > 2 && pArgs[2].nVarType != 1) || nNumArgs > 3)
	{
		return AlteryxAbacusUtils::ReturnError(L"MakeTime: Requires between 0 and 3 numerical arguments", pReturnValue, nNumArgs, pArgs);
	}

	int hour = nNumArgs > 0 && !pArgs[0].isNull ? static_cast<int>(pArgs[0].dVal) : 0;
	int minute = nNumArgs > 1 && !pArgs[1].isNull ? static_cast<int>(pArgs[1].dVal) : 0;
	int second = nNumArgs > 2 && !pArgs[2].isNull ? static_cast<int>(pArgs[2].dVal) : 0;

	if (hour < 0 || hour > 23)
	{
		return AlteryxAbacusUtils::ReturnError(L"MakeTime: Hour must be between 0 and 23", pReturnValue, nNumArgs, pArgs);
	}

	if (minute < 0 || minute > 59)
	{
		return AlteryxAbacusUtils::ReturnError(L"MakeTime: Minute must be between 0 and 59", pReturnValue, nNumArgs, pArgs);
	}

	if (second < 0 || second > 59)
	{
		return AlteryxAbacusUtils::ReturnError(L"MakeTime: Second must be between 0 and 59", pReturnValue, nNumArgs, pArgs);
	}

	std::wstring output = (hour < 10 ? L"0" : L"") + std::to_wstring(hour);
	output += (minute < 10 ? L":0" : L":") + std::to_wstring(minute);
	output += (second < 10 ? L":0" : L":") + std::to_wstring(second);
	AlteryxAbacusUtils::SetString(pReturnValue, output.c_str());
	pReturnValue->isNull = 0;
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long __declspec(dllexport) _stdcall MakeDateTime(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	// The Date Part
	long dateResult = MakeDate(nNumArgs > 3 ? 3 : nNumArgs, pArgs, pReturnValue);
	if (dateResult != 0)
	{
		std::wstring msg(pReturnValue->pVal);
		AlteryxAbacusUtils::SetString(pReturnValue, msg.substr(8).insert(0, L"MakeDateTime").c_str());
		return dateResult;
	}
	std::wstring datePart(pReturnValue->pVal);

	if (nNumArgs < 4)
	{
		if (pReturnValue->isNull == 0) {
			std::wstring date(pReturnValue->pVal);
			AlteryxAbacusUtils::SetString(pReturnValue, date.append(L" 00:00:00").c_str());
		}

		return 0;
	}

	// The Time Part
	long timeResult = MakeTime(nNumArgs - 3, pArgs + 3, pReturnValue);
	if (timeResult != 0)
	{
		std::wstring msg(pReturnValue->pVal);
		AlteryxAbacusUtils::SetString(pReturnValue, msg.substr(8).insert(0, L"MakeDateTime").c_str());
		return dateResult;
	}
	
	AlteryxAbacusUtils::SetString(pReturnValue, datePart.append(pReturnValue->pVal).c_str());
	return 0;
}