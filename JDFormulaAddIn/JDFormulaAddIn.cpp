// AlteryxAddIn.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "JDFormulaAddIn.h"

void SetString(FormulaAddInData *pReturnValue, const wchar_t *pString)
{
	size_t nLen = wcslen(pString);
	wchar_t *pStringRet = (wchar_t *)GlobalAlloc(GMEM_FIXED, (nLen + 1) * sizeof(wchar_t));
	wcscpy_s(pStringRet, nLen, pString);
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

// this sample takes a variable number of numbers and simply sums them together, returning a number
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
