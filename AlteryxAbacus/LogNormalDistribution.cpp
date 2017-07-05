#include "stdafx.h"
#include "AlteryxAbacusUtils.h"
#include "AlteryxAbacus.h"
#include <boost\math\distributions\lognormal.hpp>

using boost::math::lognormal;

// Syntax: X, Mean, StDev, Cumulative
extern "C" long _declspec(dllexport) _stdcall LogNormDist(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	switch (nNumArgs) {
	case 1:
	case 2:
	case 3:
	case 4:
		for (int i = 0; i < nNumArgs; i++)
		{
			if (pArgs[i].nVarType != 1) {
				return AlteryxAbacusUtils::ReturnError(L"LogNormDist: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
			}
		}
		break;
	default:
		return AlteryxAbacusUtils::ReturnError(L"LogNormDist: Syntax x, Mean = 0, StDev = 1, Cumulative = 0 (x required other default)", pReturnValue, nNumArgs, pArgs);
	}

	// Do Calculation
	if (pArgs[0].isNull) {
		pReturnValue->isNull = 1;
	}
	else {
		double location = nNumArgs < 2 || pArgs[1].isNull ? 0 : pArgs[1].dVal;
		double scale = nNumArgs < 3 || pArgs[2].isNull ? 1 : pArgs[2].dVal;
		bool cuml = nNumArgs == 4 && !pArgs[3].isNull && pArgs[3].dVal;
		double x = pArgs[0].dVal;

		pReturnValue->isNull = 0;
		lognormal s(location, scale);
		pReturnValue->dVal = cuml ? cdf(s, x) : pdf(s, x);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// Syntax: P, Mean, StDev
extern "C" long _declspec(dllexport) _stdcall LogNormInv(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	switch (nNumArgs) {
	case 1:
	case 2:
	case 3:
		for (int i = 0; i < nNumArgs; i++)
		{
			if (pArgs[i].nVarType != 1) {
				return AlteryxAbacusUtils::ReturnError(L"LogNormInv: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
			}
		}
		break;
	default:
		return AlteryxAbacusUtils::ReturnError(L"LogNormInv: Syntax p, Mean = 0, StDev = 1", pReturnValue, nNumArgs, pArgs);
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[0].dVal <= 0 || pArgs[0].dVal >= 1) {
		pReturnValue->isNull = 1;
	}
	else {
		double location = nNumArgs < 2 || pArgs[1].isNull ? 0 : pArgs[1].dVal;
		double scale = nNumArgs < 3 || pArgs[2].isNull ? 1 : pArgs[2].dVal;
		double p = pArgs[0].dVal;

		lognormal s(location, scale);
		double x = quantile(s, p);

		pReturnValue->isNull = 0;
		pReturnValue->dVal = x;
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}