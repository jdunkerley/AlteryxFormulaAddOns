#include "stdafx.h"
#include "JDFormulaAddIn.h"

#include <boost\math\distributions\normal.hpp>
using boost::math::normal;

// Syntax: X, Mean, StDev, Cumulative
extern "C" long _declspec(dllexport) _stdcall NormDist(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
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
				const wchar_t* errorMessage = L"NormDist: Non-numeric argument";
				SetString(pReturnValue, errorMessage);
				pReturnValue->isNull = 1;
				ResetIsNull(nNumArgs, pArgs);
				return 0;
			}
		}
		break;
	default:
		const wchar_t* errorMessage = L"NormDist: Syntax x, Mean (= 0), StDev (= 1), Cumulative (= 0) (x required, others optional)";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = 1;
		ResetIsNull(nNumArgs, pArgs);
		return 0;
		break;
	}

	// Do Calculation
	if (pArgs[0].isNull) {
		pReturnValue->isNull = 1;
	}
	else {
		normal s;
		double mean = nNumArgs < 2 || pArgs[1].isNull ? 0 : pArgs[1].dVal;
		double stDev = nNumArgs < 3 || pArgs[2].isNull ? 1 : pArgs[2].dVal;
		bool cuml = nNumArgs == 4 && !pArgs[3].isNull && pArgs[3].dVal;
		double x = (pArgs[0].dVal - mean) / stDev;

		pReturnValue->isNull = 0;
		pReturnValue->dVal = cuml ? cdf(s, x) : pdf(s, x);
	}

	ResetIsNull(nNumArgs, pArgs);
	return 1;
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
				const wchar_t* errorMessage = L"NormInv: Non-numeric argument";
				SetString(pReturnValue, errorMessage);
				pReturnValue->isNull = 1;
				ResetIsNull(nNumArgs, pArgs);
				return 0;
			}
		}
		break;
	default:
		const wchar_t* errorMessage = L"NormInv: Syntax p, Mean = 0, StDev = 1";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = 1;
		ResetIsNull(nNumArgs, pArgs);
		return 0;
		break;
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[0].dVal <= 0 || pArgs[0].dVal >= 1) {
		pReturnValue->isNull = 1;
	}
	else {
		normal s;
		double mean = nNumArgs < 2 || pArgs[1].isNull ? 0 : pArgs[1].dVal;
		double stDev = nNumArgs < 3 || pArgs[2].isNull ? 1 : pArgs[2].dVal;
		double p = pArgs[0].dVal;
		double x = quantile(s, p);

		pReturnValue->isNull = 0;
		pReturnValue->dVal = x * stDev + mean;
	}

	ResetIsNull(nNumArgs, pArgs);
	return 1;
}