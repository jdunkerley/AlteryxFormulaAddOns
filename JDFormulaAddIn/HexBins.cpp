#include "stdafx.h"
#include "JDFormulaAddIn.h"
#include "AlteryxAddInUtils.h"

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
		return AlteryxAddInUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	double r = (pArgs[2].isNull ? 1.0 : pArgs[2].dVal);
	double dy = 2 * 0.86602540378443864676372317075294 * r; // 2 * Sin(π/3)
	double dx = 1.5 * r;

	double px = pArgs[0].dVal / dx;
	int pi = static_cast<int>(round(px));
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

	return AlteryxAddInUtils::ReturnSuccess(nNumArgs, pArgs);
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
		return AlteryxAddInUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	double r = (pArgs[2].isNull ? 1.0 : pArgs[2].dVal);
	double dy = 2 * 0.86602540378443864676372317075294 * r; // 2 * Sin(π/3)
	double dx = 1.5 * r;

	double px = pArgs[0].dVal / dx;
	int pi = static_cast<int>(round(px));
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

	return AlteryxAddInUtils::ReturnSuccess(nNumArgs, pArgs);
}
