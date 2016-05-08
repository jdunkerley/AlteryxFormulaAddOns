// AlteryxAddIn.cpp : Defines the exported functions for the DLL application.
//
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

// this sample takes a variable number of inputs and returns the first non-null
extern "C" long _declspec(dllexport) _stdcall Coalesce(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = pArgs[0].nVarType;
	pReturnValue->isNull = 1;

	for (int x = 0; x < nNumArgs; x++)
	{
		if (pArgs[x].isNull == 0)
		{
			pReturnValue->isNull = 0;
			if (pArgs[x].nVarType == 1) {
				pReturnValue->nVarType = 1;
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

// Need String, String (char), Integer
extern "C" long _declspec(dllexport) _stdcall Split(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 2;

	// Check Input Parameters
	if (nNumArgs != 3 ||
		pArgs[0].isNull || pArgs[0].nVarType != 2 ||
		pArgs[1].isNull || pArgs[1].nVarType != 2 ||
		pArgs[2].isNull || pArgs[2].nVarType != 1 || pArgs[2].dVal < 0) {
		pReturnValue->isNull = 1;
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

// Need Double X, Double Y, Double R
extern "C" long _declspec(dllexport) _stdcall HexBinX(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Check Input Parameters
	if (nNumArgs < 2 || nNumArgs > 3 ||
		pArgs[0].isNull || pArgs[0].nVarType != 1 ||
		pArgs[1].isNull || pArgs[1].nVarType != 1 ||
		(nNumArgs == 3 && pArgs[2].nVarType != 1)) {
		pReturnValue->isNull = 1;
		ResetIsNull(nNumArgs, pArgs);
		return 1;
	}

	double r = (pArgs[2].isNull ? 1.0 : pArgs[2].dVal);
	double dy = 2 * 0.86602540378443864676372317075294 * r; // 2 * Sin(π/3)
	double dx = 1.5 * r;

	double px = pArgs[0].dVal / dx;
	int pi = (int)round(px);
	bool mod2 = (pi & 1) == 1;
	double py = pArgs[1].dVal / dy - (mod2 ? 0.5 : 0);
	double pj = round(py);
	double px1 = (px - pi) * dx;

	if (fabs(px1) * 3 > 1)
	{
		double py1 = (py - pj) * dy;
		double pj2 = pj + (py < pj ? -1 : 1) / 2.0;
		int pi2 = pi + (px < pi ? -1 : 1);
		double px2 = (px - pi2) * dx;
		double py2 = (py - pj2) * dy;

		if (px1 * px1 + py1 * py1 > px2 * px2 + py2 * py2)
		{
			pi = pi2;
		}
	}

	if (isnan(pi * dx)) {
		pReturnValue->isNull = 1;
	}
	else {
		pReturnValue->dVal = pi * dx;
	}

	return 1;
}

// Need Double X, Double Y, Double R
extern "C" long _declspec(dllexport) _stdcall HexBinY(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Check Input Parameters
	if (nNumArgs < 2 || nNumArgs > 3 ||
		pArgs[0].isNull || pArgs[0].nVarType != 1 ||
		pArgs[1].isNull || pArgs[1].nVarType != 1 ||
		(nNumArgs == 3 && pArgs[2].nVarType != 1)) {
		pReturnValue->isNull = 1;
		ResetIsNull(nNumArgs, pArgs);
		return 1;
	}

	double r = (pArgs[2].isNull ? 1.0 : pArgs[2].dVal);
	double dy = 2 * 0.86602540378443864676372317075294 * r; // 2 * Sin(π/3)
	double dx = 1.5 * r;

	double px = pArgs[0].dVal / dx;
	int pi = (int)round(px);
	bool mod2 = (pi & 1) == 1;
	double py = pArgs[1].dVal / dy - (mod2 ? 0.5 : 0);
	double pj = round(py);
	double px1 = (px - pi) * dx;

	if (fabs(px1) * 3 > 1)
	{
		double py1 = (py - pj) * dy;
		double pj2 = pj + (py < pj ? -1 : 1) / 2.0;
		int pi2 = pi + (px < pi ? -1 : 1);
		double px2 = (px - pi2) * dx;
		double py2 = (py - pj2) * dy;

		if (px1 * px1 + py1 * py1 > px2 * px2 + py2 * py2)
		{
			pj = pj2 + (mod2 ? 1 : -1) / 2.0;
			pi = pi2;
			mod2 = (pi & 1) == 1;
		}
	}

	if (isnan((pj + (mod2 ? 0.5 : 0)) * dy)) {
		pReturnValue->isNull = 1;
	}
	else {
		pReturnValue->dVal = (pj + (mod2 ? 0.5 : 0)) * dy;
	}

	return 1;
}