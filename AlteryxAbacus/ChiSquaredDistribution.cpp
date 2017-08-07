#include "stdafx.h"
#include "AlteryxAbacus.h"

#include <boost\math\distributions\chi_squared.hpp>
#include "AlteryxAbacusUtils.h"

using boost::math::chi_squared_distribution;

// Syntax: X, Degres of Freedom
extern "C" long _declspec(dllexport) _stdcall ChiDist(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs != 2) {
		return AlteryxAbacusUtils::ReturnError(L"ChiDist: Syntax x, Degrees of Freedom", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != 1) {
			return AlteryxAbacusUtils::ReturnError(L"ChiDist: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[1].isNull || pArgs[1].dVal < 1) {
		pReturnValue->isNull = 1;
	}
	else {
		chi_squared_distribution<double> s(floor(pArgs[1].dVal));
		pReturnValue->isNull = 0;
		pReturnValue->dVal = (1.0 - cdf(s, pArgs[0].dVal));
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// Syntax: P, Degrees of Freedom
extern "C" long _declspec(dllexport) _stdcall ChiInv(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs != 2) {
		return AlteryxAbacusUtils::ReturnError(L"ChiInv: Syntax p, Degrees of Freedom", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != 1) {
			return AlteryxAbacusUtils::ReturnError(L"ChiInv: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[0].dVal <= 0 || pArgs[0].dVal >= 1 || pArgs[1].isNull || pArgs[1].dVal < 1) {
		pReturnValue->isNull = 1;
	}
	else {
		chi_squared_distribution<double> s(floor(pArgs[1].dVal));
		pReturnValue->isNull = 0;
		pReturnValue->dVal = -quantile(s, pArgs[0].dVal);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}