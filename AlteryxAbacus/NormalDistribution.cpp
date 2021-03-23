#include "stdafx.h"
#include "AlteryxAbacus.h"

#include <boost\math\distributions\normal.hpp>
#include "AlteryxAbacusUtils.h"

using boost::math::normal;

// Syntax: X, Mean, StDev, Cumulative
extern "C" long _declspec(dllexport) _stdcall NormDist(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs < 1 || nNumArgs > 4) {
		return AlteryxAbacusUtils::ReturnError(L"NormDist: Syntax x, Mean (= 0), StDev (= 1), Cumulative (= 0) (x required, others optional)", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != 1) {
			return AlteryxAbacusUtils::ReturnError(L"NormDist: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull) {
		pReturnValue->isNull = 1;
	}
	else {
		double mean = nNumArgs < 2 || pArgs[1].isNull ? 0 : pArgs[1].dVal;
		double stDev = nNumArgs < 3 || pArgs[2].isNull || pArgs[2].dVal == 0 ? 1 : pArgs[2].dVal;
		bool cuml = nNumArgs == 4 && !pArgs[3].isNull && pArgs[3].dVal;
		double x = pArgs[0].dVal;
		normal s(mean, stDev);

		pReturnValue->isNull = 0;
		pReturnValue->dVal = cuml ? cdf(s, x) : pdf(s, x);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// Syntax: P, Mean, StDev
extern "C" long _declspec(dllexport) _stdcall NormInv(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
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
				return AlteryxAbacusUtils::ReturnError(L"NormInv: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
			}
		}
		break;
	default:
		return AlteryxAbacusUtils::ReturnError(L"NormInv: Syntax p, Mean = 0, StDev = 1", pReturnValue, nNumArgs, pArgs);
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[0].dVal <= 0 || pArgs[0].dVal >= 1) {
		pReturnValue->isNull = 1;
	}
	else {
		double mean = nNumArgs < 2 || pArgs[1].isNull ? 0 : pArgs[1].dVal;
		double stDev = nNumArgs < 3 || pArgs[2].isNull || pArgs[2].dVal == 0 ? 1 : pArgs[2].dVal;
		double p = pArgs[0].dVal;
		normal s(mean,stDev);
		double x = quantile(s, p);

		pReturnValue->isNull = 0;
		pReturnValue->dVal = x;
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}
