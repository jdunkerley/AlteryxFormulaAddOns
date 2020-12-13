#include "stdafx.h"
#include "AlteryxAbacus.h"

#include <boost\math\distributions\poisson.hpp>
#include "AlteryxAbacusUtils.h"

using boost::math::poisson;

 //Syntax: X, Mean, Cumulative
extern "C" long _declspec(dllexport) _stdcall PoissonDist(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs < 2 || nNumArgs > 3) {
		return AlteryxAbacusUtils::ReturnError(L"PoissonDist: Syntax x, Mean, Cumulative (= 0) (x and Mean required, others optional)", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != nVarType_DOUBLE) {
			return AlteryxAbacusUtils::ReturnError(L"PoissonDist: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[1].isNull || pArgs[1].dVal == 0) {
		pReturnValue->isNull = 1;
	}
	else {
		const double mean = pArgs[1].dVal;
		const double x = pArgs[0].dVal;

		pReturnValue->isNull = 0;
		poisson s(mean);
		pReturnValue->dVal = nNumArgs == 3 && !pArgs[2].isNull && pArgs[2].dVal
			? cdf(s, x) : pdf(s,x);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

// Syntax: P, Mean
extern "C" long _declspec(dllexport) _stdcall PoissonInv(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = 1;

	// Verify Arguments
	if (nNumArgs < 2 || nNumArgs > 2) {
		return AlteryxAbacusUtils::ReturnError(L"PoissonInv: Syntax P, Mean", pReturnValue, nNumArgs, pArgs);
	}
	for (int i = 0; i < nNumArgs; i++)
	{
		if (pArgs[i].nVarType != nVarType_DOUBLE) {
			return AlteryxAbacusUtils::ReturnError(L"PoissonInv: Non-numeric argument", pReturnValue, nNumArgs, pArgs);
		}
	}

	// Do Calculation
	if (pArgs[0].isNull || pArgs[0].dVal <= 0 || pArgs[0].dVal >= 1 || pArgs[1].dVal == 0) {
		pReturnValue->isNull = 1;
	}
	else {
		const double mean = pArgs[1].dVal;
		const double p = pArgs[0].dVal;

		pReturnValue->isNull = 0;
		
		//change rounding policy so that the selected values match the expected probability
		// https://www.boost.org/doc/libs/1_35_0/libs/math/doc/sf_and_dist/html/math_toolkit/dist/dist_ref/dists/poisson_dist.html
		using namespace boost::math::policies;
		using namespace boost::math;

		typedef poisson_distribution<
			double,
			policy<discrete_quantile<integer_round_up> > >
			poisson_round;

		poisson_round s(mean);
		
		pReturnValue->dVal = quantile(s,p);
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}
