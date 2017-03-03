#include "stdafx.h"
#include "JDFormulaAddIn.h"
#include <string>
#include <sstream>

int numericalValues[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
char characterValues[] = { 'M', '?', 'D', 0, 'C', '?', 'L', 0, 'X', '?', 'V', 0, 'I' };

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
	if (value > 5000 || value < 1) {
		const wchar_t* errorMessage = L"ToRoman: Outside Range of 1 to 5000.";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = true;
		return ReturnAndResetNull(false, nNumArgs, pArgs);
	}

	int integerValue = (int)value;
	std::wstringstream output;

	while (integerValue != 0) {
		for (int i = 0; i < sizeof(numericalValues); i++)
		{
			if (integerValue >= numericalValues[i]) {
				switch (characterValues[i]) {
				case '?':
					output << characterValues[i + 3] << characterValues[i - 1];
					break;
				case 0:
					output << characterValues[i + 1] << characterValues[i - 1];
					break;
				default:
					output << characterValues[i];
				}

				integerValue -= numericalValues[i];
				break;
			}
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