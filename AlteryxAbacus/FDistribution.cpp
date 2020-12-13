#include "stdafx.h"
#include "AlteryxAbacus.h"

#include <boost\math\distributions\fisher_f.hpp>
#include "AlteryxAbacusUtils.h"

using boost::math::fisher_f;

 //Syntax: X, DegreesFreedom1, DegreesFreedom2, Cumulative
extern "C" long _declspec(dllexport) _stdcall FDist(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs < 2 || nNumArgs > 3) {
		return AlteryxAbacusUtils::ReturnError(L"FDist: Syntax x, DegreesFreedom1, DegreesFreedom2", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != nVarType_DOUBLE) {
			return AlteryxAbacusUtils::ReturnError(L"FDist: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[1].isNull || pArgs[1].dVal == 0 || pArgs[2].isNull || pArgs[2].dVal == 0) {
		pReturnValue->isNull = 1;
	}
	else {
		const double df1 = pArgs[1].dVal < 1 ? 1 : pArgs[1].dVal;
		const double df2 = pArgs[2].dVal < 1 ? 1 : pArgs[2].dVal;
		const double x = pArgs[0].dVal;

		pReturnValue->isNull = 0;
		fisher_f s(df1, df2);
		pReturnValue->dVal = 1- cdf(s, x);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// Syntax: P, DegreesFreedom1, DegreesFreedom2
extern "C" long _declspec(dllexport) _stdcall FInv(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs < 3 || nNumArgs > 3) {
		return AlteryxAbacusUtils::ReturnError(L"FInv: Syntax P, DegreesFreedom1, DegreesFreedom2", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != nVarType_DOUBLE) {
			return AlteryxAbacusUtils::ReturnError(L"FInv: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[0].dVal <= 0 || pArgs[0].dVal >= 1 || pArgs[1].dVal == 0 || pArgs[2].dVal == 0 || pArgs[1].isNull || pArgs[2].isNull) {
		pReturnValue->isNull = 1;
	}
	else {
		const double df1 = pArgs[1].dVal < 1 ? 1 : pArgs[1].dVal;
		const double df2 = pArgs[2].dVal < 1 ? 1 : pArgs[2].dVal;
		const double p = pArgs[0].dVal;

		pReturnValue->isNull = 0;
		
		fisher_f s(df1, df2);
		
		pReturnValue->dVal = quantile(s,1-p);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}