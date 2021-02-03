#include "stdafx.h"
#include "AlteryxAbacus.h"

#include <boost\math\distributions\gamma.hpp>
#include "AlteryxAbacusUtils.h"

// Syntax: X, Shape, Scale, Cumulative
extern "C" long _declspec(dllexport) _stdcall GammaDist(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs < 2 || nNumArgs > 4) {
		return AlteryxAbacusUtils::ReturnError(L"GammaDist: Syntax x, Shape, Scale (= 1), Cumulative (= 0) (x and Shape required, others optional)", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != nVarType_DOUBLE) {
			return AlteryxAbacusUtils::ReturnError(L"GammaDist: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[1].isNull || pArgs[1].dVal == 0) {
		pReturnValue->isNull = 1;
	}
	else {
		const double shape = pArgs[1].dVal;
		const double scale = nNumArgs < 3 || pArgs[2].isNull ? 1 : pArgs[2].dVal;
		const double x = pArgs[0].dVal / scale;

		pReturnValue->isNull = 0;
		pReturnValue->dVal = nNumArgs == 4 && !pArgs[3].isNull && pArgs[3].dVal
			? boost::math::gamma_p(shape, x)/scale
			: boost::math::gamma_p_derivative(shape, x);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// Syntax: P, Shape, Scale
extern "C" long _declspec(dllexport) _stdcall GammaInv(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs < 2 || nNumArgs > 3) {
		return AlteryxAbacusUtils::ReturnError(L"GammaInv: Syntax P, Shape, Scale (= 1) (x and Shape required, others optional)", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != nVarType_DOUBLE) {
			return AlteryxAbacusUtils::ReturnError(L"GammaInv: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[0].dVal <= 0 || pArgs[0].dVal >= 1 || pArgs[1].dVal == 0) {
		pReturnValue->isNull = 1;
	}
	else {
		const double shape = pArgs[1].dVal;
		const double scale = nNumArgs < 3 || pArgs[2].isNull ? 1 : pArgs[2].dVal;
		const double p = pArgs[0].dVal;

		pReturnValue->isNull = 0;
		pReturnValue->dVal = boost::math::gamma_p_inv(shape, p) * scale;
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}
