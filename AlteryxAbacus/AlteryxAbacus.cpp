// AlteryxAddIn.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "AlteryxAbacus.h"
#include "AlteryxAbacusUtils.h"
#include <string>

//// a way to error a function from XML
extern "C" long _declspec(dllexport) _stdcall ReportError(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = nNumArgs > 2 ? pArgs[2].nVarType : 1;

	if (nNumArgs < 1 || pArgs[0].nVarType != 1 || pArgs[0].isNull != 0 || pArgs[0].dVal != 0) {
		return AlteryxAbacusUtils::ReturnError((nNumArgs < 2 || pArgs[1].nVarType == 1) ? L"Reporting An Error!" : pArgs[1].pVal, pReturnValue, nNumArgs, pArgs);
	}

	if (nNumArgs < 2) {
		pReturnValue->isNull = 1;
	}
	else {
		AlteryxAbacusUtils::CopyValue(&pArgs[2], pReturnValue);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

//// this sample takes a variable number of inputs and returns the first non-null
extern "C" long _declspec(dllexport) _stdcall Coalesce(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	if (nNumArgs < 1) {
		pReturnValue->nVarType = 1;
		return AlteryxAbacusUtils::ReturnError(L"Need an argument!", pReturnValue, nNumArgs, pArgs);
	}

	int varType = pArgs[0].nVarType;
	pReturnValue->nVarType = varType;

	pReturnValue->isNull = 1;

	for (int x = 0; x < nNumArgs; x++)
	{
		if (pArgs[x].nVarType != varType) {
			return AlteryxAbacusUtils::ReturnError(L"Mismatched argument types, all must be same general type as first parameter.", pReturnValue, nNumArgs, pArgs);
		}

		if (!pArgs[x].isNull)
		{
			AlteryxAbacusUtils::CopyValue(&pArgs[x], pReturnValue);
			break;
		}
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// this sample takes a variable number of inputs and returns the first non-null
extern "C" long _declspec(dllexport) _stdcall Count(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;
	pReturnValue->isNull = 0;

	int count = 0;
	for (int x = 0; x < nNumArgs; x++)
	{
		count += pArgs[x].isNull == 0;
	}

	pReturnValue->dVal = count;
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// this sample takes a variable number of inputs and returns the first non-null
extern "C" long _declspec(dllexport) _stdcall Sum(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;
	pReturnValue->isNull = 0;

	double sum = 0;
	for (int x = 0; x < nNumArgs; x++)
	{
		if (pArgs[x].nVarType != 1) {
			return AlteryxAbacusUtils::ReturnError(L"Non-numeric argument, all must be numbers.", pReturnValue, nNumArgs, pArgs);
		}

		if (!pArgs[x].isNull)
		{
			sum += pArgs[x].dVal;
		}
	}

	pReturnValue->dVal = sum;
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// this sample takes a variable number of inputs and returns the first non-null
extern "C" long _declspec(dllexport) _stdcall Average(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;
	pReturnValue->isNull = 0;

	double sum = 0;
	int count = 0;
	for (int x = 0; x < nNumArgs; x++)
	{
		if (pArgs[x].nVarType != 1)
		{
			const wchar_t* errorMessage = L"Non-numeric argument, all must be numbers.";
			AlteryxAbacusUtils::SetString(pReturnValue, errorMessage);
			pReturnValue->isNull = 1;
			return 0;
		}

		if (pArgs[x].isNull == 0)
		{
			sum += pArgs[x].dVal;
			count++;
		}
	}

	if (count == 0) {
		pReturnValue->isNull = 1;
	}
	else {
		pReturnValue->dVal = sum / count;
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

auto matches(const wchar_t letter, const std::wstring separator) {
	for (auto i : separator)
	{
		if (i == letter) {
			return true;
		}
	}

	return false;
}

// Need String, String (char), Integer
extern "C" long _declspec(dllexport) _stdcall Split(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 2;

	// Check Input Parameters
	if (nNumArgs != 3 ||
		pArgs[0].nVarType != 2 ||
		pArgs[1].nVarType != 2 ||
		pArgs[2].nVarType != 1) {
		return AlteryxAbacusUtils::ReturnError(L"Syntax: String, Delimiter, Token Number.", pReturnValue, nNumArgs, pArgs);
	}

	// Check for Nulls
	if (pArgs[0].isNull || pArgs[2].isNull || pArgs[2].dVal < 1 || pArgs[1].isNull) {
		AlteryxAbacusUtils::CopyValue(&pArgs[0], pReturnValue);
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	// Separator Map
	const std::wstring separatorString(pArgs[1].pVal);

	// Copy the string
	const std::wstring input(pArgs[0].pVal);
	const size_t len = input.size();
	if (!len) {
		AlteryxAbacusUtils::CopyValue(&pArgs[0], pReturnValue);
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	int count = static_cast<int>(pArgs[2].dVal);
	pReturnValue->isNull = 1;
	size_t oldPos = 0;
	size_t charPos;
	for (charPos = 0; charPos < len; charPos++) {
		if (matches(input[charPos], separatorString)) {
			if (!--count) {
				break;
			}

			oldPos = charPos + 1;
		}
	}

	if (count <= 1) {
		AlteryxAbacusUtils::SetString(pReturnValue, oldPos < charPos ? input.substr(oldPos, charPos - oldPos).c_str() : L"");
		pReturnValue->isNull = 0;
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}