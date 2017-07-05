#include "stdafx.h"
#include "AlteryxAbacus.h"
#include <string>
#include <sstream>
#include "AlteryxAbacusUtils.h"

const int numericalValues[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
const std::wstring characterValues[] = { L"M", L"CM", L"D", L"CD", L"C", L"XC", L"L", L"XL", L"X", L"IX", L"V", L"IV", L"I" };

// Syntax: Value
extern "C" long _declspec(dllexport) _stdcall ToRoman(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 2;

	if (nNumArgs != 1 || pArgs[0].nVarType != 1) {
		return AlteryxAbacusUtils::ReturnError(L"ToRoman: Requires one numerical argument.", pReturnValue, nNumArgs, pArgs);
	}

	if (pArgs[0].isNull) {
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	double value = pArgs[0].dVal;
	if (value > 5000 || value < 0) {
		return AlteryxAbacusUtils::ReturnError(L"ToRoman: Outside Range of 0 to 5000.", pReturnValue, nNumArgs, pArgs);
	}

	int integerValue = static_cast<int>(value);
	std::wstringstream output;

	for (int i = 0; i < 13; i++) {
		while (integerValue >= numericalValues[i]) {
			output << characterValues[i];
			integerValue -= numericalValues[i];
		}
	}

	AlteryxAbacusUtils::SetString(pReturnValue, output.str().c_str());
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// Syntax: Roman
extern "C" long _declspec(dllexport) _stdcall FromRoman(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	if (nNumArgs != 1 || pArgs[0].nVarType != 2) {
		return AlteryxAbacusUtils::ReturnError(L"FromRoman: Requires one text argument.", pReturnValue, nNumArgs, pArgs);
	}

	if (pArgs[0].isNull) {
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
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
			return AlteryxAbacusUtils::ReturnError(L"FromRoman: Invalid Roman Numeral.", pReturnValue, nNumArgs, pArgs);
		}

		value += numericalValues[r];
		i += characterValues[r].size();
	}

	pReturnValue->dVal = value;
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}