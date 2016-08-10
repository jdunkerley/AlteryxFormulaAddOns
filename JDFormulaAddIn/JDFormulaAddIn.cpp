// AlteryxAddIn.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "JDFormulaAddIn.h"

void SetString(FormulaAddInData *pReturnValue, const wchar_t *pString)
{
	size_t nLen = wcslen(pString);
	wchar_t *pStringRet = (wchar_t *)GlobalAlloc(GMEM_FIXED, (nLen + 1) * sizeof(wchar_t));
	wcscpy(pStringRet, pString);
	pReturnValue->pVal = pStringRet;
	pReturnValue->nVarType = 2;
}

void ResetIsNull(int nNumArgs, FormulaAddInData *pArgs)
{
	for (int x = 0; x < nNumArgs; x++)
	{
		pArgs[x].isNull = 0;
	}
}

//// this sample takes a variable number of inputs and returns the first non-null
extern "C" long _declspec(dllexport) _stdcall Coalesce(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = pArgs[0].nVarType;
	pReturnValue->isNull = 1;

	for (int x = 0; x < nNumArgs; x++)
	{
		if (pArgs[x].nVarType != pArgs[0].nVarType) {

			const wchar_t* errorMessage = L"Mismatched argument types, all must be same general type as first parameter.";
			SetString(pReturnValue, errorMessage);
			ResetIsNull(nNumArgs, pArgs);
			return 0;
		}

		if (pArgs[x].isNull == 0)
		{
			pReturnValue->isNull = 0;
			if (pArgs[0].nVarType == 1) {
				pReturnValue->dVal = pArgs[x].dVal;
			}
			else {
				SetString(pReturnValue, pArgs[x].pVal);
			}
			break;
		}
	}

	ResetIsNull(nNumArgs, pArgs);
	return 1;
}

// this sample takes a variable number of inputs and returns the first non-null
extern "C" long _declspec(dllexport) _stdcall Count(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;
	pReturnValue->isNull = 0;

	int count = 0;
	for (int x = 0; x < nNumArgs; x++)
	{
		if (pArgs[x].isNull == 0)
		{
			count++;
		}
	}

	pReturnValue->dVal = count;
	ResetIsNull(nNumArgs, pArgs);
	return 1;
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
			const wchar_t* errorMessage = L"Non-numeric argument, all must be numbers.";
			SetString(pReturnValue, errorMessage);
			pReturnValue->isNull = 1;
			return 0;
		}

		if (pArgs[x].isNull == 0)
		{
			sum += pArgs[x].dVal;
		}
	}

	pReturnValue->dVal = sum;
	ResetIsNull(nNumArgs, pArgs);
	return 1;
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
		if (pArgs[x].nVarType != 1) {
			const wchar_t* errorMessage = L"Non-numeric argument, all must be numbers.";
			SetString(pReturnValue, errorMessage);
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

	ResetIsNull(nNumArgs, pArgs);
	return 1;
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
		const wchar_t* errorMessage = L"Syntax: String, Delimiter, Token Number.";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = 1;
		return 0;
	}

	// Check for Nulls
	if (pArgs[0].isNull || pArgs[2].isNull || pArgs[2].dVal < 0 || pArgs[1].isNull || wcslen(pArgs[1].pVal) == 0) {
		SetString(pReturnValue, pArgs[0].pVal);
		ResetIsNull(nNumArgs, pArgs);
		return 1;
	}

	// Copy the string
	size_t nLen = wcslen(pArgs[0].pVal);
	if (nLen == 0) {
		pReturnValue->isNull = true;
		return 1;
	}

	wchar_t *input = new wchar_t[nLen + 1];
	wcscpy(input, pArgs[0].pVal);

	// Split the String
	wchar_t* buffer = NULL;
	wchar_t *token = NULL;
	token = wcstok_s(input, pArgs[1].pVal, &buffer);
	int count = 1;
	while (token != NULL && count < pArgs[2].dVal) {
		token = wcstok_s(NULL, pArgs[1].pVal, &buffer);
		count++;
	}

	if (token == NULL) {
		pReturnValue->isNull = true;
	} else {
		SetString(pReturnValue, token);
	}

	delete input;
	return 1;
}


// Need String, String (char), Integer
extern "C" long _declspec(dllexport) _stdcall CharMatch(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Check Input Parameters
	if (nNumArgs != 2 ||
		pArgs[0].nVarType != 2 ||
		pArgs[1].nVarType != 2) {
		const wchar_t* errorMessage = L"Syntax: Left, Right.";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = 1;
		return 0;
	}

	// Check for Nulls
	if (pArgs[0].isNull || pArgs[1].isNull) {
		pReturnValue->dVal = 0;
		pReturnValue->isNull = true;
		ResetIsNull(nNumArgs, pArgs);
		return 1;
	}



	return 1;
}

