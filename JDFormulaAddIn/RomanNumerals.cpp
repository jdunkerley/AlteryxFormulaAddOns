#include "stdafx.h"
#include "JDFormulaAddIn.h"
#include <string>
#include <sstream>

int numericalValues[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
std::wstring characterValues[] = { L"M", L"CM", L"D", L"CD", L"C", L"XC", L"L", L"XL", L"X", L"IX", L"V", L"IV", L"I" };

// Syntax: Value
extern "C" long _declspec(dllexport) _stdcall ToRoman(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 2;

	if (nNumArgs != 1 || pArgs[0].nVarType != 1) {
		const wchar_t* errorMessage = L"ToRoman: Requires one numerical argument.";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = true;
		return ReturnAndResetNull(false, nNumArgs, pArgs);
	}

	if (pArgs[0].isNull) {
		pReturnValue->isNull = true;
		return ReturnAndResetNull(true, nNumArgs, pArgs);
	}

	double value = pArgs[0].dVal;
	if (value > 5000 || value < 0) {
		SetString(pReturnValue, L"ToRoman: Outside Range of 0 to 5000.");
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

// Syntax: Roman
extern "C" long _declspec(dllexport) _stdcall FromRoman(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	if (nNumArgs != 1 || pArgs[0].nVarType != 2) {
		SetString(pReturnValue, L"FromRoman: Requires one text argument.");
		pReturnValue->isNull = true;
		return ReturnAndResetNull(false, nNumArgs, pArgs);
	}

	if (pArgs[0].isNull) {
		pReturnValue->isNull = true;
		return ReturnAndResetNull(true, nNumArgs, pArgs);
	}

	std::wstring roman(pArgs[0].pVal);

	long value = 0;
	size_t i = 0;
	int r = 0;
	while (i < roman.size()) {
		while (r < 13 && characterValues[r].compare(roman.substr(i, characterValues[r].size())) != 0) {
			r++;
		}

		if (r == 13) {
			SetString(pReturnValue, L"FromRoman: Invalid Roman Numeral.");
			pReturnValue->isNull = true;
			return ReturnAndResetNull(false, nNumArgs, pArgs);
		}

		value += numericalValues[r];
		i += characterValues[r].size();
	}

	pReturnValue->dVal = value;
	return ReturnAndResetNull(true, nNumArgs, pArgs);
}