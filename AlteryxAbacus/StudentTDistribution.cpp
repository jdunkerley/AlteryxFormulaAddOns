#include "stdafx.h"
#include "AlteryxAbacus.h"

#include <boost\math\distributions\students_t.hpp>
#include "AlteryxAbacusUtils.h"

using boost::math::students_t_distribution;

// Syntax: X, Degres of Freedom
extern "C" long _declspec(dllexport) _stdcall TDist(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs != 2) {
		return AlteryxAbacusUtils::ReturnError(L"TDist: Syntax x, Degrees of Freedom", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != 1) {
			return AlteryxAbacusUtils::ReturnError(L"TDist: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}	
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[1].isNull || pArgs[1].dVal <= 0) {
		pReturnValue->isNull = 1;
	}
	else {
		students_t_distribution<double> s(pArgs[1].dVal);
		pReturnValue->isNull = 0;
		pReturnValue->dVal = (1.0 - cdf(s, pArgs[0].dVal)) * 2;
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// Syntax: P, Degrees of Freedom
extern "C" long _declspec(dllexport) _stdcall TInv(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs != 2) {
		return AlteryxAbacusUtils::ReturnError(L"TInv: Syntax p, Degrees of Freedom", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != 1) {
			return AlteryxAbacusUtils::ReturnError(L"TInv: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[0].dVal <= 0 || pArgs[0].dVal >= 1 || pArgs[1].isNull || pArgs[1].dVal <= 0) {
		pReturnValue->isNull = 1;
	}
	else {
		students_t_distribution<double> s(pArgs[1].dVal);
		pReturnValue->isNull = 0;
		pReturnValue->dVal = -quantile(s, pArgs[0].dVal / 2);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}