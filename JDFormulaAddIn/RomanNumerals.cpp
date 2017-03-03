#include "stdafx.h"
#include "JDFormulaAddIn.h"
#include <string>
#include <sstream>

int numericalValues[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
std::wstring characterValues[] = { L"M", L"CM", L"D", L"CD", L"C", L"XC", L"L", L"XL", L"X", L"IX", L"V", L"IV", L"I" };

// Syntax: X, Mean, StDev, Cumulative
extern "C" long _declspec(dllexport) _stdcall ToRoman(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 2;

	if (nNumArgs != 1 || pArgs[0].nVarType != 1) {
		const wchar_t* errorMessage = L"ToRoman: Require one numerical argument.";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = true;
		return ReturnAndResetNull(false, nNumArgs, pArgs);
	}

	if (pArgs[0].isNull) {
		pReturnValue->isNull = true;
		return ReturnAndResetNull(true, nNumArgs, pArgs);
	}

	double value = pArgs[0].dVal;
	if (value > 5000) {
		const wchar_t* errorMessage = L"ToRoman: Outside Range of 1 to 5000.";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = true;
		return ReturnAndResetNull(false, nNumArgs, pArgs);
	}

	int integerValue = (int)value;
	std::wstringstream output;

	for (int i = 0; i < 13; i++) {
		while (integerValue >= numericalValues[i]) {
			output << characterValues[i];
			integerValue -= numericalValues[i];
		}
	}

	SetString(pReturnValue, output.str().c_str());
	return ReturnAndResetNull(true, nNumArgs, pArgs);
}

// Syntax: X, Mean, StDev, Cumulative
extern "C" long _declspec(dllexport) _stdcall FromRoman(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	if (nNumArgs != 1 || pArgs[0].nVarType != 2) {
		const wchar_t* errorMessage = L"FromRoman: Require one text argument.";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = true;
		return ReturnAndResetNull(false, nNumArgs, pArgs);
	}

	if (pArgs[0].isNull) {
		pReturnValue->isNull = true;
		return ReturnAndResetNull(true, nNumArgs, pArgs);
	}

	std::wstring roman(pArgs[0].pVal);



	return ReturnAndResetNull(true, nNumArgs, pArgs);
}