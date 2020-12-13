#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include "AlteryxAbacus.h"
#include "AlteryxAbacusUtils.h"

extern "C" long _declspec(dllexport) _stdcall Int64Add(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = nVarType_WCHAR;

	if (nNumArgs == 0) {
		AlteryxAbacusUtils::SetString(pReturnValue, L"0");
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	long long acc = 0;

	for (size_t i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != nVarType_WCHAR) {
			pReturnValue->isNull = true;
			return AlteryxAbacusUtils::ReturnError(L"Int64 Add: <Integers:Strings>", pReturnValue, nNumArgs, pArgs);
		}

		if (pArgs[i].isNull) {
			pReturnValue->isNull = true;
			return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
		}

		acc += _wtoll(pArgs[i].pVal);
	}

	AlteryxAbacusUtils::SetString(pReturnValue, std::to_wstring(acc).c_str());
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall Int64Mult(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = nVarType_WCHAR;

	if (nNumArgs == 0) {
		AlteryxAbacusUtils::SetString(pReturnValue, L"1");
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	long long acc = 1;

	for (size_t i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != nVarType_WCHAR) {
			pReturnValue->isNull = true;
			return AlteryxAbacusUtils::ReturnError(L"Int64 Mult: <Integers:String>", pReturnValue, nNumArgs, pArgs);
		}

		if (pArgs[i].isNull) {
			pReturnValue->isNull = true;
			return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
		}

		acc *= _wtoll(pArgs[i].pVal);
	}

	AlteryxAbacusUtils::SetString(pReturnValue, std::to_wstring(acc).c_str());
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall Int64Div(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = nVarType_WCHAR;

	if (nNumArgs != 2 || pArgs[0].nVarType != nVarType_WCHAR || pArgs[1].nVarType != nVarType_WCHAR) {
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnError(L"Int64 Div: <A:String> <B:String>", pReturnValue, nNumArgs, pArgs);
	}

	if (pArgs[0].isNull || pArgs[1].isNull) {
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	long long div = _wtoll(pArgs[1].pVal);
	if (div == 0) {
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	long long acc = _wtoll(pArgs[0].pVal) / div;
	AlteryxAbacusUtils::SetString(pReturnValue, std::to_wstring(acc).c_str());
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall Int64Mod(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = nVarType_WCHAR;

	if (nNumArgs != 2 || pArgs[0].nVarType != nVarType_WCHAR || pArgs[1].nVarType != nVarType_WCHAR) {
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnError(L"Int64 Mod: <A:String> <B:String>", pReturnValue, nNumArgs, pArgs);
	}

	if (pArgs[0].isNull || pArgs[1].isNull) {
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	long long div = _wtoll(pArgs[1].pVal);
	if (div == 0) {
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	long long acc = _wtoll(pArgs[0].pVal) % div;
	AlteryxAbacusUtils::SetString(pReturnValue, std::to_wstring(acc).c_str());
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}
